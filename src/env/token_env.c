#include "minishell.h"

int env_size(t_env *env);
char *get_env_value(char *var_name, t_env *env_list);
t_env *new_env(char *key, char *value);
void add_env_back(t_env **env, t_env *new);

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