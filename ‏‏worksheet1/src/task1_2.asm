%include "asm_io.inc"

segment .data
    bytes   dd  0x6C697665  ; "live" in hex (little-endian will show "evil")
    end     db  0           ; null terminator
    msg1    db  "String at address: ", 0
    msg2    db  "Memory dump: ", 0

segment .text
    global asm_main

asm_main:
    enter   0, 0
    pusha
    
    ; Demonstrate little-endian
    mov     eax, msg1
    call    print_string
    mov     eax, bytes
    call    print_string  ; Will print "evil" not "live"
    call    print_nl
    
    ; Show memory dump
    mov     eax, msg2
    call    print_string
    call    print_nl
    dump_mem 1, bytes, 1  ; Dump memory around bytes
    
    ; Show register dump
    dump_regs 1
    
    popa
    mov     eax, 0
    leave
    ret