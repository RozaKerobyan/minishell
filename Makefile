NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src/
INC_DIR = ./inc/
OBJ_DIR = ./obj/
LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC = \
	builtins/cd.c \
	builtins/cd_utils.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/export_utils.c \
	builtins/pwd.c \
	builtins/history.c \
	builtins/unset.c \
	environment/env_utils.c \
	environment/env_utils2.c \
	environment/env_utils3.c \
	environment/shlvl.c \
	environment/env_sort.c \
	execution/builtins.c \
	execution/execute_cmd.c \
	execution/process.c \
	execution/process_input.c \
	execution/pipe.c \
	execution/pipeline.c \
	expansion/expand.c \
	expansion/expander.c \
	expansion/utils.c \
	heredoc/heredoc.c \
	heredoc/heredoc_utils.c \
	lexer/tokenization.c \
	lexer/tokenization_utils.c \
	main/minishell.c \
	parser/parsing.c \
	parser/pars_utils.c \
	redirections/redirections.c \
	signals/signals.c \
	signals/signals_utils.c \
	utils/args_utils.c \
	utils/error.c \
	utils/free.c \
	utils/free2.c \
	utils/ft_atoi_long.c \
	utils/ft_itoa_long.c \
	utils/ft_strcmp.c \
	utils/ft_isspace.c \
	utils/utils.c

OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
INC = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LIBFT) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
