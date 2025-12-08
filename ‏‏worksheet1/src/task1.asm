%include "asm_io.inc"

segment .data
    msg1    db  "Enter first number: ", 0
    msg2    db  "Enter second number: ", 0
    result_msg db "Sum is: ", 0

segment .bss
    num1    resd 1
    num2    resd 1
    sum     resd 1

segment .text
    global asm_main

asm_main:
    enter   0, 0
    pusha
    
    ; Get first number
    mov     eax, msg1
    call    print_string
    call    read_int
    mov     [num1], eax
    
    ; Get second number
    mov     eax, msg2
    call    print_string
    call    read_int
    mov     [num2], eax
    
    ; Calculate sum
    mov     eax, [num1]
    add     eax, [num2]
    mov     [sum], eax
    
    ; Print result
    mov     eax, result_msg
    call    print_string
    mov     eax, [sum]
    call    print_int
    call    print_nl
    
    popa
    mov     eax, 0
    leave
    ret