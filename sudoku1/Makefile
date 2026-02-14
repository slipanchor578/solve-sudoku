CC		= gcc
CFLAGS 	= -std=c11 -Wall -Wextra -march=native -pedantic-errors -fdiagnostics-color=always -g -DDEBUG
TARGET	= sudoku
SRCS	= main.c sudoku.c
OBJS	= $(SRCS:.c=.o)
HEADERS	= sudoku.h

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

run: ${TARGET}
	./${TARGET}

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: run clean
