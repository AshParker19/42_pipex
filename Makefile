NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

SRCS := srcs/here_doc.c  srcs/multipipes.c  srcs/path_and_command.c  \
		srcs/pipex.c  srcs/utils2.c  srcs/utils.c

OBJS :=$(SRCS:.c=.o)

INCLUDES = -I includes -I .

# colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

# libft
LIBFT = make -sC ./libft
LIBFT_FOLDER = ./libft

.PHONY: all clean fclean bonus re

all : $(NAME)

bonus : CFLAGS:= $(CFLAGS) -DLIMIT_ARGS=-1
bonus : $(NAME)

$(NAME): $(OBJS)
	@$(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -Llibft -lft -o $(NAME)
	@echo "$(GREEN)______ ___________ _______   __"
	@echo "| ___ \_   _| ___ \  ___\ \ / /"
	@echo "| |_/ / | | | |_/ / |__  \ V /"
	@echo "|  __/  | | |  __/|  __| /   \\"
	@echo "| |    _| |_| |   | |___/ /^\ \\"
	@echo "\_|    \___/\_|   \____/\/   \/$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -sC ./libft
	@echo "$(ORANGE)┌─────────────────────────────┐"
	@echo "│         $(GREEN)[✓]CLEANED!$(ORANGE)         │"
	@echo "$(ORANGE)└─────────────────────────────┘$(RESET)"

fclean : clean
		@rm -f $(NAME)
		@make fclean -sC ./libft

re : fclean all