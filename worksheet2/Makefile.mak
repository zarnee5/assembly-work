CC = gcc
ASM = nasm
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -Wall -Wextra -I./include -I./drivers
ASMFLAGS = -f elf
LDFLAGS = -T source/link.ld -melf_i386

OBJECTS = source/loader.o source/kmain.o source/io.o \
          drivers/frame_buffer.o drivers/keyboard.o drivers/pic.o \
          drivers/interrupts.o drivers/interrupt_handlers.o \
          drivers/interrupt_asm.o drivers/hardware_interrupt_enabler.o

all: os.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o iso/boot/kernel.elf

os.iso: kernel.elf
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso

run: os.iso
	qemu-system-i386 -nographic -boot d -cdrom os.iso -m 32 -d cpu -D log0.txt

run-curses: os.iso
	qemu-system-i386 -curses \
		-monitor telnet::45454,server,nowait \
		-serial mon:stdio \
		-boot d \
		-cdrom os.iso \
		-m 32 \
		-d cpu \
		-D log0.txt

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -f source/*.o drivers/*.o kernel.elf os.iso iso/boot/kernel.elf

.PHONY: all clean run run-curses