#include "minishell.h"

t_env *new_env(char *key, char *value);
void add_env_back(t_env **env, t_env *new);
t_env *env_init(char **envp);
int env_size(t_env *env);
char **env_to_array(t_env *env);
char *get_env_value(char *var_name, t_env *env_list);



t_env *new_env(char *key, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    return (node);
}

void add_env_back(t_env **env, t_env *new)
{
    t_env *tmp;

    if (!*env)
    {
        *env = new;
        return ;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

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

void print_env_list(t_env *env)
{
    while (env)
    {
        printf("key=[%s] value=[%s]\n",
               env->key,
               env->value);
        env = env->next;
    }
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

int env_size(t_env *env)
{
    int count = 0;

    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char *get_env_value(char *var_name, t_env *env_list)
{
    while (env_list)
    {
        if (ft_strcmp(env_list->key, var_name) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}

