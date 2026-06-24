#include "minishell.h"

int is_built_in(char *cmd);
void run_builtin(t_cmd *cmd, t_env *env);

int is_built_in(char *cmd)
{   
    
    if (!ft_strcmp(cmd,"echo"))
        return 1;
    else if (!ft_strcmp(cmd,"cd"))
        return 1;
    else if (!ft_strcmp(cmd,"pwd"))
        return 1;
    else if (!ft_strcmp(cmd,"export"))
        return 1;
    else if (!ft_strcmp(cmd,"unset"))
        return 1;
    else if (!ft_strcmp(cmd,"env"))
        return 1;
    else if (!ft_strcmp(cmd,"exit"))
        return 1;
    return (0);                    
}

void run_builtin(t_cmd *cmd, t_env *env)
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
    else if (!ft_strcmp(comando,"export"))
        built_export(cmd, env);                    
}