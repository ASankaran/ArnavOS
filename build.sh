nasm -f elf32 boot/kernel.asm -o build/kasm.o
nasm -f elf32 devices/keyboard/keyboard.asm -o build/keyasm.o
i686-elf-gcc -m32 -c devices/keyboard/keyboard.c -o build/keyboard.o
i686-elf-gcc -m32 -c devices/screen/screen.c -o build/screen.o
i686-elf-gcc -m32 -c kernel/kernel.c -o build/kc.o
i686-elf-ld -m elf_i386 -T link.ld -o build/kernel build/kasm.o build/kc.o build/keyasm.o build/keyboard.o build/screen.o