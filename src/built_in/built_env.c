#include "minishell.h"

int built_env(t_env *envp);

int built_env(t_env *envp)
{
    char **env;
    int i;

    i = 0;
    env = env_to_array(envp);
    while (env[i])
    {
        printf("%s\n",env[i]);
        i++;
    }
    return (1);
}