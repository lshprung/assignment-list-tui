#include <string.h>

#include "entry.h"

// getters
int entry_get_id(Entry *e) {
	return e->id;
}

int entry_get_group_id(Entry *e) {
	return e->group_id;
}

struct tm *entry_get_due_date(Entry *e) {
	if(e->due_date_set) return &e->due_date;
	return NULL;
}

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

bool entry_get_done(Entry *e) {
	return e->done;
}

char *entry_get_url(Entry *e) {
	return e->url;
}


// setters
void entry_set_id(Entry *e, int id) {
	e->id = id;
}

void entry_set_group_id(Entry *e, int id) {
	e->group_id = id;
}

void entry_set_due_date(Entry *e, struct tm *due_date) {
	if(due_date != NULL) {
		e->due_date = *due_date;
		e->due_date_set = true;
	}
	else {
		e->due_date = (struct tm){0};
		e->due_date_set = false;
	}
}

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

void entry_set_done(Entry *e, bool done) {
	e->done = done;
}

void entry_set_url(Entry *e, char *url) {
	strcpy(e->url, url);
}
