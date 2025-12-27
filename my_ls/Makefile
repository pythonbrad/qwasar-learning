SRC=my_ls.c
OBJ=my_ls.o
TARGET=my_ls

all: $(TARGET)

${TARGET}: $(OBJ)
	gcc ${CFLAGS} -o ${TARGET} ${OBJ}

${OBJ}:
	gcc -Wall -Werror -Wextra -o ${OBJ} -c ${SRC}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${TARGET}

re: fclean all

.gitignore:
	printf "${OBJ}\n${TARGET}" > .gitignore
