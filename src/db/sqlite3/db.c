#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"
#include "db.h"

/* return values:
     0 -> success
	 1 -> failure
*/
int create_tables(const char *path);

int db_init() {
	int res;
	char db_path[BUF_LEN];

	// create USER_DATA_DIR if not exists
	res = mkdir(USER_DATA_DIR, S_IRWXU);
	//if(res != 0 && res != EEXIST) return 1; // TODO write a better check incase mkdir fails

	// return if db already exists
	res = access(USER_DATA_PATH, F_OK);
	if(res == 0) return 0;

	// create database with tables
	res = create_tables(USER_DATA_PATH);
	if(res != 0) return 2;

	return 0;
}

int create_tables(const char *path) {
	sqlite3 *db;
	char queries[2][BUF_LEN]; 
	int num_queries = 2;
	char *zErrMsg = NULL; // hold error from sqlite3_exec
	int res;
	int i;

	sprintf(queries[0], 
			"CREATE TABLE IF NOT EXISTS 'Group' ("
			"'ID' int NOT NULL PRIMARY KEY, "
			"'Name' varchar(%d) NOT NULL, "
			"'Desc' varchar(%d) DEFAULT NULL, "
			"'Url' varchar(%d) DEFAULT NULL);",
			BUF_LEN, BUF_LEN, BUF_LEN);

	sprintf(queries[1],
			"CREATE TABLE IF NOT EXISTS 'Entry' ("
			"'ID' int NOT NULL PRIMARY KEY, "
			"'Group_ID' int NOT NULL, " // FIXME might want foreign key constraint
			// TODO add due_date here once it's figure out
			"'Alt_due_date' varchar(%d) DEFAULT NULL, "
			"'Title' varchar(%d) NOT NULL, "
			"'Color' varchar(%d) DEFAULT NULL, "
			"'Highlight' varchar(%d) DEFAULT NULL, "
			"'Done' boolean DEFAULT NULL, "
			"'Url' varchar(%d) DEFAULT NULL);",
			BUF_LEN, BUF_LEN, BUF_LEN, BUF_LEN, BUF_LEN);

	// open the database and run each query
	res = sqlite3_open(path, &db);
	if(res) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	for(i = 0; i < num_queries; ++i) {
		res = sqlite3_exec(db, queries[i], NULL, NULL, &zErrMsg);
		if(res != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
	}

	// wrap-up
	sqlite3_close(db);
	return 0;
}
