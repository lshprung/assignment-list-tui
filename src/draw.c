#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "draw.h"
#include "entry.h"
#include "group.h"
#include "tui_text.h"

void draw_data(Tui_text **main_text, Group **groups, int g_count, Entry **entries, int e_count, WINDOW *w, int start_x, int start_y);


void tui_init(Group **groups, int g_count, Entry **entries, int e_count) {
	int input; // capture user input
	Tui_text *main_text = NULL; // keep track of text location - this array will be in order - top to bottom
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

	// draw groups and entries
	draw_data(&main_text, groups, g_count, entries, e_count, w_main, 1, 1);
	wrefresh(w_main);

	input = getch();
	tui_end();
	free(*groups);
	free(*entries);
}

void tui_end() {
	endwin();
}



void draw_data(Tui_text **main_text, Group **groups, int g_count, Entry **entries, int e_count, WINDOW *w, int start_x, int start_y) {
	int i;
	int j;
	int mt_index = 0; // separate index to keep track of main_text array
	char buf[BUF_LEN];
	
	// initialize main_text
	if(*main_text != NULL) free(*main_text);
	*main_text = malloc(sizeof(Tui_text) * (e_count + g_count));

	for(i = 0; i < g_count; ++i) {
		// print group
		mvwprintw(w, start_y, start_x, "%s", group_get_name(&((*groups)[i])));

		// save group in main_text array
		tui_text_set_x(&((*main_text)[mt_index]), start_x);
		tui_text_set_y(&((*main_text)[mt_index]), start_y);
		tui_text_set_type(&((*main_text)[mt_index]), GROUP);
		tui_text_set_data(&((*main_text)[mt_index]), &((*groups)[i]));
		++mt_index;

		++start_y;
		for(j = 0; j < e_count; ++j) {
			// check if an entry belongs to the group
			if(entry_get_group_id(&((*entries)[j])) == group_get_id(&((*groups)[i]))) {
				// print entry
				mvwprintw(w, start_y, start_x, "\t");
				// print date if there is one
				if(entry_get_due_date(&((*entries)[j])) != NULL) {
					memset(buf, 0, BUF_LEN);
					strftime(buf, BUF_LEN, "%a, %m/%d", entry_get_due_date(&((*entries)[j])));
					wprintw(w, "%s: ", buf);
				}
				// print entry title
				wprintw(w, "%s", entry_get_title(&((*entries)[j])));

				// save entry in main_text array
				tui_text_set_x(&((*main_text)[mt_index]), start_x);
				tui_text_set_y(&((*main_text)[mt_index]), start_y);
				tui_text_set_type(&((*main_text)[mt_index]), ENTRY);
				tui_text_set_data(&((*main_text)[mt_index]), &((*entries)[j]));
				mt_index++;

				++start_y;
			}
		}
		++start_y;
	}
}
