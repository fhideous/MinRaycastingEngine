cmake_minimum_required(VERSION 3.17)

project(cub3d C)
set(CMAKE_C_STANDARD 99)

set(SOURCE_DIR_LIBFT /home/fhideous/CLionProjects/cub3d/lib/libft.a)
set (MLX_DIR /home/fhideous/CLionProjects/cub3d/mlx/libmlx.a)
set(CMAKE_C_FLAGS "-O0")
add_executable(cub3d main.c parser_map.c get_next_line.c get_next_line_utils.c
        parse_set.c find_player.c create_win.c stuff.c
        parser_map_stuff.c ray.c
        mlx_commands.c screan.c messages.c map_validate.c all_free.c parse_color.c
        movements.c to_window.c sprite_preparation.c big_kek.c )

target_link_libraries(cub3d  ${SOURCE_DIR_LIBFT} ${MLX_DIR})

target_link_libraries(cub3d
        mlx Xext X11    # for mlx
        m               # math library
        )
