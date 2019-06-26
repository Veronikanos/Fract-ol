cmake_minimum_required(VERSION 3.12.1)
project(fractol C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(libft LBFT_SRC)
aux_source_directory(src SOURCES)
add_library(ft STATIC ${LBFT_SRC})
include_directories(libft/includes)
include_directories(inc)

add_executable(${CMAKE_PROJECT_NAME}
                ${SOURCES} src/draw_fractals.c src/control.c src/color.c src/init_fractals.c src/count_fractals.c src/choose_color_scheme.c)
#-Wall -Wextra -Werror
#set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=\"address\" -g -fno-omit-frame-pointer")
#set(GCC_COVERAGE_COMPILE_FLAGS "-march=native -Ofast")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
target_link_libraries(${CMAKE_PROJECT_NAME} ft "-Ipthreads -lmlx -framework OpenGL -framework AppKit")