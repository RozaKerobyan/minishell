#include "minishell.h"

void	sigint_handler(int sig)
{
	g_status = sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_parent_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
