#include "library.h"

int main(int argc, char *argv[]) {
	int i;

	init_graphics();
	clear_screen();

	//draw_pixel(100, 100, RGB(255, 255, 255));
	draw_rect(100, 100, 50, 50, RGB(255, 255, 255));
	sleep_ms(3000);
	
	clear_screen();
	exit_graphics();

	return (0);
}