#include <stdio.h>

#include "db.h"
#include "draw.h"
#include "entry.h"
#include "group.h"

int main() {
	Group *groups;
	Entry *entries;

	db_init();
	groups = db_load_groups();
	entries = db_load_entries();

	tui_init();

	return 0;
}
