#include <curses.h>
#include <signal.h>
#include <stdlib.h>

#include "draw.h"

void tui_init(Group **groups, Entry **entries) {
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

	// draw groups and entries
	fprintf(stderr, "groups: %d\n", sizeof(*groups) / sizeof(Group));
	fprintf(stderr, "entries: %d\n", sizeof(*entries) / sizeof(Entry));

	input = getch();
	tui_end();
	free(*groups);
	free(*entries);
}

void tui_end() {
	endwin();
}
