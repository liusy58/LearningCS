cmake_minimum_required(VERSION 3.5)

# Set the project name
project (mdriver)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "gcc")
set (CMAKE_CXX_FLAGS "-Wall -O2 -m32 -fsanitize=address")
set (CMAKE_C_FLAGS "-Wall -O2 -m32 -fsanitize=address")
# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/clock.c
        src/fcyc.c
        src/fsecs.c
        src/ftimer.c
        src/mdriver.c
        src/memlib.c
        src/mm.c
        )

# Add an executable with the above sources
add_executable(mdriver ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(mdriver
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )