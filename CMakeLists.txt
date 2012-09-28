cmake_minimum_required (VERSION 2.8)
project (SOP)
set (CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_SUPPRESS_REGENERATION on)

include_directories ("${PROJECT_BINARY_DIR}")

add_executable (sop misc.c set.c sop.c)
