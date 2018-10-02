EXECUTAVEL?=basecalc

all:
	${CC} -Wall main.c -o ${EXECUTAVEL} -g

clean:
	rm ${EXECUTAVEL}

