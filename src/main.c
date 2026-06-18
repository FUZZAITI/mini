#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char        *line;
	t_token     *tokens_list;
	t_env       *env;
	t_cmd       *cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("$Mine -> ");
		if (!line)
			exit(0);   
		tokens_list = lexer(line);
		add_history(line);
		if((check_syntax(tokens_list, line)))
		{
			remove_quotes_tokens(tokens_list);
			cmd = parse(tokens_list);
			free_tokens(tokens_list);
			print_cmds(cmd);
			//execute(cmd, envp);
			//execute_cmd(cmd, envp);
		}
		//free_tokens(tokens_list);
		free(line);
	}
}




