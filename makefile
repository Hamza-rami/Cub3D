NAME = CUB3D
NAME_BNS = CUB3D_BNS

SRC = mandatory/parsing/cub.c mandatory/parsing/parse_file.c mandatory/parsing/store_map.c mandatory/parsing/check_ext.c mandatory/next_line/get_next_line.c  mandatory/next_line/get_next_line_utils.c mandatory/parsing/ft_splite.c \
		mandatory/parsing/valid_char.c mandatory/parsing/ft_atoi.c  mandatory/parsing/parse_map.c mandatory/parsing/ft_malloc.c mandatory/game/rendering.c mandatory/game/cast_ray.c mandatory//game/draw_textured_wall.c \
		mandatory/game/mlx_free.c mandatory/game/put_window.c mandatory/game/check_move.c


SRC_BNS = cub3d_bonus/parsing/cub.c cub3d_bonus/parsing/parse_file.c cub3d_bonus/next_line/get_next_line.c  cub3d_bonus/next_line/get_next_line_utils.c cub3d_bonus/parsing/ft_splite.c \
		cub3d_bonus/parsing/ft_atoi.c cub3d_bonus/parsing/ft_malloc.c  cub3d_bonus/parsing/parse_map.c cub3d_bonus/game/rendering_bonus.c cub3d_bonus/game/cast_ray_bonus.c cub3d_bonus/game/draw_textured_wall_bonus.c \
		cub3d_bonus/game/minimap_bonus.c cub3d_bonus/game/mouse_move_bonus.c cub3d_bonus/game/animation_bonus.c  cub3d_bonus/game/ft_itoa_bonus.c cub3d_bonus/game/door.c cub3d_bonus/game/check_move_bonus.c \
		cub3d_bonus/game/ft_strjoin_bonus.c cub3d_bonus/game/ft_free_mlx_bonus.c cub3d_bonus/parsing/store_map.c cub3d_bonus/parsing/valid_char.c cub3d_bonus/parsing/check_ext.c cub3d_bonus/game/put_window_bonus.c

OBJS = ${SRC:.c=.o}
OBJS_BNS = ${SRC_BNS:.c=.o}

INC =  mandatory/parsing/cub.h
INC_BNS = cub3d_bonus/parsing/cub.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf
LDFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm 
MLX_DIR = ./minilibx-linux

all: ${NAME}

%.o: %.c ${INC} ${INC_BNS}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	make -C $(MLX_DIR)
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LDFLAGS}

bonus: ${NAME_BNS}

${NAME_BNS}: ${OBJS_BNS}
	make -C $(MLX_DIR)
	${CC} ${CFLAGS} ${OBJS_BNS} -o ${NAME_BNS} ${LDFLAGS}

clean:
	${RM} ${OBJS} ${OBJS_BNS}

fclean: clean
	${RM} ${NAME} ${NAME_BNS}

re: fclean all