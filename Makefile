NAME=sha1
CC=cc
CFLAGS=-Wall -Werror -Wextra -g

FILES= debug main list parsing

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj

SRC=$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(FILES)))
OBJ=$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(FILES)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
