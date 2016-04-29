# uc library files
#cmake_minimum_required(VERSION 2.8)

set(tests test_pwm test_analog test_softPWM_long test_softPWM_short)


SET(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "" FORCE)



link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

foreach(TEST ${tests})
	add_executable(${TEST} ${TEST}.c)
	#add_executable(${TEST}.hex ${TEST})
	target_link_libraries(${TEST} aavr)
endforeach()
