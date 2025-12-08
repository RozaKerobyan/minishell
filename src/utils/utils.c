#include "minishell.h"

void	close_fd(int *fd)
{
	if (!fd || *fd == -1)
	{
		return ;
	}
	close(*fd);
	*fd = -1;
}
