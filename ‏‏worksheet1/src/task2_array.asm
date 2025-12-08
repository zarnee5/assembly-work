%include "asm_io.inc"

segment .data
    array_size   equ 100
    result_msg   db  "Sum of 1 to 100 is: ", 0

segment .bss
    array        resd array_size

segment .text
    global asm_main

asm_main:
    enter   0, 0
    pusha
    
    ; Initialize array with 1..100
    mov     ecx, array_size
    mov     ebx, 1
    mov     edi, array
    
init_loop:
    mov     [edi], ebx
    add     edi, 4
    inc     ebx
    loop    init_loop
    
    ; Sum array
    mov     ecx, array_size
    mov     esi, array
    mov     eax, 0
    
sum_loop:
    add     eax, [esi]
    add     esi, 4
    loop    sum_loop
    
    ; Print result
    mov     ebx, result_msg
    xchg    eax, ebx
    call    print_string
    xchg    eax, ebx
    call    print_int
    call    print_nl
    
    popa
    mov     eax, 0
    leave
    ret