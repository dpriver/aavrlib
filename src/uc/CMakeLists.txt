# uc library files
#cmake_minimum_required(VERSION 2.8)

set(uc_source_files analog.c spi.c system.c timers.c usart.c systick.c softPWM.c softPWM_long.c)

add_library(uc_objects OBJECT ${uc_source_files})
