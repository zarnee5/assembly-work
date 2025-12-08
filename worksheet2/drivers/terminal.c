#include "frame_buffer.h"
#include "interrupts.h"

#define MAX_CMD_LEN 128
#define MAX_ARGS 10

// Command structure
struct command {
    const char* name;
    void (*function)(char* args);
};

// Command implementations
void cmd_echo(char* args) {
    fb_write_string(args);
    fb_write_string("\n");
}

void cmd_clear(char* args) {
    (void)args;  // Unused
    fb_clear();
}

void cmd_help(char* args) {
    (void)args;
    fb_write_string("Available commands:\n");
    fb_write_string("  echo <text>   - Display text\n");
    fb_write_string("  clear         - Clear screen\n");
    fb_write_string("  help          - Show this help\n");
    fb_write_string("  version       - Show OS version\n");
}

void cmd_version(char* args) {
    (void)args;
    fb_write_string("TinyOS v1.0 - UWE Advanced Systems Programming\n");
}

// Command table
struct command commands[] = {
    {"echo", cmd_echo},
    {"clear", cmd_clear},
    {"help", cmd_help},
    {"version", cmd_version},
    {NULL, NULL}
};

void terminal_run(void) {
    char input[MAX_CMD_LEN];
    char prompt[] = "myos> ";
    
    while(1) {
        fb_write_string(prompt);
        readline(input, MAX_CMD_LEN);
        
        // Skip empty input
        if (input[0] == '\0') {
            continue;
        }
        
        // Parse command
        char *cmd = input;
        char *args = NULL;
        
        // Find space separating command and arguments
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == ' ') {
                input[i] = '\0';
                args = &input[i + 1];
                break;
            }
        }
        
        // Find and execute command
        int found = 0;
        for (int i = 0; commands[i].name != NULL; i++) {
            if (strcmp(cmd, commands[i].name) == 0) {
                commands[i].function(args);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            fb_write_string("Unknown command: ");
            fb_write_string(cmd);
            fb_write_string("\nType 'help' for available commands\n");
        }
    }
}

// Simple string compare
int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Simple string copy
void strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}