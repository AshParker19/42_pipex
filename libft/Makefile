#################################################################################################
###**										Makefile										**###
#####***************************************************************************************#####


###-------------------------------------------------------------------------------------------###
###**							Variables and dependencies									**###
#####---------------------------------------------------------------------------------------#####

NAME = libft.a

SRCS =	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	\
		ft_isascii.c	ft_isprint.c	ft_strlen.c		\
		ft_memset.c		ft_bzero.c		ft_memcpy.c		\
		ft_memmove.c	ft_strlcpy.c	ft_strlcat.c	\
		ft_toupper.c	ft_tolower.c	ft_strchr.c		\
		ft_strrchr.c	ft_strncmp.c	ft_memchr.c		\
		ft_memcmp.c		ft_strnstr.c	ft_atoi.c		\
		ft_calloc.c		ft_strdup.c		ft_substr.c		\
		ft_strjoin.c	ft_strtrim.c	ft_split.c		\
		ft_itoa.c		ft_strmapi.c	ft_striteri.c	\
		ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c	\
		ft_putnbr_fd.c	ft_printf.c		ft_putchar.c	\
		ft_putstr.c		ft_puthex.c		ft_putnbr.c		\
		ft_putaddress.c	get_next_line.c get_next_line_utils.c

OBJS :=$(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra

GREEN = \033[0;32m
RED = \033[0;31m
ORANGE = \033[0;33m
DEF = \033[0m

###+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++###
###**								PHONY targets and rules									**###
#####+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#####

.PHONY: all clean fclean re

$(NAME) : $(OBJS)
	@ar -crs $@ $^
	@echo "$(ORANGE)┌───────────────────────────────────────────────────┐$(DEF)"
	@echo "$(ORANGE)│                 $(GREEN)LIBFT IS COMPILED$(ORANGE)\
	                 │$(DEF)"
	@echo "$(ORANGE)└───────────────────────────────────────────────────┘$(DEF)"
	
all: $(NAME)

clean:
	@rm -f $(OBJS)

%.o : %.c
	@gcc $(CFLAGS) -c $< -o $@

fclean: clean
	@rm -f $(NAME)

re: fclean all

#####***************************************************************************************#####
###**										Thank you!										**###
#################################################################################################
