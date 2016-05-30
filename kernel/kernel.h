#ifndef KERNEL_H
 #define KERNEL_H

#ifndef __cplusplus
 #include <stdbool.h>
#endif

#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong os. */
#ifdef __linux__
 #error "You should use the cross-compiler."
#endif

#ifndef __i386__
 #error "It's not a ix86-elf compiler."
#endif

/* Hardware text mode color constants. */
typedef enum    e_vga_color{
  COLOR_BLACK = 0,
  COLOR_BLUE = 1,
  COLOR_GREEN = 2,
  COLOR_CYAN = 3,
  COLOR_RED = 4,
  COLOR_MAGENTA = 5,
  COLOR_BROWN = 6,
  COLOR_LIGHT_GREY = 7,
  COLOR_DARK_GREY = 8,
  COLOR_LIGHT_BLUE = 9,
  COLOR_LIGHT_GREEN = 10,
  COLOR_LIGHT_CYAN = 11,
  COLOR_LIGHT_RED = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN = 14,
  COLOR_WHITE = 15
} vga_color;

static const size_t     VGA_WIDTH = 80;
static const size_t     VGA_HEIGHT = 25;

size_t          terminal_row;
size_t          terminal_column;
uint8_t         terminal_color;
uint16_t*       terminal_buffer;

uint8_t         make_color(vga_color fg, vga_color bg);
uint16_t        make_vgaentry(char c, uint8_t color);
size_t          strlen(const char* str);
void            terminal_initialize();
void            terminal_setcolor(uint8_t color);
void            terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void            terminal_putchar(char c);
void            terminal_writestring(const char* data);
void            kernel_main();

#endif // KERNEL_H
