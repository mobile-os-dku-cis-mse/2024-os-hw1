NAME	=	SiSH

SRCDIR	=	src

SRC		=	$(SRCDIR)/main.c				\
			$(SRCDIR)/execute_command.c		\
			$(SRCDIR)/getenv.c				\

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

debug:	CFLAGS += -g
debug:	re