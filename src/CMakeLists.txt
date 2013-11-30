add_definitions(
  -W
  -pedantic
  -Wall
)

set(CMAKE_CXX_FLAGS "-g -Wall")


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
include_directories(${GOBJECT_INCLUDE_DIRS})
link_directories(${GOBJECT_LIBRARY_DIRS})
add_definitions(${GOBJECT_CFLAGS_OTHER})


add_executable(
			main
			main.cpp

			codewar.h
			codewar.cpp
			
			ui/window.h
			ui/window.cpp
			ui/IsWidget.h
			ui/IsWidget.cpp

			ui/menu/MenuApp.h
			ui/menu/MenuApp.cpp

			ui/game/Board.h
			ui/game/Board.cpp
		)

target_link_libraries( main ${GTK3_LIBRARIES})