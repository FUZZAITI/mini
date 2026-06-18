#include "minishell.h"

char *get_cmd_path(t_cmd *cmd, char **path);
void execve_cmd(t_cmd *cmd, char **envp, char *path);
char **split_path(char **env);

/*
void execute_cmd(t_cmd *cmd, char **env)
{
    char **path;
    char *full_path;

    path = split_path(env);
    if (!(is_built_in(cmd, env)))
    {
        if ((full_path = get_cmd_path(cmd,path)))
            execve_cmd(cmd, env, full_path);
    }
}

char **split_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
        {
            return (ft_split(env[i] + 5, ':'));
            break;
        }
        i++;
    }
    return NULL; 
}

char *get_cmd_path(t_cmd *cmd, char **path)
{
    int i;
    char *tmp;
    char *full_path;

    i = 0;
    while (path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        full_path = ft_strjoin(tmp, cmd->argv[0]);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return(full_path);
        free(full_path);
        i++;
    }
    return NULL;
}

void execve_cmd(t_cmd *cmd, char **envp, char *path)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        execve(path, cmd->argv, envp);
        perror("execve");
        exit(1);
    }
    waitpid(pid, NULL, 0);
    free(path);
}
    */