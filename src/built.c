#include "minishell.h"

int bulit_pwd();
void bulit_exit();
int bulit_cd(char *cd);
int built_echo(t_cmd *cmd);
int built_env(char **envp);

int is_built_in(t_cmd *cmd, char **envp)
{   
    char *comando;

    comando = cmd->argv[0];
    if (!ft_strcmp(comando,"echo"))
        return (built_echo(cmd));
    else if (!ft_strcmp(comando,"cd"))
        return bulit_cd(cmd->argv[1]);
    else if (!ft_strcmp(comando,"pwd"))
        return (bulit_pwd());
    else if (!ft_strcmp(comando,"export"))
        return 1;
    else if (!ft_strcmp(comando,"unset"))
        return 1;
    else if (!ft_strcmp(comando,"env"))
        return (built_env(envp));
    else if (!ft_strcmp(comando,"exit"))
        bulit_exit();
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