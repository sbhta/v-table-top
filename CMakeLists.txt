cmake_minimum_required(VERSION 3.10)

# Make clangd aware
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Get the current directory name for project name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})


# Gather all source files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add raylib as a subdir
add_subdirectory(libs/raylib)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)


