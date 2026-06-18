#include "minishell.h"

int bulit_pwd();
void bulit_exit();
int bulit_cd(char *cd);
int built_echo(t_cmd *cmd);
int built_env(char **envp);

int is_built_in(char *cmd)
{   
    
    if (!ft_strcmp(cmd,"echo"))
        return 1;
    else if (!ft_strcmp(cmd,"cd"))
        return 1;
    else if (!ft_strcmp(cmd,"pwd"))
        return 1;
    else if (!ft_strcmp(cmd,"export"))
        return 1;
    else if (!ft_strcmp(cmd,"unset"))
        return 1;
    else if (!ft_strcmp(cmd,"env"))
        return 1;
    else if (!ft_strcmp(cmd,"exit"))
        return 1;
    return (0);                    
}


int bulit_pwd()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return (1);
}

void bulit_exit()
{
    printf("exit\n");
    exit(0);
}

int bulit_cd(char *cd)
{
    if (chdir(cd) == -1)
        perror("cd");
    return (1);    
}

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

int built_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n",envp[i]);
        i++;
    }
    return (1);
}