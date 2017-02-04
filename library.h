/* 
Kyle Sucro
kes172
*/

#ifndef _LIBRARY_INCLUDED_H
#define _LIBRARY_INCLUDED_H

#include <stdlib.h>
#include <stdio.h>

#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>

typedef unsigned short color_t;    // |15 11|10  5|4  0|
                                   // |red  |green|blue|
                                   //   5   + 6   + 5  =  16 bits
// Macros to extract RGB colors 
#define BMASK(c) (c & 0x001F) // Blue mask
#define GMASK(c) (c & 0x07E0) // Green mask
#define RMASK(c) (c & 0xF800) // Red mask

void init_graphics();
void exit_graphics();
void clear_screen();
char get_key();
void sleep_ms(long ms);

void draw_pixel(int x, int y, color_t color);
void draw_rect(int x1, int y1, int width, int height, color_t c);
void draw_text(int x, int y, const char *text, color_t c);

#endif
