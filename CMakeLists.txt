cmake_minimum_required (VERSION 2.8)
project (SOP)
set (cmake_color_makefile on)
set (cmake_verbose_makefile on)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(sop sop.c)
