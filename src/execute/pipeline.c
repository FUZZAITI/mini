#include "minishell.h"

void execute_single_child(t_cmd *cmd, t_env *env);
pid_t launch_cmd(t_cmd *cmd, t_env *env, int prev_fd, int fd[2]);
void execute_pipeline(t_cmd *cmd, t_env *env, int cmd_count);
void free_array(char **array);



pid_t launch_cmd(t_cmd *cmd, t_env *env, int prev_fd, int fd[2])
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (prev_fd != -1)
            dup2(prev_fd, STDIN_FILENO);
        if (cmd->next)
            dup2(fd[1], STDOUT_FILENO);
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
        {
            close(fd[0]);
            close(fd[1]);
        }
        execute_single_child(cmd, env);
        exit(g_exit_status);   
    }
    return (pid);
}

void execute_pipeline(t_cmd *cmd, t_env *env, int cmd_count)
{
    int     fd[2];
    int     prev_fd;
    pid_t   pid;

    prev_fd = -1;
    while (cmd)
    {
        if (cmd->next)
            pipe(fd);
        pid = launch_cmd(cmd, env, prev_fd, fd);
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
        cmd = cmd->next;
    }
    while (cmd_count--)
        wait(NULL);
}


void execute_single_child(t_cmd *cmd, t_env *env)
{
    char    *path;
    char    **envp;
    char    **full_path;

    if (setup_redirections(cmd) < 0)
        exit(1);
    if (is_built_in(cmd->argv[0]))
    {
        run_builtin(cmd, env);
        exit(g_exit_status);
    }
    if (ft_strchr(cmd->argv[0], '/'))
        path = ft_strdup(cmd->argv[0]);
    else
    {
        full_path = split_path(env);
        path = get_cmd_path(cmd, full_path);
        free_array(full_path);
    }
    if (!path)
    {
        ft_putstr_fd(cmd->argv[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    envp = env_to_array(env);
    execve(path, cmd->argv, envp);
    perror("execve");
    exit(126);
}

void free_array(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}