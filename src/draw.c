#include <curses.h>
#include <signal.h>

#include "draw.h"

void tui_init() {
	int input; // capture user input
	
	// set an interrupt to end cleanly
	signal(SIGINT, tui_end);

	// init and set options
	initscr();
	keypad(stdscr, TRUE); // enable arrow keys and other function keys
	cbreak();             // set for interactive curses applications

	input = getch();
	tui_end();
}

void tui_end() {
	endwin();
}
