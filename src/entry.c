#include <string.h>

#include "entry.h"

// getters
char *entry_get_alt_due_date(Entry *e) {
	return e->alt_due_date;
}

char *entry_get_title(Entry *e) {
	return e->title;
}

char *entry_get_color(Entry *e) {
	return e->color;
}

char *entry_get_highlight(Entry *e) {
	return e->highlight;
}

char *entry_get_url(Entry *e) {
	return e->url;
}


// setters
void entry_set_alt_due_date(Entry *e, char *alt_due_date) {
	strcpy(e->alt_due_date, alt_due_date);
}

void entry_set_title(Entry *e, char *title) {
	strcpy(e->title, title);
}

void entry_set_color(Entry *e, char *color) {
	strcpy(e->color, color);
}

void entry_set_highlight(Entry *e, char *highlight) {
	strcpy(e->highlight, highlight);
}

void entry_set_url(Entry *e, char *url) {
	strcpy(e->url, url);
}
