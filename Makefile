.PHONY: status all * clean

SRCS	:= ${wildcard *.c}

NAME	:= ${SRCS:%.c=%}

CC	:= gcc

RM	:= rm -rf

OUT	:= a.out

RUN	:= ./a.out

STA	:= hw-status --all

SEN	:= hw-send

CFLAGS	:= -Wall -Wextra -Werror

status:
	@${STA}

all:	${SRCS}

${SRCS}:
	@echo "Running $@ ..."
	@${CC} ${CFLAGS} $@ -lm
	@${RUN}
	@${RM} ${OUT}
	@echo "=============================="

${NAME}:
	@${SEN} $@ ${@:%=%.c}

clean:
	@${RM} ${OUT}

enter:
	ssh b6510503263@adt.mikelab.net -p 59921
