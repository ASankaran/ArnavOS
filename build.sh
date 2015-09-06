nasm -f elf32 boot/kernel.asm -o build/kasm.o
i686-elf-gcc -m32 -c kernel/kernel.c -o build/kc.o
i686-elf-ld -m elf_i386 -T link.ld -o build/kernel build/kasm.o build/kc.o