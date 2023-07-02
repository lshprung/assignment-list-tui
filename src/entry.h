#ifndef ENTRY_H
#define ENTRY_H

#include <stdbool.h>

#include "../config.h"

// a group/category for entries to be put in
typedef struct {
	//TODO due_date
	char alt_due_date[BUF_LEN];
	char title[BUF_LEN];
	char color[BUF_LEN]; // TODO consider making an enum
	char highlight[BUF_LEN]; // TODO consider making an enum
	bool done;
	char url[BUF_LEN];
} Entry;

// getters
char *entry_get_alt_due_date(Entry *e);
char *entry_get_title(Entry *e);
char *entry_get_color(Entry *e);
char *entry_get_highlight(Entry *e);
bool entry_get_done(Entry *e);
char *entry_get_url(Entry *e);

// setters
void entry_set_alt_due_date(Entry *e, char *alt_due_date);
void entry_set_title(Entry *e, char *title);
void entry_set_color(Entry *e, char *color);
void entry_set_highlight(Entry *e, char *highlight);
void entry_set_done(Entry *e, bool done);
void entry_set_url(Entry *e, char *url);

#endif
