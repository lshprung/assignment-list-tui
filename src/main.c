#include <stdio.h>

#include "db.h"
#include "draw.h"
#include "group.h"

int main() {
	Group *groups;

	db_init();
	groups = db_load_groups();

	// REMOVE debug
	printf("%d\t%s\t%s\t%s\n", group_get_id(groups), group_get_name(groups), group_get_desc(groups), group_get_url(groups));

	tui_init();

	return 0;
}
