#include "minishell.h"

void	built_export(t_cmd *cmd, t_env *env);
void add_env_node_export(t_env *last, char *key, char *value);
int	update_export(t_env *env, char *key, char *value);
void	update_env(t_env *node, char *value);

void	built_export(t_cmd *cmd, t_env *env)
{
	char	*equal;
	char	*key;
	char	*value;
	t_env	*last;

	equal = ft_strchr(cmd->argv[1], '=');
	if (!equal)
		return ;
	key = ft_substr(cmd->argv[1], 0, equal - cmd->argv[1]);
	value = ft_strdup(equal + 1);
	if (!update_export(env, key, value))
	{
		last = env;
		while (last->next)
			last = last->next;
		add_env_node_export(last, key, value);
	}
	free(key);
	free(value);
}

void add_env_node_export(t_env *last, char *key, char *value)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;

    last->next = new;
}

int	update_export(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			update_env(env, value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	update_env(t_env *node, char *value)
{
	free(node->value);
	node->value = ft_strdup(value);
}
