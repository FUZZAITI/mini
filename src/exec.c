#include "minishell.h"

int setup_redirections(t_cmd *cmd);
int count_cmds(t_cmd *cmd);
void execute(t_cmd *cmd_list, char  **env);
void execute_single(t_cmd *cmd, char **env);
void run_builtin(t_cmd *cmd, char **env);



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

void execute(t_cmd *cmd_list, char  **env)
{
    int cmd_count;

    cmd_count = count_cmds(cmd_list);
    if (cmd_count == 1)
       execute_single(cmd_list, env);
   // else
        //execute_pipeline(cmd_list, env, cmd_count);
}

void execute_single(t_cmd *cmd, char **env)
{
    int saved_stdin;
    int saved_stdout;

    if (is_built_in(cmd->argv[0]))
    {   
        saved_stdin = dup(STDIN_FILENO);
        saved_stdout = dup(STDOUT_FILENO);
        //if (setup_redirections(cmd) < 0)
        //    return ;
        run_builtin(cmd, env);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
    }
    //else
        //execute_external_single(cmd, env);
}

void run_builtin(t_cmd *cmd, char **env)
{   
    char *comando = cmd->argv[0];

    if (!ft_strcmp(comando,"echo"))
        built_echo(cmd);
    else if (!ft_strcmp(comando,"cd"))
        bulit_cd(cmd->argv[1]);
    else if (!ft_strcmp(comando,"pwd"))
        bulit_pwd();
    else if (!ft_strcmp(comando,"env"))
        built_env(env);
    else if (!ft_strcmp(comando,"exit"))
        bulit_exit();                   
}

int setup_redirections(t_cmd *cmd)
{
    if (cmd->infile == NULL && cmd->outfile == NULL)
        return (0);

}