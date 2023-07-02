#ifndef DB_H
#define DB_H

/* initialize data.db file
 * return values:
 *   0 -> success
 *   1 -> failure: could not create directory
 *   2 -> failure: could not create file
 */
int db_init();

#endif
