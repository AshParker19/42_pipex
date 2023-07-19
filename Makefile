NAME = pipex

CC = cc

CFLAGS = -g
#!!! DON'T FORGET FREAKING FLAGS !!!

SRCS := $(wildcard *.c)

OBJS :=$(SRCS:.c=.o)

# colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "$(GREEN)♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖"
	@echo "$(GREEN)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(BLUE)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(BLUE)♜ ♞ ♝ ♚ ♛ ♝ ♞ ♜"
	@rm -rf $(OBJS) # !!! remove this shit !!!

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "$(ORANGE)┌────────────────────────────────────────────────────────────────────────┐"
	@echo "│                              $(GREEN)[✓] CLEANED!$(ORANGE)                              │"
	@echo "$(ORANGE)└────────────────────────────────────────────────────────────────────────┘$(RESET)"

fclean : clean
		@rm -f $(NAME)