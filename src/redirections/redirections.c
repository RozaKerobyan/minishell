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

int	open_input(t_mini *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(filename), -1);
	close_fd(&(shell->input));
	shell->input = fd;
	return (0);
}

int     open_output(t_mini *shell, char *filename)
{
        int     fd;

        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
                return (perror(filename), -1);
        close_fd(&(shell->output));
        shell->output = fd;
        return (0);
}

int     open_append(t_mini *shell, char *filename)
{
        int     fd;

        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
                return (perror(filename), -1);
        close_fd(&(shell->output));
        shell->output = fd;
        return (0);
}

int	one_redir(t_mini *shell, t_type type, char *filename)
{
	if (type == INPUT)
		return (open_input(shell, filename));
	if (type == TRUNC)
		return (open_output(shell, filename));
	if (type == APPEND)
		return (open_append(shell, filename));
	if (type == HEREDOC)
		return (heredoc(shell, filename));
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
			if (g_status == SIGINT)
				return (-2);
			return (-1);
		}
	}
	if (cmd->infile)
	{
		if (open_input(shell, cmd->infile) == -1)
			return (-1);
	}
	if (cmd->outfile)
	{
	    	if (cmd->append)
        	{
			if (open_append(shell, cmd->outfile) == -1)
				return (-1);
		}
		else
		{
			if (open_output(shell, cmd->outfile) == -1)
				return (-1);
        	}
	} 
	return (0);
}

int	redirections(t_mini *shell)
{
	if (!shell)
		return (0);
	if (shell->input != -1)
	{
		if (dup2(shell->input, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close_fd(&(shell->input));
	}
	if (shell->output != -1)
	{
		if (dup2(shell->output, STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		close_fd(&(shell->output));
	}
	return (0);
}
