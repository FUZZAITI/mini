#include "minishell.h"

t_token *lexer(char *input); 

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