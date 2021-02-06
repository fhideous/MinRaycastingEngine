cmake_minimum_required(VERSION 3.17)
project(cub3d C)
set(CMAKE_C_STANDARD 99)

#set(SOURCE_DIR /Users/fhideous/Desktop/fhideous/test_printf_final_plz/libft/libft.a)
set(SOURCE_DIR /Users/fhideous/Desktop/fhideous/cub3d/minilibx_opengl_20191021/libmlx.a)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Ilmx -framework OpenGL -framework AppKit")

add_executable(cub3d parser_map.c gnl/get_next_line.c gnl/get_next_line_utils.c gnl/get_next_line.h)

target_link_libraries(cub3d  ${SOURCE_DIR})