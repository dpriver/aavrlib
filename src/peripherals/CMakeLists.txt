# uc library files
#cmake_minimum_required(VERSION 2.8)

set(peripherals_source_files HC-SR04.c infrared.c lcd_1602a.c)

add_library(peripherals_objects OBJECT ${peripherals_source_files})
