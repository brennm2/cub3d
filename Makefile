OS = $(shell uname)

# Colors
RESET   = \033[0m
BLACK   = \033[1;30m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
PURPLE  = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

# Commands
CC = cc -g -Ofast -ffast-math -finline-functions -march=native -flto
RM = rm -rf
AR = ar -rcs

# Folders
INC_FOLDER = includes
INC_FOLDER_BONUS = includes_bonus
SRC_FOLDER = src
SRC_FOLDER_BONUS = src_bonus
OBJ_FOLDER = objects
OBJ_FOLDER_BONUS = objects_bonus
LIBFT = ./libs
LIBFT_MAKE = $(MAKE) -s -C $(LIBFT)

# System-specific settings
ifeq ($(OS), Darwin)
    MLX = ./libs/minilibx-mac
    MLXFLAGS = -L ./$(MLX) -lmlx -framework OpenGL -framework AppKit -lm
else
    MLX = ./libs/minilibx-linux
    MLXFLAGS = -L $(MLX) -lm -lmlx -lXext -lX11
endif

LIBS = -L./libs -lft
LDFLAGS = $(LIBS) $(MLXFLAGS) -lm -lpthread

# Files for Mandatory
MANDATORY_FILES += init_game/draw_wall free endgame init_game/shoot_rays init_game/fog_creator
MANDATORY_FILES += init_struct/create_texture init_struct/texture_color
MANDATORY_FILES += init_struct/file init_struct/structs init_struct/textures init_struct/map init_struct/player
MANDATORY_FILES += init_struct/textures_utils init_struct/utils init_struct/map_utils
MANDATORY_FILES += init_game/init_game init_game/move_player init_game/move_orientation

BONUS_FILES += init_game/draw_wall_bonus free_bonus endgame_bonus init_game/shoot_rays_bonus init_game/fog_creator_bonus  init_game/door_texture_handler_bonus init_game/mouse_handler_bonus
BONUS_FILES += init_struct/create_texture_bonus init_struct/texture_color_bonus init_game/door_animation_bonus
BONUS_FILES += init_struct/file_bonus init_struct/structs_bonus init_struct/textures_bonus init_struct/map_bonus init_struct/player_bonus
BONUS_FILES += init_struct/textures_utils_bonus init_struct/utils_bonus init_struct/texture_color_sup_bonus init_struct/map_utils_bonus
BONUS_FILES += init_game/init_game_bonus init_game/move_player_bonus init_game/move_orientation_bonus init_game/key_handler_bonus init_game/intro_screen_bonus init_game/minimap_bonus

# Object files
OBJS = $(patsubst %, $(OBJ_FOLDER)/%.o, $(MANDATORY_FILES))
OBJS_BONUS = $(patsubst %, $(OBJ_FOLDER_BONUS)/%.o, $(BONUS_FILES))
MAIN_OBJ = $(OBJ_FOLDER)/main.o
MAIN_OBJ_BONUS = $(OBJ_FOLDER_BONUS)/main_bonus.o # Adjust this if there's a different main for bonus
NAME = cub3d
NAME_BONUS = cub3d_bonus

# Compilation flags for normal and bonus
CFLAGS = -I$(INC_FOLDER) -Wall -Wextra -Werror
CFLAGS_BONUS = -I$(INC_FOLDER_BONUS) -Wall -Wextra -Werror

# Rules
all: $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJS) $(MAIN_OBJ)
	@./Asccii/creating.sh
	$(MAKE) -s -C $(MLX) > /dev/null 2>&1
	$(MAKE) -s -C $(LIBFT) > /dev/null 2>&1
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $(NAME)
	@./Asccii/completed.sh

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(dir $@)  # Ensure the directory exists
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_FOLDER)/main.o: main.c
	@mkdir -p $(OBJ_FOLDER) # Ensure the directory exists
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o $(OBJ_FOLDER)/main.o

# Bonus rule
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_FOLDER_BONUS) $(OBJS_BONUS) $(MAIN_OBJ_BONUS)
	@./Asccii/creating.sh
	$(MAKE) -s -C $(MLX) > /dev/null 2>&1
	$(MAKE) -s -C $(LIBFT) > /dev/null 2>&1
	$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) $(MAIN_OBJ_BONUS) $(LDFLAGS) -o $(NAME_BONUS)
	@./Asccii/completed.sh

$(OBJ_FOLDER_BONUS)/%.o: $(SRC_FOLDER_BONUS)/%.c
	@mkdir -p $(dir $@)  # Ensure the directory exists
	$(CC) $(CFLAGS_BONUS) $(CPPFLAGS) -c $< -o $@

$(OBJ_FOLDER_BONUS)/main_bonus.o: main_bonus.c
	@mkdir -p $(OBJ_FOLDER_BONUS) # Ensure the directory exists
	$(CC) $(CFLAGS_BONUS) $(CPPFLAGS) -c main_bonus.c -o $(OBJ_FOLDER_BONUS)/main_bonus.o

re: fclean
	@$(MAKE) all

clean:
	@$(MAKE) clean -s -C $(LIBFT) > /dev/null 2>&1
	@$(RM) $(OBJ_FOLDER) $(OBJ_FOLDER_BONUS)
	@./Asccii/object.sh

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT) > /dev/null 2>&1
	@$(MAKE) clean -s -C $(MLX) > /dev/null 2>&1
	@$(RM) $(NAME) $(NAME_BONUS)

# Custom Rules
$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

$(OBJ_FOLDER_BONUS):
	mkdir -p $(OBJ_FOLDER_BONUS)

norm:
	@echo "\n\t$(BLUE)Checking norm for *.h files...$(RESET)\n"
	@norminette $(shell find . -type f -name "*.h" -not -path "./libs/minilibx-linux/*" -not -path "./libs/minilibx-mac/*")
	@echo "\n\t$(BLUE)Checking norm for *.c files...$(RESET)\n"
	@norminette $(shell find . -type f -name "*.c" -not -path "./libs/minilibx-linux/*" -not -path "./libs/minilibx-mac/*")

update:
	@wget https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
	@tar -xzf minilibx-linux.tgz -C libs
	@rm minilibx-linux.tgz

.SILENT:
