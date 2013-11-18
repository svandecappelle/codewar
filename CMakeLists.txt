cmake_minimum_required(VERSION 2.6)
project(CODE_WAR)
find_package(PkgConfig)
pkg_check_modules(GTK gtk+-2.0) # look into FindPkgConfig.cmake, 
pkg_check_modules(GLADE libglade-2.0) # look into FindPkgConfig.cmake, 
pkg_check_modules(GLIB glib-2.0) # look into FindPkgConfig.cmake, 
if(GLADE_NOT_FOUND)
  message("truc qui cloche")
endif(GLADE_NOT_FOUND)
add_subdirectory(graphic) 