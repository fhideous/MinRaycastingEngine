cmake_minimum_required(VERSION 3.17)

project(cub3d C)
set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR_LIBFT /home/fhideous/CLionProjects/cub3d/lib/libft.a)
set (MLX_DIR /home/fhideous/CLionProjects/cub3d/mlx/libmlx.a)
#set(SOURCE_DIR /Users/fhideous/Desktop/fhideous/cub3d/minilibx_opengl_20191021/libmlx.a)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Ilmx -framework OpenGL -framework AppKit")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS "-O3")
add_executable(cub3d main.c parser_map.c gnl/get_next_line.c
        parse_set.c find_player.c create_win.c stuff.c
        lib/libft.h hdrs/get_next_line.h hdrs/cub3d.h scene_put.c ray.c print_ray.c mlx_commands.c)

target_link_libraries(cub3d  ${SOURCE_DIR_LIBFT} ${MLX_DIR})

target_link_libraries(cub3d
        mlx Xext X11    # for mlx
        m               # math library
#        pthread         # for multithreading
        )
