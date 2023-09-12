.PHONY: all *.c clean

SRCS	:= ${wildcard *.c}

CC	:= gcc

RM	:= rm -rf

OUT	:= a.out

RUN	:= ./a.out

CFLAGS  := -Wall -Wextra -Werror

all: ${SRCS}

${SRCS}:
	@echo "Running $@ ..."
	@${CC} ${CFLAGS} $@ -lm
	@${RUN}
	@${RM} ${OUT}
	@echo "=============================="

clean:
	${RM} ${OUT}
