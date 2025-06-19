SRC_FOLDER = 	./src

SRC = 			main.c

OBJ_FOLDER = 	obj

OBJ = 			$(patsubst %.c,$(OBJ_FOLDER)/%.o,$(SRC))

CC =			gcc
FLAGS =			-g -Wall -Wextra -Werror
INC =			./inc
LIBFT = 		./libft

NAME =			book_library

all: $(NAME)
	# ./book_library

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) libft.a

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c | $(OBJ_FOLDER)
	$(CC) $(FLAGS) -c -I$(INC) $< -o $@

$(OBJ_FOLDER): libft
	mkdir -p $(OBJ_FOLDER)

libft:
	make -C $(LIBFT)
	cp $(LIBFT)/libft.a .

clean:
	rm -rf $(OBJ_FOLDER)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -rf libft.a
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft