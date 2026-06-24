#include "minishell.h"

void add_token(t_token **list, char *word, int type);
void add_list(t_token **list,t_token *token);
t_token	*ft_lstlast(t_token *lst);

void add_token(t_token **list, char *word, int type)
{
	t_token *token = malloc(sizeof(t_token));

	token -> content = ft_strdup(word);
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