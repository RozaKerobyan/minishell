#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	free(s1);
	return (join);
}
