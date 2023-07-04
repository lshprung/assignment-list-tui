#ifndef DB_H
#define DB_H

/* initialize data.db file
 * return values:
 *   0 -> success
 *   1 -> failure: could not create directory
 *   2 -> failure: could not create file
 */

#include "entry.h"
#include "group.h"

int db_init();

Group *db_load_groups(int *group_count);

Entry *db_load_entries(int *entry_count);

#endif
