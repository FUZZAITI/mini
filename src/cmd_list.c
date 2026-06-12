#include "minishell.h"

t_cmd *parse(t_token *tok)
{
	t_cmd *head;
	t_cmd *cmd;
	int 	arg_i;

	head = new_cmd(count_args(tok));
	cmd = head;
	arg_i = 0;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			cmd->argv[arg_i] = NULL;
			cmd->next = new_cmd(count_args(tok->next));
			cmd = cmd->next;
			arg_i = 0;
		}
		else if (tok->type == WORD)
			cmd->argv[arg_i++] = ft_strdup(tok->content);
		else if (is_redir(tok->type))
		{
			handle_cmd_redirect(cmd, tok);
			tok = tok->next;
		}
		tok = tok->next;
	}
	cmd->argv[arg_i] = NULL;
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

void print_cmds(t_cmd *cmd)
{
    int i;
    int n = 1;

    while (cmd)
    {
        printf("=== CMD %d ===\n", n++);

        printf("argv:\n");
        i = 0;
        while (cmd->argv && cmd->argv[i])
        {
            printf("  argv[%d] = [%s]\n", i, cmd->argv[i]);
            i++;
        }

        printf("infile    : %s\n",
            cmd->infile ? cmd->infile : "NULL");

        printf("outfile   : %s\n",
            cmd->outfile ? cmd->outfile : "NULL");

        printf("append    : %d\n", cmd->append);

        printf("heredoc   : %d\n", cmd->heredoc);

        printf("delimiter : %s\n",
            cmd->delimiter ? cmd->delimiter : "NULL");

        printf("\n");

        cmd = cmd->next;
    }
}



void handle_cmd_redirect(t_cmd *cmd, t_token *tok)
{
    if (tok->type == REDIR_IN)
        cmd->infile = ft_strdup(tok->next->content);

    else if (tok->type == REDIR_OUT)
        cmd->outfile = ft_strdup(tok->next->content);

    else if (tok->type == APPEND)
    {
        cmd->outfile = ft_strdup(tok->next->content);
        cmd->append = 1;
    }
    else if (tok->type == HEREDOC)
    {
        cmd->delimiter = ft_strdup(tok->next->content);
        cmd->heredoc = 1;
    }
}