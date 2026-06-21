#include "minishell.h"

int g_exit_status = 0;


void init_shell(t_env *env);


int main(int argc, char *argv[], char *envp[])
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = env_init(envp);
	init_shell(env);
	return (0);
}

void init_shell(t_env *env)
{
	char	*line;
	t_token	*tokens_list;
	t_cmd	*cmd;

	while (1)
	{
		line = readline("Minishell$> ");
		if (!line)
		{
			free_env(env);
			exit(g_exit_status);
		}
		add_history(line);
		tokens_list = lexer(line);
		if (tokens_list && check_syntax(tokens_list, line))
		{
			remove_quotes_tokens(tokens_list);
			cmd = parse(tokens_list);
			execute(cmd, env);
			free_cmd(cmd);
		}
		free_tokens(tokens_list);
		free(line);
	}
}




