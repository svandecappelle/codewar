add_definitions(
  -W
  -pedantic
  -Waddress
  -Warray-bounds
  -Wchar-subscripts
  -Wimplicit-function-declaration
  -Wcomment
  -Wformat
  -Wmaybe-uninitialized
  -Wnonnull
  -Wpointer-sign
  -Wreturn-type
  -Wsequence-point
  -Wstrict-aliasing
  -Wstrict-overflow=1
  -Wswitch
  -Wtrigraphs
  -Wuninitialized
  -Wunknown-pragmas
  -Wunused-function
  -Wunused-label
  -Wunused-value
  -Wvolatile-register-var

  -Wno-overflow
)

find_library(M_LIB m)

add_executable(Terminal 
		CodeWar.c
		definitions.h
		launch/modifications.h
		launch/modifications.c

		interpretor/arguments.h
		interpretor/arguments.c
		interpretor/commands.h
		interpretor/commands.c
		interpretor/flags.h
		interpretor/flags.c
		interpretor/interpretor.h
		interpretor/interpretor.c
		interpretor/operand.h
		interpretor/operand.c

		display/display.h
 		display/display.c
		
		debug/debug.h 
		debug/debug.c
)
target_link_libraries(Terminal ${M_LIB})
