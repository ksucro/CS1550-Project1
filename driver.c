#include <stdio.h>

int main(int argc, char *argv[]) {
	int i;

	init_graphics();
	clear_screen();

	sleep_ms(100);
	
	clear_screen();
	exit_graphics();

	return (0);
}