cmake_minimum_required (VERSION 2.8)
project (cxx11os NONE)

# Cross compiling to 32 bits
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "i686")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs" CACHE STRING "c flags")

enable_language(ASM_NASM)
enable_language(C)

set(CMAKE_EXE_LINKER_FLAGS "-melf_i386 -T ${PROJECT_SOURCE_DIR}/src/linker.ld")
set(CMAKE_C_LINK_EXECUTABLE "ld <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET>")

add_executable(kernel.elf src/io.asm src/loader.asm src/kmain.c)
file(DOWNLOAD http://littleosbook.github.com/files/stage2_eltorito "${CMAKE_BINARY_DIR}/stage2_eltorito")

add_custom_command(
   OUTPUT os.iso 
   COMMAND mkdir -p iso/boot/grub
   COMMAND cp stage2_eltorito iso/boot/grub/ 
   COMMAND cp ${CMAKE_BINARY_DIR}/kernel.elf iso/boot/
   COMMAND cp ${CMAKE_SOURCE_DIR}/src/menu.lst iso/boot/grub/
   COMMAND genisoimage 
   -R 
   -b boot/grub/stage2_eltorito
   -no-emul-boot
   -boot-load-size 4
   -A os
   -input-charset utf8
   -quiet 
   -boot-info-table 
   -o os.iso 
   iso
   DEPENDS kernel.elf ${CMAKE_SOURCE_DIR}/src/menu.lst
   )

add_custom_target(iso DEPENDS os.iso)

add_custom_target(run 
   COMMAND bochs -f ${CMAKE_SOURCE_DIR}/cfg/bochsrc.txt -q
   DEPENDS os.iso)
