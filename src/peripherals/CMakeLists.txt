# uc library files
#cmake_minimum_required(VERSION 2.8)

set(peripherals_source_files d7seg.c infrared.c lcd.c ultrasonic.c)

add_library(peripherals_objects OBJECT ${peripherals_source_files})
