#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "draw.h"
#include "entry.h"
#include "group.h"
#include "tui_text.h"

// main window-related globals
WINDOW *w_main;
Tui_text *main_text = NULL; // keep track of text location - this array will be in order - top to bottom

// hover-related globals
int hover_index; // current hover (as index for Tui_text, usually main_text)
int hover_count; // number of hovers available


// initialize a window
void draw_data(Group **groups, int g_count, Entry **entries, int e_count, WINDOW *w, int start_x, int start_y);

// move hover to a new Tui_text in window w
void hover_move(WINDOW *w, int new_hover_index);

// handle feedback loop
void feedback_loop();

// create windows for options
void draw_options();


void tui_init(Group **groups, int g_count, Entry **entries, int e_count) {
	int input; // capture user input
	
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
	draw_data(groups, g_count, entries, e_count, w_main, 1, 1);
	wrefresh(w_main);

	// initialize hover
	hover_index = 0;
	hover_move(w_main, 0);
	wrefresh(w_main);

	// feedback loop
	feedback_loop();

	tui_end();
	free(*groups);
	free(*entries);
}

void tui_end() {
	endwin();
}



void draw_data(Group **groups, int g_count, Entry **entries, int e_count, WINDOW *w, int start_x, int start_y) {
	int i;
	int j;
	int mt_index = 0; // separate index to keep track of main_text array
	char buf[BUF_LEN];
	
	// initialize main_text
	if(main_text != NULL) free(main_text);
	main_text = malloc(sizeof(Tui_text) * (e_count + g_count));

	// set hover count
	hover_count = e_count + g_count;

	for(i = 0; i < g_count; ++i) {
		// print group
		mvwprintw(w, start_y, start_x, "%s", group_get_name(&((*groups)[i])));

		// save group in main_text array
		tui_text_set_x(&(main_text[mt_index]), start_x);
		tui_text_set_y(&(main_text[mt_index]), start_y);
		tui_text_set_type(&(main_text[mt_index]), GROUP);
		tui_text_set_data(&(main_text[mt_index]), &((*groups)[i]));
		++mt_index;

		++start_y;
		for(j = 0; j < e_count; ++j) {
			// check if an entry belongs to the group
			if(entry_get_group_id(&((*entries)[j])) == group_get_id(&((*groups)[i]))) {
				// print entry
				mvwprintw(w, start_y, start_x, "  ");
				// print date if there is one
				if(entry_get_due_date(&((*entries)[j])) != NULL) {
					memset(buf, 0, BUF_LEN);
					strftime(buf, BUF_LEN, "%a, %m/%d", entry_get_due_date(&((*entries)[j])));
					wprintw(w, "%s: ", buf);
				}
				// print entry title
				wprintw(w, "%s", entry_get_title(&((*entries)[j])));

				// save entry in main_text array
				tui_text_set_x(&(main_text[mt_index]), start_x+2);
				tui_text_set_y(&(main_text[mt_index]), start_y);
				tui_text_set_type(&(main_text[mt_index]), ENTRY);
				tui_text_set_data(&(main_text[mt_index]), &((*entries)[j]));
				mt_index++;

				++start_y;
			}
		}
		++start_y;
	}
}

void hover_move(WINDOW *w, int new_hover_index) {
	// avoid going out of bounds
	if(new_hover_index < 0) new_hover_index = 0;
	if(new_hover_index >= hover_count) new_hover_index = hover_count-1;

	// unset previous hover
	mvwchgat(w, 
			tui_text_get_y(&(main_text[hover_index])), 
			tui_text_get_x(&(main_text[hover_index])), 
			w->_maxx - tui_text_get_x(&(main_text[hover_index])), 
			A_NORMAL, 0, NULL);

	// set new hover
	hover_index = new_hover_index;
	mvwchgat(w, 
			tui_text_get_y(&(main_text[hover_index])), 
			tui_text_get_x(&(main_text[hover_index])), 
			w->_maxx - tui_text_get_x(&(main_text[hover_index])), 
			A_REVERSE, 0, NULL);
}

void feedback_loop() {
	int input;
	bool finish = false; // turn to true to break out

	while(!finish) {
		input = getch();

		switch(input) {
			case 'q':
				finish = true;
				break;

			case KEY_UP:
				hover_move(w_main, hover_index-1);
				wrefresh(w_main);
				break;

			case KEY_DOWN:
				hover_move(w_main, hover_index+1);
				wrefresh(w_main);
				break;

			// Enter key
			case 10:
				draw_options();
				break;

			// debug
				/*
			default:
				wprintw(w_main, "%d", input);
				wrefresh(w_main);
				*/
		}
	}
}

void draw_options() {
	WINDOW *w_options;
	int height; // height of w_options depends on whether it's a group or entry

	if(tui_text_get_type(&(main_text[hover_index])) == GROUP) height = 5;
	else height = 6;
	w_options = newwin(height, 0, 
			tui_text_get_y(&(main_text[hover_index]))+1,
			tui_text_get_x(&(main_text[hover_index])));
	box(w_options, 0, 0);
	refresh();

	// TODO create data structure that maps each of these to a function
	// TODO reuse code for hovering
	// TODO allow for toggling window location (if there is room)
	if(tui_text_get_type(&(main_text[hover_index])) == GROUP) {
		mvwprintw(w_options, 1, 1, "add assignment");
		mvwprintw(w_options, 2, 1, "edit");
		mvwprintw(w_options, 3, 1, "delete");
	}
	else {
		mvwprintw(w_options, 1, 1, "edit");
		mvwprintw(w_options, 2, 1, "clone");
		mvwprintw(w_options, 3, 1, "mark as done");
		mvwprintw(w_options, 4, 1, "delete");
	}

	wrefresh(w_options);

	// TODO feedback_loop should reuse code
	int input = getch();

	// clean options window
	delwin(w_options);
	touchwin(w_main);
	wrefresh(w_main);
}
