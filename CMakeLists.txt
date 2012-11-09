cmake_minimum_required (VERSION 2.8)
project (SOP)
set (CMAKE_SUPPRESS_REGENERATION on)

set (CMAKE_VERBOSE_MAKEFILE no)
set (CMAKE_C_FLAGS "-march=native -O3 -pipe -floop-block -floop-strip-mine -floop-interchange -flto")
#set (CMAKE_VERBOSE_MAKEFILE yes)
#set (CMAKE_C_FLAGS "-O0 -ggdb -Wall")

include_directories ("${PROJECT_BINARY_DIR}")

add_executable (sop misc.c set.c sop.c set_next.c stack.c)
