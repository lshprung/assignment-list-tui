#include "../config.h"

// a group/category for entries to be put in
typedef struct {
	char name[BUF_LEN];
	char desc[BUF_LEN];
	char url[BUF_LEN];
	//bool column
} Group;

// getters
char *group_get_name(Group *g);
char *group_get_desc(Group *g);
char *group_get_url(Group *g);

// setters
void group_set_name(Group *g, char *name);
void group_set_desc(Group *g, char *desc);
void group_set_url(Group *g, char *url);
