# cmake
#cmake_minimum_required(VERSION 2.8)

add_subdirectory(uc)
add_subdirectory(peripherals)


set(util_source_files softPWM_short.c softPWM_long.c systick.c ir_nec.c)
add_library(util_objects OBJECT ${util_source_files})

