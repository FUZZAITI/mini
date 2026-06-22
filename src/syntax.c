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
		if (tok->next->type != WORD)
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
			tmp = remove_quotes(lst->content);
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

char *remove_quotes(char *str)
{
    char    *result;
    int     i;
    int     state;

    result = strdup("");
    i = 0;
    state = NORMAL;
    while (str[i])
    {
        if (str[i] == '\'' && state == NORMAL)
            state = S_QUOTE;
        else if (str[i] == '\'' && state == S_QUOTE)
            state = NORMAL;
        else if (str[i] == '\"' && state == NORMAL)
            state = D_QUOTE;
        else if (str[i] == '\"' && state == D_QUOTE)
            state = NORMAL;
        else
            result = add_char_to_str(result, str[i]);
        i++;
    }
    return (result);
}