#include <stdio.h>
#include <string.h>

#include "db.h"
#include "draw.h"
#include "entry.h"
#include "group.h"

int main() {
	Group *groups;
	int group_count;
	Entry *entries;
	int entry_count;

	db_init();
	groups = db_load_groups(&group_count);
	entries = db_load_entries(&entry_count);

	for(int i = 0; i < group_count; ++i) {
		fprintf(stderr, "group %d:\n", i+1);
		fprintf(stderr, "\t  ID: %d\n", group_get_id(&(groups[i])));
		fprintf(stderr, "\tName: %s\n", group_get_name(&(groups[i])));
		fprintf(stderr, "\tDesc: %s\n", group_get_desc(&(groups[i])));
		fprintf(stderr, "\t Url: %s\n", group_get_url(&(groups[i])));
	}

	// DEBUG
	char due_date[BUF_LEN];
	for(int i = 0; i < entry_count; ++i) {
		fprintf(stderr, "entry %d:\n", i+1);
		fprintf(stderr, "\t          ID: %d\n", entry_get_id(&(entries[i])));
		fprintf(stderr, "\t    Group ID: %d\n", entry_get_group_id(&(entries[i])));
		memset(due_date, 0, BUF_LEN);
		if(entry_get_due_date(&(entries[i])) != NULL)
			strftime(due_date, BUF_LEN, "%F", entry_get_due_date(&(entries[i])));
		fprintf(stderr, "\t    Due date: %s\n", due_date);
		fprintf(stderr, "\tAlt due date: %s\n", entry_get_alt_due_date(&(entries[i])));
		fprintf(stderr, "\t       Title: %s\n", entry_get_title(&(entries[i])));
		fprintf(stderr, "\t       Color: %s\n", entry_get_color(&(entries[i])));
		fprintf(stderr, "\t   Highlight: %s\n", entry_get_highlight(&(entries[i])));
		fprintf(stderr, "\t        Done: %d\n", entry_get_done(&(entries[i])));
		fprintf(stderr, "\t         Url: %s\n", entry_get_url(&(entries[i])));
	}

	if(groups == NULL) perror("could not get groups");
	if(entries == NULL) perror("could not get entries");

	tui_init(&groups, group_count, &entries, entry_count);

	return 0;
}
