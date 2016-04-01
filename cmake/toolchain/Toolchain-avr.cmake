INCLUDE(CMakeForceCompiler)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)


# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# TODO: configure linker
find_program(AVRCPP avr-g++)
find_program(AVRC avr-gcc)
find_program(AVRAR avr-ar)
find_program(AVRSTRIP avr-strip)
find_program(OBJCOPY avr-objcopy)
find_program(OBJDUMP avr-objdump)
find_program(AVRSIZE avr-size)
find_program(AVRDUDE avrdude)
find_program(SCREEN screen)

# Tools
SET(CMAKE_C_COMPILER ${AVRC})
SET(CMAKE_AR ${AVRAR})

SET(CMAKE_BUILD_TYPE debug)

SET(CSTANDARD "-std=gnu99")
SET(CWARN "-Wall -Wpedantic")
SET(CTUNING "")
SET(CDEBUG "")
#SET(COPT "-Os -flto -fuse-linker-plugin")
SET(COPT "-Os")
SET(CMCU "-mmcu=atmega328p")
SET(CDEFS "-DF_CPU=16000000UL")
SET(CFLAGS "${CMCU} ${CDEBUG} ${CWARN} ${CTUNING} ${COPT} ${CSTANDARD} ${CDEFS}")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}" CACHE STRING "" FORCE)

SET(CMAKE_AR_FLAGS "${CMAKE_AR_FLAGS} csrv" CACHE STRING "" FORCE)

