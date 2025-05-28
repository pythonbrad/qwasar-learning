SRC=main.c
OBJ=$(TARGET).o
TARGET=my_mastermind

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) -o ${TARGET} $(OBJ)

$(OBJ): ${SRC}
	gcc -Wall -Wextra -Werror $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all
