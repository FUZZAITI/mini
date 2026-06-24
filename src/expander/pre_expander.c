#include "minishell.h"

void pre_expander(t_token *list, t_env *env_list);
char *get_var_value(char *line, int *i, t_env *env_list);

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