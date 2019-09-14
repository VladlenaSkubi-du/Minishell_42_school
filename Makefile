NAME = minishell

FLAGS = -g

SOURCES =	main.c \
			readline.c \
			cmd_readline_changes.c \
			commands_check.c \
			cmd_echo.c \
			cmd_exit_cd.c \
			cmd_env_set_unset.c \
			special_signs.c \
			other_functions_1.c \
			other_functions_2.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME):		text $(OBJS)
				@make -C ./libft
				@gcc $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a
				@echo "\x1b[32;01mYour minishell is ready\x1b[0m"

text:
				@echo "\x1b[32;01mCompiling your minishell...\x1b[0m"

$(OBJS):		$(DIR_O)/%.o: $(DIR_S)/%.c includes/minishell.h
				@mkdir -p $(DIR_O)
				gcc $(FLAGS) -c -I includes -o $@ $<
clean:
				@echo "\033[34mDeliting minishell o-files\033[0m"
				@/bin/rm -Rf $(DIR_O)
				@make clean --directory ./libft

fclean: clean
				@echo "\033[34mDeliting minishell binary\033[0m"
				@/bin/rm -f $(NAME)
				@make fclean --directory ./libft

re:		fclean all
