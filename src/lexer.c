#include "minishell.h"

t_token *lexer(char *input); 
int handle_word(t_token **tokens, char *str);
int handle_infile(t_token **tokens, char *str);
int handle_infile(t_token **tokens, char *str);
int handle_outfile(t_token **tokens, char *str);
int find_quote_end(char *str, char quote);



t_token *lexer(char *input) 
{
	int i = 0;
	t_token *tokens = NULL;

	while (input[i]) 
	{
		while (input[i] && (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13)))
			i++; 
		if (!input[i]) break;

		if (input[i] == '|')
		{
			add_token(&tokens, "|", 1);
			i++;
		}
		else if (input[i] == '>')
			i += handle_infile(&tokens, &input[i]);
		else if (input[i] == '<')
			i += handle_outfile(&tokens, &input[i]);	
		else
			i += handle_word(&tokens, &input[i]);
	}
	return (tokens);
}

int handle_word(t_token **tokens, char *str)
{
	int i = 0;
	int start = 0;
	char *word;

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

void print_tokens(t_token *list)
{
	if (!list)
	{
		printf("Lista vazia!\n");
		return;
	}
	while (list != NULL)
	{
		printf("%i = ",list -> type);
		printf("%s\n",list -> content );
		list = list->next; 
	}
}