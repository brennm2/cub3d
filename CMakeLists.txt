cmake_minimum_required(VERSION 3.10)
project(cub3d C)

# Set C flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# Include the directories for your libraries
include_directories(${CMAKE_SOURCE_DIR}/libs/includes)
include_directories(${CMAKE_SOURCE_DIR}/libs/minilibx-mac)

# Link libraries
target_link_libraries(cub3d ${CMAKE_SOURCE_DIR}/libs/libft.a ${CMAKE_SOURCE_DIR}/libs/minilibx-mac/libmlx.a)


# Define sources
set(SOURCES
        src/main.c
        src/key_handler.c
        src/free.c
        src/map_check.c
)

# Include directories
include_directories(${LIBFT_PATH})
include_directories(${MLX_PATH})

# Create executable
add_executable(cub3d ${SOURCES})

# Link directories
link_directories(${LIBFT_PATH})
link_directories(${MLX_PATH})

# Link against libft, minilibx, and macOS frameworks
target_link_libraries(cub3d ${LIBFT_PATH}/libft.a ${MLX_PATH}/libmlx.a "-framework OpenGL" "-framework AppKit" "-lm")
