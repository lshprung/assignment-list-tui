#include "tui_text.h"

// getters
int tui_text_get_x(Tui_text *t) {
	return t->start_x;
}

int tui_text_get_y(Tui_text *t) {
	return t->start_y;
}

enum tui_text_type tui_text_get_type(Tui_text *t) {
	return t->type;
}

void *tui_text_get_data(Tui_text *t) {
	return t->data;
}


// setters
void tui_text_set_x(Tui_text *t, int start_x) {
	t->start_x = start_x;
}

void tui_text_set_y(Tui_text *t, int start_y) {
	t->start_y = start_y;
}

void tui_text_set_type(Tui_text *t, enum tui_text_type type) {
	t->type = type;
}

void tui_text_set_data(Tui_text *t, void *data) {
	t->data = data;
}
