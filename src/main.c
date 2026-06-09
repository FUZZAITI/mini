#include "minishell.h"


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
	add_token(tokens, word, "WORD");
	free(word);
	return (i);
}

int handle_redirect(t_token **tokens, char *str)
{
  int i;
  char *word;
  
  i = 0;
  if (str[i] == '>' && str[i + 1] == '>')
  {
	word = strndup(str, (i + 2));
	add_token(tokens, word, "APPEND");
	return (2);
  }
  else if (str[i] == '<' && str[i + 1] == '<')
  {
	word = strndup(str, (i + 2));
	add_token(tokens, word, "HEREDOC");
	return (2);
  }
  else if (str[i] == '>')
  {
	word = strndup(str, (i + 1));
	add_token(tokens, word, "REDIR_OUT");
  }
  else if (str[i] == '<')
  {
	word = strndup(str, (i + 1));
	add_token(tokens, word, "REDIR_IN");
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
	printf("%s = ",list -> type);
	printf("%s\n",list -> content );
	list = list->next; 
  }
}

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
			add_token(&tokens, "|", "PIPE");
			i++;
		}
		else if (input[i] == '>' || input[i] == '<')
			i += handle_redirect(&tokens, &input[i]);
		else
			i += handle_word(&tokens, &input[i]);
	}
	return (tokens);
}

///////////////////////////////////////////////////////////////////////////////////

void add_token(t_token **list, char *word, char *type)
{
  t_token *token = malloc(sizeof(t_token));

  token -> content = strdup(word);
  token -> type = type;
  token -> next = NULL;
  add_list(list, token);
}

void add_list(t_token **list,t_token *token)
{
  t_token *last;

  if (!token) 
		return;
  if (*list == NULL)
  {
	*list = token;
	return;
  }
  last = ft_lstlast(*list);
  last -> next = token;
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

///////////////////////////////////////////////////////////////////////////////////

int is_redir(char *type)
{
  return (!strcmp(type, "REDIR_IN") || !strcmp(type, "REDIR_OUT") || !strcmp(type, "APPEND") || !strcmp(type, "HEREDOC"));
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
  if (!strcmp(tok->type,"PIPE"))
		return (printf("syntax error near '|'\n"), 0);
  while (tok)
  {
	if (!strcmp(tok->type,"PIPE") && tok->next == NULL)
	  return (printf("syntax error near '|'\n"), 0);
	if (!strcmp(tok->type,"PIPE") && tok->next && (!strcmp(tok->next->type,"PIPE")))
	  return (printf("syntax error near '|'\n"), 0);
	if (is_redir(tok->type))
	{
	  if (!tok->next)
			return (printf("syntax error near newline\n"), 0);
	  if ((strcmp(tok->next->type,"WORD")))
			return (printf("syntax error\n"), 0);
	}
	tok = tok->next;
  }
  return (1);
}

//////////////////////////////////////////////////////////////////////////////////////

void remove_quotes_tokens(t_token *lst)
{
	char *tmp;

	while (lst)
	{
		if (!strcmp(lst->type, "WORD"))
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

/////////////////////////////////////////////////////////////////////////////////////

t_cmd *parse(t_token *tok)
{
  t_cmd *head;
  t_cmd *cmd;

  head = new_cmd();
  cmd = head;
	while (tok)
  {
    if (tok->type == PIPE)
    {
      cmd->next = new_cmd();
      cmd = cmd->next;
    }
    else if (tok->type == WORD)
    {
            // adiciona no argv
    }
    else if (is_redir(tok->type))
    {
            // trata redirecionamento
    }
    tok = tok->next;
  }
  return (head);
}

void add_arg(t_cmd cmd, char *str)
{
	char **args
}

t_cmd *new_cmd(void)
{
  t_cmd *cmd;

  cmd = malloc(sizeof(t_cmd));
  cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = NULL;
	cmd->next = NULL;
  return (cmd);
}

////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[], char *envp[])
{
  char        *line;
  t_token     *tokens_list;
  t_env       *env;

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
		}
		free(line);
	}
}




