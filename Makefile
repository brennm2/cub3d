MAKEFLAGS += -s

NAME = cub3D

LIBFT = ./libs/libft.a
MINILIBX = ./libs/minilibx-linux/libmlx_Linux.a

CC = cc -g -O3 -ffast-math
CCFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
RM = rm
RMFLAGS= -f
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[1;93m
NC=\033[0m


SRC = main.c \
	src/key_handler.c \
	src/free.c \
	src/map_handler/fill_map.c \
	src/debug/debug_fuctions.c \
	src/raycasting/shoot_rays.c \
	src/raycasting/draw_wall.c \
	src/player/place_player.c \
	src/init.c \
	src/map_check.c \
	src/texture_handler/create_texture.c\
	#src/map_check.c

OBJ_DIR = obj
LIBFT   = libs
LIBFT_LIB = $(LIBFT)/libft.a

#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                        FILES                                              ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

NAME    = cub3d

_FILES  += debug_fuctions.c draw_wall.c fill_map.c shoot_rays.c free.c init.c key_handler.c main.c map_check.c place_player.c
SRC     = $(addprefix $(SRC_DIR)/, $(_FILES))
OBJ     = $(addprefix $(OBJ_DIR)/, $(_FILES:%.c=%.o))

#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                     CONDITIONALS                                          ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

ifeq ($(OS), Darwin)
	MLX = minilibx-mac
	MLXFLAGS = -L ./$(MLX) -lmlx -framework OpenGL -framework AppKit -lm
endif

#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                         RULES                                             ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	@make -C $(MLX) > /dev/null 2>&1
	@echo "[$(CYAN)Linking$(RESET)] $(GREEN)$(NAME)$(RESET)"
	@$(CC) -L $(MLX) $(CFLAGS) $^ -o $@ $(MLXFLAGS)
	@echo "$(GREEN)Done.$(RESET)"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@echo "[$(RED)Deleted$(RESET)] $(GREEN)$(OBJ_DIR)/*.o$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@echo "[$(RED)Deleted$(RESET)] $(GREEN)$(NAME)$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT: