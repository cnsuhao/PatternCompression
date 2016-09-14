#include_directories(${DERP_SOURCE_DIR}/code)
# add_sources(main.cpp)

# file( GLOB SRCS *.c *.h *.cpp *.hpp ../src/*.c ../src/*.h ../src/*.cpp ../src/*.hpp) 
# ile( GLOB HEADERS *.c *.h *.cpp *.hpp) 
file( GLOB SRCS *.c *.h *.cpp *.hpp ../src/*.c ../src/*.h ../src/*.cpp ../src/*.hpp) 

add_executable( ${ExeName} ${SRCS} )

if (MSVC)
 #   target_link_libraries(${ExeName} ${LIBDIR}/opengl32.lib ${LIBDIR}/glew32.lib ${LIBDIR}/SDL2.lib ${LIBDIR}/SDL2main.lib)    
    set(LIBDIR "C:/Dependencies/lib")
    #find_library(SDL_LIBRARY SDL2 HINTS ${LIBDIR}/)
    #find_library(SDLmain_LIBRARY SDL2main HINTS ${LIBDIR}/)
    #find_library(GLEW_LIBRARY glew32 HINTS ${LIBDIR}/)
    #target_link_libraries(${ExeName} PUBLIC opengl32.lib ${SDL_LIBRARY} ${SDLmain_LIBRARY} ${GLEW_LIBRARY})
    #LINK_DIRECTORIES(${LIBDIR} "C:/Boost/boost_1_61_0/stage/lib")
    #target_link_libraries(${ExeName})
elseif (UNIX)
	include_directories(${CMAKE_BINARY_DIR}/../include)
	#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lGL -lGLEW -lSDL2 -lSDL2main" )	
	#find_package (SDL2 REQUIRED)
	#find_package (GLM REQUIRED)
	#find_package (GLEW REQUIRED)
	#if (SDL2_FOUND)
	#	if (GLM_FOUND)
	#		if (GLEW_FOUND)
	#			#Debug
	#			MESSAGE("GLEW Include: ${GLEW_INCLUDE_DIRS}.")
	#			MESSAGE("GLEW Libraries: ${GLEW_LIBRARIES}.")
#
	#			# SDL2 path handling
	#			string(REGEX REPLACE "/SDL2" "" SDL_INCLUDE_OUT "${SDL2_INCLUDE_DIRS}")
	#			string(REGEX REPLACE "SDL2 " "SDL2" SDL_OUT "${SDL2_LIBRARIES}")
	#			MESSAGE("SDL2 Include: ${SDL_INCLUDE_OUT}.")
	#			MESSAGE("SDL2 Libraries: ${SDL_OUT}.")
#
#
	#			# GLEW path handling
#
	#			# Link and add search paths
	#			target_include_directories(${ExeName} PUBLIC "${CMAKE_BINARY_DIR}/../include" "${SDL_INCLUDE_OUT}" "${GLM_INCLUDE_DIRS}")
	#			set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed,-framework OpenGL")
	#			target_link_libraries(${ExeName} ${SDL_OUT} "-framework OpenGL" "${GLEW_LIBRARIES}")
	#			#target_link_libraries(${ExeName} -lGL -lGLEW -lSDL2 -lSDL2main)	
	#		endif (GLEW_FOUND)
	#	endif (GLM_FOUND)
	#endif (SDL2_FOUND)
endif ()
