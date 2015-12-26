cmake_minimum_required (VERSION 2.8)
project (cxx11os NONE)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "i686")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags")
set(CMAKE_ASM_NASM_LINK_FLAGS "-T ${PROJECT_SOURCE_DIR}/src/linker.ld -melf_i386")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
enable_language(ASM_NASM)
add_executable(kernel.elf src/loader.asm)
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
