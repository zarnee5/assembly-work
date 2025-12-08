%include "asm_io.inc"

segment .data
    array_size   equ 100
    prompt_start db "Enter start index (0-99): ", 0
    prompt_end   db "Enter end index (0-99): ", 0
    error_msg    db "Invalid range!", 0
    sum_msg      db "Sum of range is: ", 0

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
    
    ; Get start index
    mov     eax, prompt_start
    call    print_string
    call    read_int
    mov     esi, eax  ; esi = start
    
    ; Get end index
    mov     eax, prompt_end
    call    print_string
    call    read_int
    mov     edi, eax  ; edi = end
    
    ; Validate range
    cmp     esi, 0
    jl      error
    cmp     esi, 99
    jg      error
    cmp     edi, 0
    jl      error
    cmp     edi, 99
    jg      error
    cmp     esi, edi
    jg      error
    
    ; Calculate sum
    mov     ecx, esi    ; start index
    mov     ebx, edi    ; end index
    mov     eax, 0      ; sum = 0
    
sum_loop:
    ; Calculate array offset: ecx * 4
    mov     edx, ecx
    shl     edx, 2      ; multiply by 4
    add     edx, array  ; edx = &array[ecx]
    add     eax, [edx]  ; add to sum
    
    inc     ecx
    cmp     ecx, ebx
    jle     sum_loop
    
    ; Print result
    push    eax
    mov     eax, sum_msg
    call    print_string
    pop     eax
    call    print_int
    call    print_nl
    jmp     done
    
error:
    mov     eax, error_msg
    call    print_string
    call    print_nl
    
done:
    popa
    mov     eax, 0
    leave
    ret