#include "minishell.h"

void bulit_exit();

void bulit_exit()
{
    ft_putstr_fd("exit\n",1);
    exit(0);
}