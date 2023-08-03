NAME = pipex

CC = cc

CFLAGS = -g #-fsanitize=address
#TODO:FIXME:!!! DON'T FORGET FREAKING FLAGS !!!FIXME:TODO:

SRCS := $(wildcard *.c) #TODO: 

OBJS :=$(SRCS:.c=.o)

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

.PHONY: all clean fclean norm bonus re

all : $(NAME)

bonus : CFLAGS:= $(CFLAGS) -DLIMIT_ARGS=-1
bonus : $(NAME)

$(NAME): $(OBJS)
	@$(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)
	@echo "$(GREEN)♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖"
	@echo "$(GREEN)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(BLUE)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(BLUE)♜ ♞ ♝ ♚ ♛ ♝ ♞ ♜$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -sC ./libft
	@echo "$(ORANGE)┌────────────────────────────────────────────────────────────────────────┐"
	@echo "│                              $(GREEN)[✓] CLEANED!$(ORANGE)                              │"
	@echo "$(ORANGE)└────────────────────────────────────────────────────────────────────────┘$(RESET)"

fclean : clean
		@rm -f $(NAME)
		@make fclean -sC ./libft

re : fclean all