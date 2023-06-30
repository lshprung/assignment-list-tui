#include <curses.h>
#include <signal.h>

#include "draw.h"

void tui_init() {
	int input; // capture user input
	WINDOW *w_main;
	
	// set an interrupt to end cleanly
	signal(SIGINT, tui_end);

	// init and set options
	initscr();
	keypad(stdscr, TRUE); // enable arrow keys and other function keys
	cbreak();             // set for interactive curses applications
	curs_set(0);             // hide cursor

	// set main window
	w_main = newwin(0, 0, 0, 0);
	box(w_main, 0, 0);
	refresh();
	wrefresh(w_main);

	input = getch();
	tui_end();
}

void tui_end() {
	endwin();
}
