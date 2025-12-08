#include "frame_buffer.h"

extern void outb(unsigned short port, unsigned char data);

static unsigned short *fb = (unsigned short *)0x000B8000;
static unsigned int cursor_pos = 0;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = ((bg & 0x0F) << 12) | ((fg & 0x0F) << 8) | c;
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write(char *buf) {
    unsigned int i = 0;
    while (buf[i]) {
        fb_write_cell(cursor_pos, buf[i], FB_LIGHT_GREY, FB_BLACK);
        i++;
        cursor_pos++;
    }
    fb_move_cursor(cursor_pos);
}

void fb_clear(void) {
    for (unsigned int i = 0; i < 80 * 25; i++) {
        fb_write_cell(i, ' ', FB_LIGHT_GREY, FB_BLACK);
    }
    cursor_pos = 0;
    fb_move_cursor(cursor_pos);
}

void fb_write_string(char *str) {
    fb_write(str);
}

void fb_write_char(char c) {
    fb_write_cell(cursor_pos, c, FB_LIGHT_GREY, FB_BLACK);
    cursor_pos++;
    fb_move_cursor(cursor_pos);
}

void fb_newline(void) {
    unsigned int row = cursor_pos / 80;
    cursor_pos = (row + 1) * 80;
    if (cursor_pos >= 80 * 25) {
        /* Scroll screen */
        for (unsigned int i = 0; i < 80 * 24; i++) {
            fb[i] = fb[i + 80];
        }
        for (unsigned int i = 80 * 24; i < 80 * 25; i++) {
            fb_write_cell(i, ' ', FB_LIGHT_GREY, FB_BLACK);
        }
        cursor_pos = 80 * 24;
    }
    fb_move_cursor(cursor_pos);
}

void fb_backspace(void) {
    if (cursor_pos > 0) {
        cursor_pos--;
        fb_write_cell(cursor_pos, ' ', FB_LIGHT_GREY, FB_BLACK);
        fb_move_cursor(cursor_pos);
    }
}