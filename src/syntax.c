#include "minishell.h"

int is_redir(t_type type)
{
    return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

int quotes_closed(char *line)
{
	char quote;
	int i;

	i = 0;
	while (line[i])
	{
	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i++];
		while (line[i] && line[i] != quote)
		i++;
		if (!line[i])
		return (0);
	}
	i++;
	}
	return (1);
}

int check_syntax(t_token *tok, char *line)
{
	if (!tok)
		return (0);
	if (!quotes_closed(line))
	{
		printf("syntax error: unclosed quotes\n");
		return (0);
	}	
	if (tok->type == PIPE)
		return (printf("syntax error near555 '|'\n"), 0);
	while (tok)
	{
	if (tok->type == PIPE && tok->next == NULL)
		return (printf("syntax error near222 '|'\n"), 0);
	if (tok->type == PIPE && tok->next->type == PIPE)
		return (printf("syntax error near333 '|'\n"), 0);
	if (is_redir(tok->type))
	{
		if (!tok->next)
			return (printf("syntax error near newline\n"), 0);
		if (tok->type == WORD)
			return (printf("syntax error\n"), 0);
	}
	tok = tok->next;
	}
	return (1);
}

void remove_quotes_tokens(t_token *lst)
{
	char *tmp;

	while (lst)
	{
		if (lst->type == WORD)
		{
			tmp = remove_quote(lst->content);
			free(lst->content);
			lst->content = tmp;
		}
		lst = lst->next;
	}
}

int len_quotes(char *line)
{
	int i;
	int len;
	
	i = 0;
	len = 0;
	while (line[i])
	{
	 if (line[i] != '\'' && line[i] != '\"')
		len++;
	 i++;
	}
	return (len);
}

char *remove_quote(char *token)
{
	int i;
	int len;
	char *resul;

	i = 0;
	len = len_quotes(token);
	resul = malloc(len + 1);
	if (!resul)
		return (NULL);
	i = 0;
	len = 0;
	while (token[i])
	{
		if (token[i] != '\'' && token[i] != '\"')
			resul[len++] = token[i];
		i++;
	}
	resul[len] = '\0';
	return (resul);
}