.PHONY: all *.c clean

SRCS	:= ${wildcard *.c}

CC	:= cc

RM	:= rm -rf

OUT	:= a.out

RUN	:= ./a.out

all: ${SRCS}

${SRCS}:
	@echo "Running $@ ..."
	@${CC} $@ -lm
	@${RUN}
	@${RM} ${OUT}
	@echo "=============================="

clean:
	${RM} ${OUT}
