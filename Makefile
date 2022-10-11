CC := gcc -g
CFLAGS := -Wall -Wextra -Werror
NAME := client
NAME_SERVER := server
SRC_CLIENT := client.c
SRC_SERVER := server.c
LIB_DIR := libft_printf/
LIBFT := $(LIB_DIR)libft.a
LDFLAGS := -L ./libft_printf/ -lft
INC := -I libft_printf/

all : $(NAME) $(NAME_SERVER)

$(NAME_SERVER) : $(SRC_SERVER)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(LDFLAGS) $(INC) -o $@

$(NAME) : $(SRC_CLIENT)
	$(CC) $(CFLAGS) $(SRC_CLIENT) $(LDFLAGS) $(INC) -o $@

$(LIBFT) :
	make -C $(LIB_DIR)
	
clean :
	rm -rf *.o

fclean : clean
	rm -f server client

re : fclean all