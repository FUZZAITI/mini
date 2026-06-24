#include "minishell.h"

int bulit_cd(char *cd);

int bulit_cd(char *cd)
{
    if (chdir(cd) == -1)
        perror("cd");
    return (1);    
}