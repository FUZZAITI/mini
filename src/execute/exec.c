#include "minishell.h"

int count_cmds(t_cmd *cmd);
void execute(t_cmd *cmd_list, t_env *env);
void execute_single(t_cmd *cmd, t_env *env);
void run_builtin(t_cmd *cmd, t_env *env);
void restore_std_fds(int saved_stdin, int saved_stdout);
int setup_redirections(t_cmd *cmd);




int count_cmds(t_cmd *cmd)
{
    int count;

    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

void execute(t_cmd *cmd_list, t_env *env)
{
    int cmd_count;

    cmd_count = count_cmds(cmd_list);
    if (cmd_count == 1)
        execute_single(cmd_list, env);
    else
        execute_pipeline(cmd_list, env, cmd_count);
}

void execute_single(t_cmd *cmd, t_env *env)
{
    int saved_stdin;
    int saved_stdout;

    if (is_built_in(cmd->argv[0]))
    {   
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        if (setup_redirections(cmd) < 0)
        {
            restore_std_fds(saved_stdin, saved_stdout);
            return ;
        }
        run_builtin(cmd, env);
        restore_std_fds(saved_stdin, saved_stdout);
    }
    else
        execute_cmd(cmd, env);
}

void restore_std_fds(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

int setup_redirections(t_cmd *cmd)
{
    int fd;

    if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
        {
            perror(cmd->infile);
            return (-1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    /*
    if (cmd->heredoc)
    {
        fd = do_heredoc(cmd->delimiter);
        if (fd < 0)
            return (-1);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    */
    if (cmd->outfile)
    {
        if (cmd->append)
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror(cmd->outfile);
            return (-1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return (0);
}
