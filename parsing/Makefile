NAME = cub

SRC = cub.c parse_file.c ../get_next_line/get_next_line.c  ../get_next_line/get_next_line_utils.c ft_splite.c \
		ft_atoi.c 

INC = cub.h
OBJS = ${SRC:.c=.o}
CC = cc -Wall -Werror -Wextra
RM = rm -f

all: ${NAME}
%.o: %.c ${INC}
	${CC} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all