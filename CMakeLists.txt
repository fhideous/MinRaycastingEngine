cmake_minimum_required(VERSION 3.17)

project(cub3d C)
set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR_LIBFT /Users/fhideous/CLionProjects/cub3d_kek/lib/libft.a)
set (MLX_DIR /Users/fhideous/CLionProjects/cub3d_kek/mlx_mac/libmlx.a)
#set(SOURCE_DIR /Users/fhideous/Desktop/fhideous/cub3d/mlx_mac/libmlx.a)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -framework OpenGL -framework AppKit")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS "-O0")

add_executable(cub3d main.c parser_map.c gnl/get_next_line.c
        parse_set.c find_player.c create_win.c stuff.c
        lib/libft.h hdrs/get_next_line.h hdrs/cub3d.h  scene_put.c ray.c
        mlx_commands.c screan.c)
 set(HEADERS hdrs/mlx.h)


target_link_libraries(cub3d  ${SOURCE_DIR_LIBFT} ${MLX_DIR})

target_link_libraries(cub3d
        mlx Xext X11      # for mlx
        m               # math library
#        pthread         # for multithreading
        )
