NAME	= duckHunt

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -I includes -std=c99

LDFLAGS	= -lmlx -lXext -lX11

SRC	= src/main.c \
	  src/remote.c \
	  src/game.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
