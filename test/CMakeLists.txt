# uc library files
#cmake_minimum_required(VERSION 2.8)

set(tests 
    test_analog test_systick test_infrared test_lcd_1602a
    test_mpu6050_datagather test_mpu6050_calib test_usart test_HC-SR04)


SET(CMAKE_C_FLAGS ${CFLAGS} CACHE STRING "" FORCE)



link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

foreach(TEST ${tests})
	add_executable(${TEST} ${TEST}.c)
	#add_executable(${TEST}.hex ${TEST})
	target_link_libraries(${TEST} ${AVRLIBC_FILES} aavr)
endforeach()
