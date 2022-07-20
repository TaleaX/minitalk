CC := gcc
CFLAGS := -Wall -Werror -Wextra
NAME := minitalk
SRC_CLIENT := client.c
SRC_SERVER := server.c
LDFLAGS := -L ./libft_printf/ -lft
INC := -I libft_printf/

all : server client

server :
	$(CC) $(SRC_SERVER) $(LDFLAGS) $(INC) -o $@

client :
	$(CC) $(SRC_CLIENT) $(LDFLAGS) $(INC) -o $@

clean :
	rm -rf *.o

fclean : clean
	rm -f server client

re : fclean all