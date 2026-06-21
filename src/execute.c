#include "minishell.h"

char *get_cmd_path(t_cmd *cmd, char **path);
void execve_cmd(t_cmd *cmd, t_env *env, char *path);
char **split_path(t_env *env);
void execute_cmd(t_cmd *cmd, t_env *env);


void execute_cmd(t_cmd *cmd, t_env *env)
{
    char **path;
    char *full_path;

    path = split_path(env);
    if ((full_path = get_cmd_path(cmd,path)))
        execve_cmd(cmd, env, full_path);
    free(path);
       
}

char **split_path(t_env *env)
{
    while (env)
    {
        if (!strcmp(env->key, "PATH"))
            return (ft_split(env->value,':'));
        env = env->next;
    }
    return (NULL); 
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

void execve_cmd(t_cmd *cmd, t_env *env, char *path)
{
    pid_t   pid;
    char    **envp;

    envp = env_to_array(env);
    pid = fork();
    if (pid == 0)
    {
        if (setup_redirections(cmd) < 0)  
            exit(1);
        execve(path, cmd->argv, envp);
        perror("execve");
        free(envp);
        exit(1);
    }
    waitpid(pid, NULL, 0);
    free(envp);
}
    