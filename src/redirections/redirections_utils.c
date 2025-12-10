#include "minishell.h"

t_type	redir_type(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(s, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(s, "<", 1))
		return (INPUT);
	if (!ft_strncmp(s, ">", 1))
		return (TRUNC);
	return (0);
}

int	handle_heredoc_infile(t_mini *shell, t_cmd *cmd)
{
	if (cmd->heredoc_limiter)
	{
		if (heredoc(shell, cmd->heredoc_limiter) == -1)
		{
			if (g_status == 130)
				return (-2);
			return (-1);
		}
	}
	if (cmd->infile)
	{
		if (open_input(shell, cmd->infile) == -1)
			return (-1);
	}
	return (0);
}

int	setup_redir(t_mini *shell, t_cmd *cmd)
{
	if (!shell || !cmd)
		return (0);
	if (cmd->heredoc_limiter)
	{
		if (heredoc(shell, cmd->heredoc_limiter) == -1)
		{
			if (g_status == 130)
				return (-2);
			return (-1);
		}
	}
	if (cmd->infile)
	{
		if (open_input(shell, cmd->infile) == -1)
			return (-1);
	}
	if (cmd->outfile && !cmd->append)
	{
		if (open_output(shell, cmd->outfile) == -1)
			return (-1);
	}
	if (cmd->outfile && cmd->append)
	{
		if (open_append(shell, cmd->outfile) == -1)
			return (-1);
	}
	return (0);
}
