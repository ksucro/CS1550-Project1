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
#include <sys/ioctl.h>
#include <unistd.h>

typedef unsigned short color_t;    // |15 11|10  5|4  0|
                                   // |red  |green|blue|
                                   //   5   + 6   + 5  =  16 bits
// Macros to extract RGB colors 
#define RGB(r, g, b) ( (r << 11) | (g << 5) | (b) )

void init_graphics();
void exit_graphics();
void clear_screen();
char get_key();
void sleep_ms(long ms);

void draw_pixel(int x, int y, color_t color);
void draw_rect(int x, int y, int width, int height, color_t c);
void draw_text(int x, int y, const char *text, color_t c);

#endif
