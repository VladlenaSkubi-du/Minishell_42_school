NAME = minishell

FLAGS = -Wall -Wextra -Werror

SOURCES =	main.c \
			readline.c \
			auto_completion.c \
			cmd_readline_changes.c \
			commands_check.c \
			special_signs.c \
			cmd_line_modification.c \
			cmd_echo.c \
			cmd_exit_cd_env.c \
			cmd_setenv_unset.c \
			cmd_nonbuiltin_processing.c \
			other_functions_1.c \
			other_functions_2.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@gcc $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a
	@echo "\x1b[32;01mYour minishell is ready\x1b[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c includes/minishell.h
	@mkdir -p $(DIR_O)
	@gcc $(FLAGS) -c -I includes -I libft/includes -o $@ $<

clean:
	@echo "\033[34mDeleting minishell o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\033[34mDeleting minishell binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all

.PHONY: all $(NAME) clean fclean re
