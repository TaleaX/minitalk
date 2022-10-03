CC := gcc -g
CFLAGS := -Wall -Wextra #-Werror
NAME := minitalk
SRC_CLIENT := client.c
SRC_SERVER := server.c
LDFLAGS := -L ./libft_printf/ -lft
INC := -I libft_printf/

all : server client

server : $(SRC_SERVER)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(LDFLAGS) $(INC) -o $@

client : $(SRC_CLIENT)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(LDFLAGS) $(INC) -o $@

clean :
	rm -rf *.o

fclean : clean
	rm -f server client

re : fclean all