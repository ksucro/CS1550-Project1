/*
Kyle Sucro
kes172
*/

#include "library.h"
#include "iso_font.h"

size_t size;
color_t *address;
int fd;
void* file_add;
unsigned long yres_virtual;
unsigned long length;

struct termios termios;

typedef unsigned short color_t;

void init_graphics() {
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    
    fd = open("/dev/fb0", O_RDWR);
    
    if (fd == -1) {
        perror("Error opening /dev/fb0");
        exit(1);
    }
    
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    
    //y
    yres_virtual = vinfo.yres_virtual;
    //x
    length = finfo.line_length;
    
    file_add = mmap(NULL, yres_virtual * length, PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (file_add == (void*) -1) {
        perror("Couldn't mmap");
        exit_graphics();
        exit(1);
    }
    
    ioctl(0, TCGETS, &termios);
    termios.c_lflag &= ~(ECHO | ICANON);
    ioctl(0, TCGETS, &termios);
    
    clear_screen();
}

void exit_graphics() {
    ioctl(0, TCGETS, &termios);
    termios.c_lflag |= (ECHO | ICANON);
    ioctl(0, TCGETS, &termios);

    munmap(file_add, yres_virtual * length);

    clear_screen();

    if(!close(fd)) {
        exit(0);
    }
    else {
        perror("Error closing /dev/fb0");
        exit(1);
    }
}

void clear_screen() {
    write(1, "\033[2J", 8);
}

char get_key() {
    char ret = 0;
    struct timeval tim;
    tim.tv_sec = 0;
    
    fd_set set;
    FD_ZERO(&set);
    FD_SET(0, &set);
    
    while (select(FD_SETSIZE, &set, NULL, NULL, &tim)) {
        read(0, &ret, 1);
    }
    //printf("%c", ret);
    
    return ret;
}

void sleep_ms(long ms) {
    struct timespec tim;
    tim.tv_sec = ms / 1000;
    tim.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&tim, NULL);
}

void draw_pixel(int x, int y, color_t color) {
    if (x < 0 || x >= yres_virtual || y < 0 || y >= length) {
        perror("Out of screen bounds");
        exit_graphics();
        exit(1);
    }

    unsigned long vert = (length/2) * y;
    unsigned long horz = x;
    unsigned short *ptr = (file_add + vert + horz);
    *ptr = color;
}

void draw_rect(int x, int y, int width, int height, color_t c) {
    int a = x;
    int b = y;
    
    for (a = x; a <= x + width; a++) {
        draw_pixel(a, b, color);
        draw_pixel(a, b + height, color);
    }
    
    for (b = y; b <= y + height; b++) {
        draw_pixel(a, b, color);
        draw_pixel(a, b + width, color);
    }
}

void draw_text(int x, int y, const char *text, color_t c) {
    
}