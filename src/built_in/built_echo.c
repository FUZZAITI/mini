#include "minishell.h"

int built_echo(t_cmd *cmd);

int built_echo(t_cmd *cmd)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (cmd->argv[1] && !strcmp(cmd->argv[1], "-n"))
    {
        n = 1;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if (!n)
        printf("\n");
    return (1);    
}