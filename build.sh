nasm -f elf32 boot/kernel.asm -o build/kasm.o
nasm -f elf32 devices/keyboard/keyboard.asm -o build/keyasm.o
i686-elf-gcc -m32  -ffreestanding -c devices/keyboard/keyboard.c -o build/keyboard.o
i686-elf-gcc -m32  -ffreestanding -c devices/screen/screen.c -o build/screen.o
i686-elf-gcc -m32  -ffreestanding -c terminal/terminal.c -o build/terminal.o
i686-elf-gcc -m32  -ffreestanding -c kernel/kernel.c -o build/kc.o
i686-elf-gcc -m32  -ffreestanding -c lib/time/time.c -o build/time.o
i686-elf-gcc -m32  -ffreestanding -c lib/string/string.c -o build/string.o
i686-elf-gcc -m32  -ffreestanding -c programs/programs.c -o build/programs.o
i686-elf-gcc -m32  -ffreestanding -c programs/echo/echo.c -o build/echo.o
i686-elf-ld -m elf_i386 -T link.ld -o build/kernel build/kasm.o build/kc.o build/keyasm.o build/keyboard.o build/screen.o build/terminal.o build/time.o build/programs.o build/echo.o build/string.o