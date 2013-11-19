add_definitions(
  -W
  #-pedantic
  #-Wall
)

find_library(M_LIB m)

add_executable(Terminal 
		CodeWar.c
		definitions.h
		launch/modifications.h
		launch/modifications.c

		interpreteur/arguments.h
		interpreteur/arguments.c
		interpreteur/commandes.h
		interpreteur/commandes.c
		interpreteur/flags.h
		interpreteur/flags.c
		interpreteur/interpreteur.h
		interpreteur/interpreteur.c
		interpreteur/typage_operande.h
		interpreteur/typage_operande.c

		affichage/affichage.h
 		affichage/affichage.c
		
		debug/debug.h 
		debug/debug.c
)
target_link_libraries(Terminal ${M_LIB})
