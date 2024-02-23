NAME = minishell
SRC =	EXTRA_UTILS/utils.c EXTRA_UTILS/utils2.c EXTRA_UTILS/gnl.c\
 		ENV/env_get.c ENV/path_get.c ENV/env_operations.c ENV/export_operations.c\
		LEXER/lexer.c LEXER/lexer_metachars.c LEXER/lexer_operations.c LEXER/lexer_add.c\
		EXPANDER/expander.c EXPANDER/expander_operations.c EXPANDER/expander_controls.c EXPANDER/expander_utils.c\
		PARSER/parser_operations.c PARSER/heredoc.c PARSER/parser.c PARSER/parser_init.c PARSER/file_operations.c PARSER/file_inits.c\
		EXECUTER/executer.c EXECUTER/export_cmd.c EXECUTER/export_cmd2.c EXECUTER/echo_cmd.c EXECUTER/execute_utils.c\
		EXECUTER/builtins.c EXECUTER/cd_cmd.c EXECUTER/cd_cmd2.c EXECUTER/pwd_cmd.c EXECUTER/fd_utils.c \
		MAIN/errors.c MAIN/signal_init.c MAIN/main.c
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBFT = INCLUDES/libft/libft.a
READLINE = readline
OBJ = $(SRC:.c=.o)

RESET=\033[0m
RED=\033[31m
LIGHT_RED=\033[91m
GREEN=\033[32m
LIGHT_GREEN=\033[92m
YELLOW=\033[33m
LIGHT_YELLOW=\033[93m
BLUE=\033[34m
LIGHT_BLUE=\033[94m
MAGENTA=\033[35m
LIGHT_MAGENTA=\033[95m
CYAN=\033[36m
LIGHT_CYAN=\033[96m
WHITE=\033[37m
GREY=\033[90m
LIGHT_GREY=\033[37m

all : $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	@clear
	@echo "$(YELLOW)Compailing readline please wait$(GREEN)"
	@curl -s -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf readline-8.2.tar.gz 2>&1 | awk '{printf "."; fflush()}'
	@cd readline-8.2 && ./configure --prefix=${PWD}/readline 2>&1 | awk '{printf "."; fflush()}'
	@cd readline-8.2 && make install 2>&1 | awk '{printf "."; fflush()}'
	@echo "$(RESET)"
	


$(LIBFT):
	@echo "$(YELLOW)Compailing include please wait$(GREEN)"
	@make -C INCLUDES/libft | awk '{printf "."; fflush()}'
	@make bonus -C INCLUDES/libft | awk '{printf "."; fflush()}'
	@echo ""
	@echo "$(YELLOW)Compailing main proje please wait$(GREEN)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/readline/include/
	@echo "$(GREEN).$(RESET)" | tr -d '\n'

$(NAME): $(SRC) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(SRC) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline -o $(NAME)
	@echo "Minishell Compailed"
	@echo "$(RESET)"
	@clear
	@echo "$(LIGHT_RED) ███▄ ▄███▓    ██▓    ███▄    █     ██▓     ██████     ██░ ██    ▓█████     ██▓        ██▓    ";
	@echo "▓██▒▀█▀ ██▒   ▓██▒    ██ ▀█   █    ▓██▒   ▒██    ▒    ▓██░ ██▒   ▓█   ▀    ▓██▒       ▓██▒    ";
	@echo "▓██    ▓██░   ▒██▒   ▓██  ▀█ ██▒   ▒██▒   ░ ▓██▄      ▒██▀▀██░   ▒███      ▒██░       ▒██░    ";
	@echo "▒██    ▒██    ░██░   ▓██▒  ▐▌██▒   ░██░     ▒   ██▒   ░▓█ ░██    ▒▓█  ▄    ▒██░       ▒██░    ";
	@echo "▒██▒   ░██▒   ░██░   ▒██░   ▓██░   ░██░   ▒██████▒▒   ░▓█▒░██▓   ░▒████▒   ░██████▒   ░██████▒";
	@echo "░ ▒░   ░  ░   ░▓     ░ ▒░   ▒ ▒    ░▓     ▒ ▒▓▒ ▒ ░    ▒ ░░▒░▒   ░░ ▒░ ░   ░ ▒░▓  ░   ░ ▒░▓  ░";
	@echo "░  ░      ░    ▒ ░   ░ ░░   ░ ▒░    ▒ ░   ░ ░▒  ░ ░    ▒ ░▒░ ░    ░ ░  ░   ░ ░ ▒  ░   ░ ░ ▒  ░";
	@echo "░      ░       ▒ ░      ░   ░ ░     ▒ ░   ░  ░  ░      ░  ░░ ░      ░        ░ ░        ░ ░   ";
	@echo "       ░       ░              ░     ░           ░      ░  ░  ░      ░  ░       ░  ░       ░  ░";
	@echo "                                                                                              ";
	@echo "			    	   						$(BLUE) by acan & uarslan$(RESET)";
	@echo "                                                  												";

clean:
	@clear
	@$(RM) $(OBJ)
	@make -C INCLUDES/libft clean
	@echo "$(CYAN)Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make -C INCLUDES/libft fclean
	@rm -rf readline
	@rm -rf readline-8.2 readline-8.2.tar.gz
	@echo "$(CYAN)Readline files removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re