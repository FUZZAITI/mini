#include "minishell.h"

int handle_word(t_token **tokens, char *str);
int handle_infile(t_token **tokens, char *str);
int handle_outfile(t_token **tokens, char *str);
int find_quote_end(char *str, char quote);

int handle_word(t_token **tokens, char *str)
{
	int i;
	char *word;

	i = 0;
	while (str[i] && !strchr(" |<>", str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += find_quote_end(&str[i], str[i]);
		}
		else
			i++;
	}
	word = strndup(str, i);
	add_token(tokens, word, 0);
	free(word);
	return (i);
}

int handle_infile(t_token **tokens, char *str)
{
	int i;
	char *word;
	
	i = 0;
	if (str[i] == '>' && str[i + 1] == '>')
	{
		word = strndup(str, (i + 2));
		add_token(tokens, word, 2);
		return (2);
	}
	else if (str[i] == '>')
	{
		word = strndup(str, (i + 1));
		add_token(tokens, word, 4);
	}
	free(word);
	return (i + 1);
}

int handle_outfile(t_token **tokens, char *str)
{
	int i;
	char *word;

	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
	{
		word = strndup(str, (i + 2));
		add_token(tokens, word, 3);
		return (2);
	}
	else if (str[i] == '<')
	{
		word = strndup(str, (i + 1));
		add_token(tokens, word, 5);
	}
	free(word);
	return (i + 1);	
}

int find_quote_end(char *str, char quote)
{
	int i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		return (i + 1);
	return (i);
}