global loader
extern kmain  ; Declare kmain as external C function

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
global _start
_start:
    ; Set up stack
    mov esp, stack_space
    
    ; Call C kernel main function
    call kmain
    
    ; If kmain returns, loop forever
.loop:
    hlt
    jmp .loop

section .bss
resb 8192  ; 8KB for stack
stack_space: