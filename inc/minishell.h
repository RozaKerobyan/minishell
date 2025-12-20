/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerobya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:37:58 by sharteny          #+#    #+#             */
/*   Updated: 2025/12/20 19:13:12 by rkerobya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/stat.h>

# define SIGINT_FLAG_BIT    0x0100
# define HEREDOC_EXIT_BIT   0x0200    
# define EXIT_STATUS_MASK   0x00FF

extern int	g_status;

typedef enum e_type
{
	CMD,
	ARG,
	PIPE,
	TRUNC,
	APPEND,
	INPUT,
	END,
	EMPTY,
	HEREDOC,
	SPACES
}	t_type;

typedef enum e_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
}	t_status;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*type;
	char			*infile;
	char			*outfile;
	char			*heredoc_limiter;
	int				append;
	int				is_heredoc;
	int				*pipe_fd;
	int				pipe_output;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_expander
{
	int		i;
	int		j;
	char	q;
	char	*res;
}	t_expander;

typedef struct s_env
{
	char			*value;
	char			*key;
	int				flag;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini
{
	int		input;
	int		output;
	char	**env_arr;
	int		status;
	t_env	*env;
	t_cmd	*cmd;
	pid_t	pid;
	char	**history;
	int		history_count;
	int		history_capacity;
}	t_mini;

// builtins
int		echo_builtin(char **args);
int		pwd_builtin(t_mini *shell, char **args);
char	**export_builtin(char **env, char **args);
int		env_builtin(t_mini *shell);
void	unset_builtin(t_mini *shell, char **args);
int		cd_builtin(t_mini *shell, char **args);
int		exit_builtin(t_mini *shell, char **args);
int		history_builtin(t_mini *shell, char **args);

// cd_utils.c
char	*home_path(t_mini *shell);
int		check_home(t_mini *shell, char **args);
int		chdir_error(char *path);
char	*cd_display(char *str);
int		cd_change(t_mini *shell, char **args);
char	*cd_target(t_mini *shell, char **args);

// export_utils.c
int		validation(char *str);
char	**add_variable(char **env, char *var);
char	**remove_var(char **env, char *var);
int		equal_sign(char *str, int *found);
char	**export_remove(char **env, char **args, int i, int found);
void	handle_one_export(char *arg, char ***env);

// exit_utils.c
int		status_exit(char *arg, int *err_status);

// execution
int		builtins(char *cmd);
int		execute_builtins(t_mini *shell, char **args);
int		file_exist(char *path);
char	*find_cmd_path(char *cmd, t_env *env);
void	child_process(t_mini *shell, t_cmd *all, t_cmd *curr);
int		process_status(int status);
int		execute_external(t_mini *shell, t_cmd *all, t_cmd *curr);
int		execute_cmd(t_mini *shell, t_cmd *all, t_cmd *curr);
void	del_redir_args(char **args);
void	process_input(t_mini *shell, char *input);
void	check_builtins(t_mini *shell, char **args, int *status);
void	restore_std_fd(int stdin_bak, int stdout_bak);
char	*norm_find_cmp(char *cmd, char **paths);
void	child_cmd(t_mini *shell, t_cmd *curr);

// environments
char	*check_env_value(t_mini *shell, char *key);
int		reset_status(t_env *env, int status);
t_env	*env_child(t_mini *shell, char *key);
void	env_change(t_env *env, char *key, char *s, int n);
void	env_add_if_missing(t_mini *shell, char *key, char *value, int flag);
int		get_shlvl(t_mini *shell);
void	update_shlvl(t_mini *shell);
void	init_shlvl(t_mini *shell);
void	check_large_lvl(t_mini *shell);
t_env	*create_env_child(char *env);
t_env	*env_list_from_array(char **env);
char	*env_str(t_env *child);
char	**env_array_from_list(t_env *env);
char	*get_env(t_env *env, char *key);
void	sort_env_arr(char **env, int count);
char	**sorted_copy(char **env);
void	print_env_var(char *var);
void	print_sorted_env(char **sorted_env);
int		find_del_var(char **env, char **args, int i, int found);
void	update_env_both(t_mini *shell, char *key, char *value, int flag);
void	handle_append_variable(char ***env, char *arg);
int		find_var_index(char **env, char *var);
char	**replace_variable(char **env, char *var, int index);
char	**append_variable(char **env, char *var);

// utils
void	tab_free(char **tab);
char	*ft_strjoin_free(char *s1, char *s2);
char	**free_str(char **str);
long	ft_atoi_long(const char *str, int *err_status);
int		free_two(char *first_str, char *second_str);
char	*ft_itoa_long(long n);
int		msg_error(t_env *env, char *msg, char *str, int status);
void	close_fd(int *fd);
void	free_env(t_env *env);
void	del_redir_args(char **args);
int		count_args_without_redir(char **args);
int		cmd_error(char *cmd);
int		fork_error(char *cmd_path);
int		ft_strcmp(char *s1, char *s2);
void	cleanup_redir(t_mini *shell);
void	cleanup_minishell(t_mini *shell);
void	free_cmds(t_cmd *cmd);
int		ft_isspace(int c);
int		args_len(char **args);
int		check_directory(char *path);
void	minishell_error(char *cmd, char *msg);
int		export_validation(char *arg);

// lexer and parser
t_token	*token_new(char *value, t_type type);
void	token_add_back(t_token **list, t_token *new);
void	free_tokens(t_token *list);
int		set_status(int status, char *str, int i);
int		is_separator(char *str, int i);
int		save_word(t_token **tokens, char *str, int start, int i);
int		save_separator(t_token **tokens, char *str, int i, t_type type);
t_token	*tokenize_line(char *line);
t_cmd	*new_cmd(void);
void	add_arg(t_cmd *cmd, const char *value);
t_cmd	*parse_tokens(t_token *tok);
void	handle_redir(t_cmd *cur, t_token **tok);
int		is_redir(t_type t);
int		syntax_error(const char *msg, const char *token);
int		check_syntax(t_token *t);
int		handle_separator(char *str, int *i, int start, t_token **tokens);
t_token	*unexpected_eof(t_token *tokens);
void	norm(t_cmd *cur, t_token *redir_token, char *unquoted);
char	*remove_quotes_str(const char *str);
void	free_args_array(char **args, int n);

// signals
void	sigint_handler(int sig);
void	setup_signals(void);
void	setup_signals_child(void);
void	setup_signals_parent_exec(void);
int		get_exit_status(void);
void	set_exit_status(int status);

// history
void	add_shell_history(t_mini *shell, const char *line);
void	free_shell_history(t_mini *shell);

// redirections
t_type	redir_type(char *s);
int		open_input(t_mini *shell, char *filename);
int		open_output(t_mini *shell, char *filename);
int		open_append(t_mini *shell, char *filename);
int		one_redir(t_mini *shell, t_type type, char *filename);
int		redirections(t_mini *shell);
int		setup_redir(t_mini *shell, t_cmd *cmd);
int		prepare_output_files(t_cmd *cmd);
int		setup_child_redir(t_mini *shell, t_cmd *all, t_cmd *curr);

// heredoc.c
int		heredoc_line(int fd, char *limit, size_t len);
int		heredoc_write(int fd, char *limit, size_t len);
int		heredoc_read(t_mini *shell);
int		heredoc_check_exit(void);
int		heredoc(t_mini *shell, char *limit);

// pipe.c
bool	create_pipes(t_cmd *cmd);
void	close_pipe_fds(t_cmd *cmd, t_cmd *skip);
bool	set_pipe_fds(t_cmd *all, t_cmd *c);
void	init_pipe_info(t_cmd *cmd);
void	free_pipe_fd(t_cmd *cmd);
int		execute_pipeline(t_mini *shell, t_cmd *cmd);
void	close_prev_pipe(t_cmd *c);
int		wait_pipeline(t_cmd *cmd);
int		fork_pipeline(t_mini *shell, t_cmd *cmd);

// expander
void	expand_variable(char *arg, char **env, t_expander *e);
void	expander(t_cmd *cmd, char **env, int code);
char	*expand_arg(char *arg, char **env, int code);
void	expand_dollar(char *arg, char **env, int code, t_expander *e);
int		hendle_quote(char c, char *q, char *s, t_expander *e);
char	**expand_args(char **args, char **env, int code);
char	*rm_quotes(char *s);
int		is_var_char(char c);
char	*env_val(char *name, char **env);
char	*exit_code_str(int code);
char	*substr(char *s, int start, int len);
int		copy_var(char *res, int j, char *var);
int		free_old_args(char **args);
void	execute_expander(t_cmd *cmd, char **env, int code, t_mini *shell);
char	*process_arg(char *arg, char **env, int code);

#endif
