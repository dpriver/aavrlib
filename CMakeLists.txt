#cmake try...

cmake_minimum_required(VERSION 2.8)

set(CMAKE_PREFIX_PATH /usr)
set(CMAKE_FIND_LIBRARY_PREFIXES lib)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_TOOLCHAIN_FILE cmake/toolchain/Toolchain-avr.cmake)

project(aavrlib C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test") 

SET(AVRLIBC_FILES c m)

foreach(FILE ${AVRLIBC_FILES})
	find_library(LIBTEMP ${FILE} HINTS /usr/lib/avr/lib REQUIRED)
	if(NOT LIBTEMP)
		message("-- ERROR: No se ha encontrado la librería avrlibc ${FILE}")
		return()
	endif()
	set(AVRLIBC "${AVRLIBC} ${LIBTEMP}")
endforeach()
message("-- AVR-libc library found")


include_directories( include /usr/lib/avr/include)

# compile library
add_subdirectory( src )
add_library(aavr STATIC $<TARGET_OBJECTS:uc_objects> 
	$<TARGET_OBJECTS:arduino_objects> $<TARGET_OBJECTS:peripherals_objects>)

# compile tests
add_subdirectory( test )
