#include <string.h>

#include "group.h"

char *group_get_name(Group *g) {
	return g->name;
}

char *group_get_desc(Group *g) {
	return g->desc;
}

char *group_get_url(Group *g) {
	return g->url;
}

void group_set_name(Group *g, char *name) {
	strcpy(g->name, name);
}

void group_set_desc(Group *g, char *desc) {
	strcpy(g->desc, desc);
}

void group_set_url(Group *g, char *url) {
	strcpy(g->url, url);
}
