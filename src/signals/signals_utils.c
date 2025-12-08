#include "minishell.h"

int     get_exit_status(void)
{
        return (g_status & EXIT_STATUS_MASK);
}

void    set_exit_status(int status)
{
        g_status = (g_status & ~EXIT_STATUS_MASK) | (status & EXIT_STATUS_MASK);
}

