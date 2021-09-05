cmake_minimum_required(VERSION 3.17)
project(pushswap C)

set(CMAKE_C_STANDARD 99)


# SET VARIABLES:
# ====================================================
# Adds list of project files
FILE(GLOB PUSH_SWAP_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/libft/*.c
        )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)
add_executable(
        pushswap
        ${PUSH_SWAP_SOURCES}
)
# Local targets
#add_executable(
#        builtins
#        ${LOCAL_SOURCES}
#)

target_link_libraries(
        libft
)

target_compile_options(
        pushswap PRIVATE
        #        -Wall -Wextra -Werror
)
