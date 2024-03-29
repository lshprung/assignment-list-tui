#ifndef ENTRY_H
#define ENTRY_H

#include <stdbool.h>
#include <time.h>

#include "../config.h"

// a group/category for entries to be put in
typedef struct {
	int id; // id from database
	int group_id; // id of corresponding group
	struct tm due_date;
	bool due_date_set;
	char alt_due_date[BUF_LEN];
	char title[BUF_LEN];
	char color[BUF_LEN]; // TODO consider making an enum
	char highlight[BUF_LEN]; // TODO consider making an enum
	bool done;
	char url[BUF_LEN];
} Entry;

// getters
int entry_get_id(Entry *e);
int entry_get_group_id(Entry *e);
struct tm *entry_get_due_date(Entry *e);
char *entry_get_alt_due_date(Entry *e);
char *entry_get_title(Entry *e);
char *entry_get_color(Entry *e);
char *entry_get_highlight(Entry *e);
bool entry_get_done(Entry *e);
char *entry_get_url(Entry *e);

// setters
void entry_set_id(Entry *e, int id);
void entry_set_group_id(Entry *e, int id);
void entry_set_due_date(Entry *e, struct tm *due_date);
void entry_set_alt_due_date(Entry *e, char *alt_due_date);
void entry_set_title(Entry *e, char *title);
void entry_set_color(Entry *e, char *color);
void entry_set_highlight(Entry *e, char *highlight);
void entry_set_done(Entry *e, bool done);
void entry_set_url(Entry *e, char *url);

#endif
