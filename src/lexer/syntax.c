#include "minishell.h"

int is_redir(t_type type);
int quotes_closed(char *line);
int check_syntax(t_token *tok, char *line);
void remove_quotes_tokens(t_token *lst);
char *remove_quotes(char *str);

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
	if (!quotes_closed(line))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n",1);
		return (0);
	}	
	if (tok->type == PIPE)
		return (ft_putstr_fd("syntax error near '|'\n",1), 0);
	while (tok)
	{
	if (tok->type == PIPE && tok->next == NULL)
		return (ft_putstr_fd("syntax error near '|'\n",1), 0);
	if (tok->type == PIPE && tok->next->type == PIPE)
		return (ft_putstr_fd("syntax error near '|'\n",1), 0);
	if (is_redir(tok->type))
	{
		if (!tok->next)
			return (ft_putstr_fd("syntax error near newline\n",1), 0);
		if (tok->next->type != WORD)
			return (ft_putstr_fd("syntax error\n",1), 0);
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