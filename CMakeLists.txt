cmake_minimum_required (VERSION 2.8)
project (cxx11os NONE)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "i686")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags")
set(CMAKE_ASM_NASM_LINK_FLAGS "-T src/link.ld -melf_i386")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
enable_language(ASM_NASM)
add_executable(loader src/loader.asm)
