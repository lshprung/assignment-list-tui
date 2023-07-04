#include <stdio.h>

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

	for(int i = 0; i < group_count; ++i) {
		fprintf(stderr, "group %d:\n", i+1);
		fprintf(stderr, "\t  ID: %d\n", group_get_id(&(groups[i])));
		fprintf(stderr, "\tName: %s\n", group_get_name(&(groups[i])));
		fprintf(stderr, "\tDesc: %s\n", group_get_desc(&(groups[i])));
		fprintf(stderr, "\t Url: %s\n", group_get_url(&(groups[i])));
	}

	/*
	for(int i = 0; i < entry_count; ++i) {
		fprintf(stderr, "entry %d:\n", i+1);
		fprintf(stderr, "\t  ID: %d\n", group_get_id(&(groups[i])));
		fprintf(stderr, "\tName: %s\n", group_get_name(&(groups[i])));
		fprintf(stderr, "\tDesc: %s\n", group_get_desc(&(groups[i])));
		fprintf(stderr, "\t Url: %s\n", group_get_url(&(groups[i])));
	}
	*/

	entries = db_load_entries(&entry_count);

	if(groups == NULL) perror("could not get groups");
	if(entries == NULL) perror("could not get entries");

	tui_init(&groups, group_count, &entries, entry_count);

	return 0;
}
