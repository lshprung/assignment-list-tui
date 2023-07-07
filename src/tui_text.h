#ifndef TUI_TEXT_H
#define TUI_TEXT_H

enum tui_text_type { ENTRY, GROUP };

typedef struct tui_text {
	// location of beginning of text in window
	int start_x;
	int start_y;

	// relevant data
	enum tui_text_type type;
	void *data; // should be either Entry * or Group *
} Tui_text;

// getters
int tui_text_get_x(Tui_text *t);
int tui_text_get_y(Tui_text *t);
enum tui_text_type tui_text_get_type(Tui_text *t);
void *tui_text_get_data(Tui_text *t);

// setters
void tui_text_set_x(Tui_text *t, int start_x);
void tui_text_set_y(Tui_text *t, int start_y);
void tui_text_set_type(Tui_text *t, enum tui_text_type type);
void tui_text_set_data(Tui_text *t, void *data);

#endif
