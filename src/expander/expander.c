#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2);
char *handle_expander(char *line, t_env *env_listn, int i, int state);
char *add_char_to_str(char *dest, char carac);
char *ft_strjoin_free(char *s1, char *s2);
void	update_state(char c, int *state);

char *handle_expander(char *line, t_env *env_list, int i, int state)
{
    char    *result;
    char    *value;

    result = ft_strdup("");
    i = 0;
    state = NORMAL;
    while (line[i])
    {
	    update_state(line[i], &state);
	    if (line[i] == '$' && (state == D_QUOTE || state == NORMAL))
	    {
		    value = get_var_value(line, &i, env_list);
		    result = ft_strjoin_free(result, value);
		    free(value);
		    continue ;
	    }
	    result = add_char_to_str(result, line[i]);
	    i++;
    }
    return (result);
}

void	update_state(char c, int *state)
{
	if (c == '\'' && *state == NORMAL)
		*state = S_QUOTE;
	else if (c == '\'' && *state == S_QUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = D_QUOTE;
	else if (c == '"' && *state == D_QUOTE)
		*state = NORMAL;
}

char *add_char_to_str(char *dest, char carac)
{
    char    *result;
    int     i;

    i = 0;
    result = malloc(strlen(dest) + 2);
    if (!result)
    {
        free(dest);
        return (NULL);
    }
    while (dest[i])
    {
        result[i] = dest[i];
        i++;
    }
    result[i] = carac;
    result[i + 1] = '\0';
    free(dest);
    return (result);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char    *new_str;
    size_t  len1;
    size_t  len2;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
    {
        free(s1);
        return (NULL);
    }
    ft_memcpy(new_str, s1, len1);
    ft_memcpy(new_str + len1, s2, len2);
    new_str[len1 + len2] = '\0';
    free(s1);
    return (new_str);
}