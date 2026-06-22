#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2);
void pre_expander(t_token *list, t_env *env_list);
char *handle_expander(char *line, t_env *env_listn, int i, int state);
char *get_var_value(char *line, int *i, t_env *env_list);
char *add_char_to_str(char *dest, char carac);
char *ft_strjoin_free(char *s1, char *s2);



void pre_expander(t_token *list, t_env *env_list)
{
    char *expanded;
    int i;
    int state;

    while (list != NULL)
    {
        if (list->type == WORD)
        {   
            expanded = handle_expander(list->content, env_list, i, state);
            free(list->content);
            list->content = expanded;
        }
        list = list->next;
    }
}

char *handle_expander(char *line, t_env *env_list, int i, int state)
{
    char    *result;
    char    *value;

    result = ft_strdup("");
    i = 0;
    state = NORMAL;
    while (line[i])
    {   
        if (line[i] == '\'' && state == NORMAL)
            state = S_QUOTE;
        else if (line[i] == '\'' && state == S_QUOTE)
            state = NORMAL;
        else if (line[i] == '"' && state == NORMAL)
            state = D_QUOTE;
        else if (line[i] == '"' && state == D_QUOTE)
            state = NORMAL;
        else if (line[i] == '$' && (state == D_QUOTE || state == NORMAL))
        {   
            value = get_var_value(line, &i, env_list);
            result = ft_strjoin_free(result, value);
            free(value);
            continue;
        }
        result = add_char_to_str(result, line[i]);
        i++;
    }
    return (result);
}

char *get_var_value(char *line, int *i, t_env *env_list)
{
    int     start;
    char    *var_name;
    char    *value;

    (*i)++;
    if (line[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(g_exit_status));
    }
    if (!line[*i] || (!ft_isalpha(line[*i]) && line[*i] != '_'))
        return (ft_strdup("$"));
    start = *i;
    while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
        (*i)++;
    var_name = ft_substr(line, start, *i - start);
    value = get_env_value(var_name, env_list);
    free(var_name);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
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