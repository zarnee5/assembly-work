#ifndef PIC_H
#define PIC_H

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2+1)

#define PIC_1_OFFSET 0x20
#define PIC_2_OFFSET 0x28

void pic_remap(s32int offset1, s32int offset2);
void pic_acknowledge(u32int interrupt);

#endif