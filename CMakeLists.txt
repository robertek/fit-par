cmake_minimum_required (VERSION 2.8)
project (SOP)
set (CMAKE_SUPPRESS_REGENERATION on)
set (CMAKE_VERBOSE_MAKEFILE no)
include_directories ("${PROJECT_BINARY_DIR}")

#set (CMAKE_C_FLAGS "-march=native -O3 -pipe -floop-block -floop-strip-mine -floop-interchange -flto")
set (CMAKE_C_FLAGS "-O0 -ggdb -Wall")

add_executable (sop set.c sop.c set_next.c stack.c sop-mpi.c)

# mpi
find_package(MPI REQUIRED)
SET(CMAKE_C_COMPILER mpicc)
set(CMAKE_C_COMPILE_FLAGS ${CMAKE_C_FLAGS} ${MPI_C_FLAGS})
set(CMAKE_C_LINK_FLAGS ${CMAKE_C_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(MPI_INCLUDE_PATH)
target_link_libraries(sop ${MPI_LIBRARIES})

# tests
enable_testing()

add_test(test1 ./sop ../test/test1)
add_test(mpi-test1 mpirun -n 2 ./sop ../test/test1)

add_test(test2 ./sop ../test/test2)
add_test(mpi-test2 mpirun -n 2 ./sop ../test/test2)

add_test(test3 ./sop ../test/test3)
add_test(mpi-test3 mpirun -n 2 ./sop ../test/test3)

add_test(test4 ./sop ../test/test4)
add_test(mpi-test4 mpirun -n 2 ./sop ../test/test4)

add_test(test5 ./sop ../test/test5)
add_test(mpi-test5 mpirun -n 2 ./sop ../test/test5)

add_test(test6 ./sop ../test/test6)
add_test(mpi-test6 mpirun -n 2 ./sop ../test/test6)

add_test(test7 ./sop ../test/test7)
add_test(mpi-test7 mpirun -n 2 ./sop ../test/test7)

add_test(test8 ./sop ../test/test8)
add_test(mpi-test8 mpirun -n 2 ./sop ../test/test8)

add_test(test9 ./sop ../test/test9)
add_test(mpi-test9 mpirun -n 2 ./sop ../test/test9)

add_test(mpi-test10 mpirun -n 2 ./sop ../test/test10)
