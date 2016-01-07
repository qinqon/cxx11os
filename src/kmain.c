#include "io.h"

#define FB_GREEN 2
#define FB_DARK_GREY 8


char *fb = (char *) 0x000B8000;

/* void update_cursor(int row, int col)
 *   * by Dark Fiber
 *     */
void fb_update_cursor(int row, int col)
{
   unsigned short position=(row*80) + col;
   // cursor LOW port to vga INDEX register
   outb(0x3D4, 0x0F);
   outb(0x3D5, (unsigned char)(position&0xFF));
   // cursor HIGH port to vga INDEX register
   outb(0x3D4, 0x0E);
   outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}


/** 
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 *
 * @param i The location in the framebuffer
 * @param c The character
 * @param fg The foreground color
 * @param bg The background color
 *
 * */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)

{
   unsigned int idx = 2 * i;
   fb[idx] = c;
   fb[idx + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void kmain()
{
   fb_write_cell(2, 'H', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(3, 'e', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(4, 'l', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(5, 'l', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(6, 'o', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(7, ' ', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(8, 'O', FB_GREEN, FB_DARK_GREY);
   fb_write_cell(9, 'S', FB_GREEN, FB_DARK_GREY);
   
   fb_update_cursor(30, 50);
}

