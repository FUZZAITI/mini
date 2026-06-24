#include "minishell.h"

int bulit_pwd();

int bulit_pwd()
{
    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return (1);
}
