add_definitions(
  -W
)
link_directories(
  ${GLIB_LIBRARY_DIRS}  ${GTK_LIBRARY_DIRS}  ${GLADE_LIBRARY_DIRS} 
  )
include_directories(
  ${GLIB_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${GLADE_INCLUDE_DIRS} 
  )
add_executable(../../bin/CodeWar # name of the executable on Windows will be example.exe 
  test2.c
  test2.h
  CodeWar.c
  CodeWar.h
  affichage.c
  affichage.h
  typage_operande.c
  typage_operande.h
  arguments.c
  arguments.h
  commandes.c
  commandes.h
  definitions.h
  interpreteur.c
  interpreteur.h
  modifications.c
  modifications.h
  flags.c
  flags.h
  debug.c
  debug.h
  argumentsGraphiques.h
  )
target_link_libraries(../../bin/CodeWar
    ${GTK_LIBRARIES}  ${GLADE_LIBRARIES})
