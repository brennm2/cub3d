#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                        COLORS                                             ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

RESET   = \033[0m
BLACK   = \033[1;30m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
PURPLE  = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                       COMMANDS                                            ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

CC      = cc
RM      = rm -rf
AR      = ar -rcs

#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                         FLAGS                                             ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

CFLAGS  = -Wall -Wextra -Werror
MLXFLAGS = -L ./libs/minilibx-linux -lmlx -lXext -lX11 -Imlx_linux
X11_FLAGS = -L/usr/X11/lib -Lmlx -L/usr/lib
MLX = libs/minilibx-linux


#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#
#·                                                                                           ·#
#·                                        FOLDERS                                            ·#
#·                                                                                           ·#
#· · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · · ·#

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
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