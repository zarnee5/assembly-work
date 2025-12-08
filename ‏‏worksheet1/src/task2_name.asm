%include "asm_io.inc"

segment .data
    prompt_name   db  "Enter your name: ", 0
    prompt_times  db  "How many times to welcome? (50-100): ", 0
    welcome       db  "Welcome, ", 0
    error_msg     db  "Error: Number must be 50-100!", 0

segment .bss
    name_buffer   resb 50

segment .text
    global asm_main

asm_main:
    enter   0, 0
    pusha
    
    ; Get name
    mov     eax, prompt_name
    call    print_string
    mov     eax, name_buffer
    call    read_string
    
    ; Get number
    mov     eax, prompt_times
    call    print_string
    call    read_int
    
    ; Validate (50-100)
    cmp     eax, 50
    jl      error
    cmp     eax, 100
    jg      error
    
    ; Print welcome message n times
    mov     ecx, eax    ; counter
print_loop:
    push    ecx
    mov     eax, welcome
    call    print_string
    mov     eax, name_buffer
    call    print_string
    call    print_nl
    pop     ecx
    loop    print_loop
    jmp     end_program
    
error:
    mov     eax, error_msg
    call    print_string
    call    print_nl

end_program:
    popa
    mov     eax, 0
    leave
    ret