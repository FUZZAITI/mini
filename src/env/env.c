#include "minishell.h"

t_env *env_init(char **envp);
char **env_to_array(t_env *env);

t_env *env_init(char **envp)
{
    t_env   *env;
    char    *equal;
    char    *key;
    char    *value;
    int     len;

    env = NULL;
    while (*envp)
    {
        equal = ft_strchr(*envp, '=');
        len = equal - *envp;
        key = ft_substr(*envp, 0, len);
        value = ft_strdup(equal + 1);
        add_env_back(&env, new_env(key, value));
        free(key);
        free(value);
        envp++;
    }
    return (env);
}

char **env_to_array(t_env *env)
{
    char **res;
    char *tmp;
    int i;

    res = malloc(sizeof(char *) * (env_size(env) + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (env)
    {
        tmp = ft_strjoin(env->key, "=");
        res[i] = ft_strjoin(tmp, env->value);
        free(tmp);

        env = env->next;
        i++;
    }
    res[i] = NULL;
    return (res);
}


