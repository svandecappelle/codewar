cmake_minimum_required(VERSION 2.6)
project(CODE_WAR)

find_package (PkgConfig REQUIRED)
#pkg_check_modules(GTK gtk) # look into FindPkgConfig.cmake, 
#pkg_check_modules(GLADE libglade-2.0) # look into FindPkgConfig.cmake, 
#pkg_check_modules(GLIB glib-2.0) # look into FindPkgConfig.cmake, 
#if(GLADE_NOT_FOUND)
#  message("truc qui cloche")
#endif(GLADE_NOT_FOUND)


#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
#add_definitions(${GTK3_CFLAGS_OTHER})

#target_link_libraries( ${CODE_WAR} gtk-3)

add_subdirectory(src)
add_subdirectory(src/core) 
