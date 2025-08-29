NAME = cub3D

SRC = cub.c parse_file.c ../next_line/get_next_line.c  ../next_line/get_next_line_utils.c ft_splite.c \
		ft_atoi.c  parse_map.c ../game/rendering.c ../game/cast_ray.c

INC = cub.h
OBJS = ${SRC:.c=.o}
# CC = cc -Wall -Werror -Wextra #-fsanitize=address
RM = rm -f
# LDFLAGS = -lmlx -framework OpenGL -framework AppKit


MLX_DIR   = ../minilibx-linux  # Replace with actual path
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
CFLAGS    = cc -Wall -Wextra -Werror -I$(MLX_DIR)

$(NAME): $(OBJS)
	$(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

all: ${NAME}

%.o: %.c ${INC}
	${CC} -c $< -o $@

# ${NAME}: ${OBJS}
# 	${CC} ${OBJS} -o ${NAME} $(LDFLAGS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all