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
CC = cc -g -O3 -ffast-math
RM = rm -rf
AR = ar -rcs

# Folders
INC_FOLDER = includes
SRC_FOLDER = src
OBJ_FOLDER = objects
LIBFT = ./libs
LIBFT_MAKE = $(MAKE) -s -C $(LIBFT)  # Use -s to suppress output
LIBS = -L./libs -lft
MLX = ./libs/minilibx-linux

# Flags
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I $(INC_FOLDER)
MAKEFLAGS = --no-print-directory
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -lXext -lX11
LDFLAGS = $(LIBS) $(MLXFLAGS) -lm -lpthread

# Conditional for macOS
ifeq ($(OS), Darwin)
    MLX = mlx_macos
    MLXFLAGS = -L ./$(MLX) -lmlx -framework OpenGL -framework AppKit -lm
endif

# Files
MANDATORY_FILES = debug_fuctions draw_wall fill_map free init key_handler map_check place_player shoot_rays
MANDATORY_FILES += texture_handler/create_texture

OBJS = $(patsubst %, $(OBJ_FOLDER)/%.o, $(MANDATORY_FILES))
MAIN_OBJ = $(OBJ_FOLDER)/main.o
NAME = cub3d

# Rules
all: $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJS) $(MAIN_OBJ)
	#@echo "[$(CYAN)Compiling MLX$(RESET)] $(GREEN)$(MLX)$(RESET)"
	@clear
	@./Asccii/creating.sh
	$(MAKE) -s -C $(MLX) > /dev/null 2>&1
	#@echo "[$(CYAN)Compiling libft$(RESET)] $(GREEN)$(LIBFT)$(RESET)"
	$(MAKE) -s -C $(LIBFT) > /dev/null 2>&1
	#@echo "[$(CYAN)Linking$(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $(NAME)
	#@echo "$(GREEN)Build complete!$(RESET)"
	@clear
	@./Asccii/completed.sh

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(dir $@)  # Ensure the directory exists
	#@echo "[$(CYAN)Compiling$(RESET)] $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_FOLDER)/main.o: main.c
	@mkdir -p $(OBJ_FOLDER)  # Ensure the directory exists
	#@echo "[$(CYAN)Compiling main.c$(RESET)] $(GREEN)$(OBJ_FOLDER)/main.o$(RESET)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c main.c -o $(OBJ_FOLDER)/main.o

re: fclean
	@$(MAKE) all

clean:
	@$(RM) $(OBJ_FOLDER) $(OBJ_FOLDER)_bonus
	@clear
	@./Asccii/object.sh


fclean: clean
	#@echo "[$(RED)Removing$(RESET)] $(GREEN)LIBFT$(RESET)"
	@$(MAKE) clean -s -C $(LIBFT) > /dev/null 2>&1
	#@echo "[$(RED)Removing$(RESET)] $(GREEN)MLX$(RESET)"
	@$(MAKE) clean -s -C $(MLX) > /dev/null 2>&1
	#@echo "[$(RED)Removing$(RESET)] $(GREEN)CUB3D$(RESET)"
	@$(RM) $(NAME)

# Custom Rules
$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

norm:
	@echo "\n\t$(BLUE)Checking norm for *.h files...$(RESET)\n"
	@norminette -R CheckDefine $(shell find . -type f -name "*.h")
	@echo "\n\t$(BLUE)Checking norm for *.c files...$(RESET)\n"
	@norminette -R checkForbiddenSourceHeader $(shell find . -type f -name "*.c")

.SILENT:
