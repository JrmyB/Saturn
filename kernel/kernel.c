#include "kernel.h"

uint8_t         make_color(vga_color fg, vga_color bg)
{
  return fg | bg << 4;
}

uint16_t        make_vgaentry(char c, uint8_t color)
{
  uint16_t      c16 = c;
  uint16_t      color16 = color;

  return c16 | color16 << 8;
}

size_t          strlen(const char* str)
{
  size_t        ret = 0;

  while (str[ret++]);
  return ret;
}

void    terminal_initialize()
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB800;
  for (size_t y = 0; y < VGA_HEIGHT; y++){
    for (size_t x = 0; x < VGA_WIDTH; x++){
      const size_t idx = y * VGA_WIDTH + x;
      terminal_buffer[idx] = make_vgaentry(' ', terminal_color);
    }
  }
}

void    terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void    terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t idx = y * VGA_WIDTH + x;
  terminal_buffer[idx] = make_vgaentry(c, color);
}

void    terminal_putchar(char c)
{
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if (++terminal_column == VGA_WIDTH){
    terminal_column = 0;
    if (++terminal_row == VGA_HEIGHT)
      terminal_row = 0;
  }
}

void terminal_writestring(const char* data)
{
  size_t datalen = strlen(data);
  for (size_t i = 0; i < datalen; i++)
    terminal_putchar(data[i]);
}

#ifdef __cplusplus
 extern "C" /* Use C linkage for kernel main */
#endif
void    kernel_main()
{
   terminal_initialize();

   /* Since there is no support for newlines in terminal_putchar
    * yet, '\n' will produce some VGA specific character instead.
    * This is normal. 
    */
   terminal_writestring("Hello world!\n");
}
