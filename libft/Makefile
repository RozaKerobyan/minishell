NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MANDATORY = ft_isalpha.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
            ft_isascii.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c \
			ft_atoi.c ft_isdigit.c ft_memset.c ft_strchr.c ft_strlen.c \
		   	ft_substr.c ft_bzero.c ft_isprint.c ft_putchar_fd.c ft_strdup.c \
		   	ft_strmapi.c ft_tolower.c ft_calloc.c ft_memchr.c ft_putendl_fd.c \
			ft_striteri.c ft_strncmp.c ft_toupper.c ft_isalnum.c ft_memcmp.c \
		   	ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c ft_itoa.c    
BONUS = 	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
MANDATORY_OBJS = $(MANDATORY:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
ARRCS = ar -rcs

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(ARRCS) $(NAME) $(MANDATORY_OBJS)

%.o: %.c libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	$(ARRCS) $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
