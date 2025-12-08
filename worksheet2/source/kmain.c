#include "../drivers/frame_buffer.h"
#include "../drivers/keyboard.h"
#include "../drivers/interrupts.h"

// Task 2: C functions to be called from assembly
int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

void print_hello(void) {
    fb_write_string("Hello from C function!\n");
}

int multiply(int a, int b) {
    return a * b;
}

void kmain(void) {
    // Initialize framebuffer
    fb_clear();
    fb_write_string("=== TinyOS Booted ===\n");
    
    // Test C functions (Task 2)
    fb_write_string("Testing C functions:\n");
    
    int sum = sum_of_three(10, 20, 30);
    char buffer[20];
    itoa(sum, buffer);
    fb_write_string("10 + 20 + 30 = ");
    fb_write_string(buffer);
    fb_write_string("\n");
    
    print_hello();
    
    int product = multiply(7, 8);
    itoa(product, buffer);
    fb_write_string("7 * 8 = ");
    fb_write_string(buffer);
    fb_write_string("\n");
    
    fb_write_string("\nType something (keyboard input):\n");
    
    // Initialize interrupts (for Worksheet 2 Part 2)
    interrupts_install_idt();
    enable_hardware_interrupts();
    
    // Main loop
    while(1) {
        // Will handle keyboard input via interrupts
    }
}