LIB=libsha1.a
PRGM=sha1

CC=cc
CFLAGS=-Wall -Werror -Wextra -g

INC_DIR=inc
SRC_DIR=src
OBJ_DIR=obj

LIB_FILES=debug list parsing sha1 endian
PRGM_FILES=$(LIB_FILES) main
MAIN_FILE=$(OBJ_DIR)/main.o

LIB_SRC=$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(LIB_FILES)))
LIB_OBJ=$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIB_FILES)))

PRGM_SRC=$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(PRGM_FILES)))
PRGM_OBJ=$(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(PRGM_FILES)))

all: $(LIB)

lib: $(LIB)
program: $(PRGM)

$(LIB): $(OBJ_DIR) $(LIB_OBJ)
	ar rcs $@ $(LIB_OBJ)
$(PRGM): $(LIB) $(MAIN_FILE)
	$(CC) $(CFLAGS) $(MAIN_FILE) -L. -l$(PRGM) -o $@

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(PRGM)
	rm -f $(LIB)
