global inb, outb

; Read byte from I/O port
inb:
    mov edx, [esp + 4]
    in al, dx
    ret

; Write byte to I/O port
outb:
    mov edx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret