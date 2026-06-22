#include "minishell.h"

int is_built_in(char *cmd);
int bulit_pwd();
void bulit_exit();
int bulit_cd(char *cd);
int built_echo(t_cmd *cmd);
int built_env(t_env *envp);
void built_export(t_cmd *cmd, t_env *env);
void add_env_node_export(t_env *env, char *key, char *value);
void update_env(t_env *node, char *value);
int	update_export(t_env *env, char *key, char *value);

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


int bulit_pwd()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return (1);
}

void bulit_exit()
{
    printf("exit\n");
    exit(0);
}

int bulit_cd(char *cd)
{
    if (chdir(cd) == -1)
        perror("cd");
    return (1);    
}

int built_echo(t_cmd *cmd)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (cmd->argv[1] && !strcmp(cmd->argv[1], "-n"))
    {
        n = 1;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if (!n)
        printf("\n");
    return (1);    
}

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