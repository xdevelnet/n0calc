cmake_minimum_required(VERSION 3.2)
project(gtk3t_a C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(SOURCE_FILES
    main.c buttons.h)

add_executable(gtk3hllwrld ${SOURCE_FILES})


target_link_libraries(gtk3hllwrld ${GTK3_LIBRARIES})
