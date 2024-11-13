NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
READLINE = -lreadline

FILES = $(shell find . -type f -name '*.c')

OBJ = $(FILES:.c=.o)

GREEN = \033[0;32m
ORANGE = \033[0;33m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(READLINE) -o $(NAME) >/dev/null
	@echo "$(ORANGE)Linking $(NAME)...$(NC)"

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -g -o $@ >/dev/null
	@echo "$(GREEN)Compiling $<$(NC)"

clean:
	@rm -rf $(OBJ)
	@echo "$(RED)Cleaning objects...$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)Cleaning $(NAME)...$(NC)"

re: fclean all

.PHONY: all clean fclean re
