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
#CC = cc -g
RM = rm -rf
AR = ar -rcs

# Folders
INC_FOLDER = includes
SRC_FOLDER = src
OBJ_FOLDER = objects
LIBFT = ./libs
LIBFT_MAKE = $(MAKE) -s -C $(LIBFT)  # Use -s to suppress output

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

# Files
MANDATORY_FILES += init_game/draw_wall free endgame init_game/shoot_rays init_game/fog_creator init_game/minimap init_game/door_animation init_game/door_texture_handler init_game/mouse_handler
MANDATORY_FILES += init_struct/create_texture init_struct/texture_color
MANDATORY_FILES += init_struct/file init_struct/structs init_struct/textures init_struct/map init_struct/player
MANDATORY_FILES += init_struct/textures_utils init_struct/utils init_struct/texture_color_sup init_struct/map_utils
MANDATORY_FILES += init_game/init_game init_game/move_player init_game/move_orientation init_game/key_handler init_game/intro_screen
MANDATORY_FILES += debug/debug_utils

OBJS = $(patsubst %, $(OBJ_FOLDER)/%.o, $(MANDATORY_FILES))
MAIN_OBJ = $(OBJ_FOLDER)/main.o
NAME = cub3d

# Rules
all: $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJS) $(MAIN_OBJ)
	#@clear
	@./Asccii/creating.sh
	$(MAKE) -s -C $(MLX) > /dev/null 2>&1
	$(MAKE) -s -C $(LIBFT) > /dev/null 2>&1
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $(NAME)
	#@clear
	@./Asccii/completed.sh

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(dir $@)  # Ensure the directory exists
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_FOLDER)/main.o: main.c
	@mkdir -p $(OBJ_FOLDER) # Ensure the directory exists
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o $(OBJ_FOLDER)/main.o

re: fclean
	@$(MAKE) all

clean:
	@$(MAKE) clean -s -C $(LIBFT) > /dev/null 2>&1
	@$(RM) $(OBJ_FOLDER) $(OBJ_FOLDER)_bonus
	#@clear
	@./Asccii/object.sh

fclean: clean
	@$(MAKE) fclean -s -C $(LIBFT) > /dev/null 2>&1
	@$(MAKE) clean -s -C $(MLX) > /dev/null 2>&1
	@$(RM) $(NAME)

# Custom Rules
$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

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
