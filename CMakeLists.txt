cmake_minimum_required(VERSION 3.17)
project(cub3d C)
set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR /home/fhideous/CLionProjects/cub3d/lib/libft.a)
#set(SOURCE_DIR /Users/fhideous/Desktop/fhideous/cub3d/minilibx_opengl_20191021/libmlx.a)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Ilmx -framework OpenGL -framework AppKit")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(cub3d main.c parser_map.c gnl/get_next_line.c hdrs/cub3d.h
        lib/ft_lstnew.c lib/ft_lstadd_back.c lib/ft_lstsize.c lib/libft.h
        hdrs/get_next_line.h lib/ft_lstclear.c parse_set.c)

target_link_libraries(cub3d  ${SOURCE_DIR})