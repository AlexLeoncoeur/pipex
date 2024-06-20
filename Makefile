CFILES = pipex.c pipex_utils.c

BONUS_CFILES = pipex_bonus.c pipex_utils_bonus.c ft_here_doc_bonus.c

OFILES = $(CFILES:.c=.o)
BONUS_OFILES = $(BONUS_CFILES:.c=.o)

CC = clang
NAME = pipex
CFLAGS = -Wall -Werror -Wextra

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: libft $(NAME)
$(NAME): $(OFILES)
	@ $(CC) $(CFLAGS) $(OFILES) libft/libft.a -o $(NAME)

bonus: libft $(NAME)_bonus
$(NAME)_bonus: $(BONUS_OFILES)
	@ $(CC) $(CFLAGS) $(BONUS_OFILES) libft/libft.a -o $(NAME)_bonus

libft:
	@ make -C libft/ bonus

clean:
	@ rm -f $(OFILES) $(BONUS_OFILES)
	@ make -C libft/ clean

fclean: clean
	@ rm -f $(NAME) $(NAME)_bonus
	@ make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re bonus libft