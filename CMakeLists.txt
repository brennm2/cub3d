cmake_minimum_required(VERSION 3.10)
project(cub3d C)

# Set C flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# Define paths to libraries
set(LIBFT_PATH ${CMAKE_SOURCE_DIR}/libs)
set(MLX_PATH ${CMAKE_SOURCE_DIR}/libs/minilibx-linux) # Use minilibx-linux for Linux

# Include the directories for your libraries
include_directories(${LIBFT_PATH}/includes)
include_directories(${MLX_PATH})

# Define sources
set(SOURCES
        src/main.c
        src/key_handler.c
        src/free.c
        src/map_check.c
)

# Add custom target for libft
add_custom_target(libft
        COMMAND make -C ${LIBFT_PATH}
        WORKING_DIRECTORY ${LIBFT_PATH}
        COMMENT "Building libft"
)

# Add custom target for minilibx (Linux version)
add_custom_target(mlx
        COMMAND make -C ${MLX_PATH}
        WORKING_DIRECTORY ${MLX_PATH}
        COMMENT "Building minilibx"
)

# Create the executable target
add_executable(cub3d ${SOURCES})

# Ensure cub3d depends on libft and mlx
add_dependencies(cub3d libft mlx)

# Find required OpenGL package
find_package(OpenGL REQUIRED)

# Link against libft, minilibx, and Linux libraries
target_link_libraries(cub3d
        ${LIBFT_PATH}/libft.a
        ${MLX_PATH}/libmlx.a
        ${OPENGL_LIBRARIES}
        -lXext
        -lX11
        -lm
        -lz
)
