#include <curses.h>
#include <signal.h>
#include <stdlib.h>

#include "draw.h"
#include "entry.h"
#include "group.h"

void draw_data(Group **groups, int g_count, Entry **entries, int e_count, int start_x, int start_y);

void tui_init(Group **groups, int g_count, Entry **entries, int e_count) {
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
	draw_data(groups, g_count, entries, e_count, 1, 1);

	input = getch();
	tui_end();
	free(*groups);
	free(*entries);
}

void tui_end() {
	endwin();
}



void draw_data(Group **groups, int g_count, Entry **entries, int e_count, int start_x, int start_y) {
	int i;
	int j;

	for(i = 0; i < g_count; ++i) {
		mvprintw(start_y, start_x, "%s", group_get_name(&((*groups)[i])));
		++start_y;
		for(j = 0; j < e_count; ++j) {
			if(entry_get_group_id(&((*entries)[j])) == group_get_id(&((*groups)[i]))) {
				mvprintw(start_y, start_x, "\t%s", entry_get_title(&((*entries)[i])));
				++start_y;
			}
		}
		++start_y;
	}
}
