#include "minishell.h"

t_cmd *parse(t_token *tok)
{
	t_cmd *head;
	t_cmd *cmd;
	int 	arg_i;

	printf("%d\n",count_args(tok));
	head = new_cmd(count_args(tok));
	cmd = head;
	
	while (tok)
	{
		if (tok->type == PIPE)
		{
			cmd->next = new_cmd(count_args(tok->next));
			cmd = cmd->next;
		}
		else if (tok->type == WORD)
			cmd->argv[arg_i++] = ft_strdup(tok->content);
		else if (is_redir(tok->type))
			handle_cmd_redirect(cmd, tok);
		tok = tok->next;
	}
	return (head);
	
}

int count_args(t_token *tok)
{
	int count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			count++;
		else if (is_redir(tok->type))
			tok = tok->next; 
		tok = tok->next;
	}
	return (count);
}

t_cmd *new_cmd(int count)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd-> delimiter = NULL;
	cmd->next = NULL;
	return (cmd);
}

void print_cmd(t_cmd *cmd)
{
	int i;
	int n = 1;

	while (cmd)
	{
		printf("=== CMD %d ===\n", n++);
		printf("argv: \n");
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf("  argv[%d] = [%s]\n", i, cmd->argv[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}



void handle_cmd_redirect(t_cmd *cmd, t_token *tok)
{
	if (tok->type == REDIR_IN)
		cmd->infile = ft_strdup(tok->next->content);
	else if (!strcmp(tok->content,">"))
		cmd->outfile = ft_strdup(tok->next->content);
	else if (!strcmp(tok->content,">>"))
	{
		cmd->outfile = ft_strdup(tok->next->content);
		cmd->append = 1;
	}	
	else if (!strcmp(tok->content,"<<"))
	{
		cmd->delimiter = ft_strdup(tok->next->content);
		cmd->heredoc = 1;
	}
}





////////////////////////////////////////////////////////////////////////////////////

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
			print_tokens(tokens_list);
			parse(tokens_list);
		}
		free(line);
	}
}




