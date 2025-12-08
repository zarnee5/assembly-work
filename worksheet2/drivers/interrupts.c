#include "interrupts.h"
#include "pic.h"
#include "io.h"
#include "frame_buffer.h"
#include "keyboard.h"

#define INTERRUPTS_DESCRIPTOR_COUNT 256
#define INTERRUPTS_KEYBOARD 33
#define INPUT_BUFFER_SIZE 256

u8int input_buffer[INPUT_BUFFER_SIZE];
u8int buffer_index = 0;
u8int buffer_start = 0;
u8int buffer_count = 0;

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

// Helper function: integer to string
void itoa(int n, char *str) {
    int i = 0;
    int is_negative = 0;
    
    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    
    if (n < 0) {
        is_negative = 1;
        n = -n;
    }
    
    while (n != 0) {
        int rem = n % 10;
        str[i++] = rem + '0';
        n = n / 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }
    
    str[i] = '\0';
    
    // Reverse string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void interrupts_init_descriptor(s32int index, u32int address) {
    idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF;
    idt_descriptors[index].offset_low = (address & 0xFFFF);
    idt_descriptors[index].segment_selector = 0x08;
    idt_descriptors[index].reserved = 0x00;
    idt_descriptors[index].type_and_attr = (0x01 << 7) | (0x00 << 6) | 
                                          (0x00 << 5) | 0x0E;
}

void interrupts_install_idt() {
    // Initialize keyboard interrupt handler
    interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (u32int)interrupt_handler_33);
    
    idt.address = (s32int) &idt_descriptors;
    idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
    load_idt((s32int) &idt);
    
    // Remap PIC
    pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
    
    // Unmask keyboard interrupt (IRQ1)
    outb(0x21, inb(0x21) & ~(1 << 1));
}

/* Interrupt handler */
void interrupt_handler(__attribute__((unused)) struct cpu_state cpu, 
                       u32int interrupt, 
                       __attribute__((unused)) struct stack_state stack) {
    u8int input;
    u8int ascii;
    
    switch (interrupt) {
        case INTERRUPTS_KEYBOARD:
            while ((inb(0x64) & 1)) {
                input = keyboard_read_scan_code();
                
                // Only process key press (not release)
                if (!(input & 0x80)) {
                    ascii = keyboard_scan_code_to_ascii(input);
                    
                    if (ascii != 0) {
                        // Handle backspace
                        if (ascii == '\b') {
                            if (buffer_index > 0) {
                                buffer_index--;
                                buffer_count--;
                                fb_backspace();
                            }
                        }
                        // Handle newline
                        else if (ascii == '\n') {
                            // Store in buffer
                            if (buffer_count < INPUT_BUFFER_SIZE) {
                                input_buffer[(buffer_start + buffer_count) % INPUT_BUFFER_SIZE] = ascii;
                                buffer_count++;
                            }
                            fb_newline();
                        }
                        // Handle regular character
                        else {
                            // Store in buffer
                            if (buffer_count < INPUT_BUFFER_SIZE) {
                                input_buffer[(buffer_start + buffer_count) % INPUT_BUFFER_SIZE] = ascii;
                                buffer_count++;
                            }
                            // Display character
                            fb_write_char(ascii);
                        }
                    }
                }
            }
            pic_acknowledge(interrupt);
            break;
            
        default:
            pic_acknowledge(interrupt);
            break;
    }
}

/* Task 2: Input Buffer API */

// Get a character from buffer (blocking)
char getc(void) {
    while (buffer_count == 0) {
        // Wait for interrupt
        asm volatile ("hlt");
    }
    
    char c = input_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % INPUT_BUFFER_SIZE;
    buffer_count--;
    
    return c;
}

// Read a line from buffer
void readline(char *buffer, int max_len) {
    int i = 0;
    char c;
    
    while (i < max_len - 1) {
        c = getc();
        
        if (c == '\n') {
            buffer[i] = '\0';
            fb_write_char('\n');
            return;
        } else if (c == '\b') {
            if (i > 0) {
                i--;
                fb_write_char('\b');
                fb_write_char(' ');
                fb_write_char('\b');
            }
        } else {
            buffer[i++] = c;
            fb_write_char(c);
        }
    }
    
    buffer[max_len - 1] = '\0';
}