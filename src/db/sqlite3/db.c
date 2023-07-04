#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
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

// callback function prototypes
int group_count_callback(void *first_arg, int argc, char **argv, char **azColName);
int entry_count_callback(void *first_arg, int argc, char **argv, char **azColName);
int load_groups_callback(void *first_arg, int argc, char **argv, char **azColName);
int load_entries_callback(void *first_arg, int argc, char **argv, char **azColName);

// globals
static int callback_index; // keep track of index when filling arrays using callback functions

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

Group *db_load_groups(int *group_count) {
	Group *output;
	sqlite3 *db;
	const char *count_query = "SELECT COUNT(*) FROM 'Group'";
	const char *query = "SELECT ROWID, * FROM 'Group'";
	char *zErrMsg = NULL; // hold error from sqlite3_exec
	int res;

	res = sqlite3_open(USER_DATA_PATH, &db);
	if(res) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return NULL;
	}
	
	// count rows in table
	res = sqlite3_exec(db, count_query, group_count_callback, &output, &zErrMsg);
	if(res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return NULL;
	}

	// do select query
	callback_index = 0;
	res = sqlite3_exec(db, query, load_groups_callback, &output, &zErrMsg);
	if(res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return NULL;
	}
	*group_count = callback_index;

	sqlite3_close(db);
	return output;
}

Entry *db_load_entries(int *entry_count) {
	Entry *output;
	sqlite3 *db;
	const char *count_query = "SELECT COUNT(*) FROM 'Entry'";
	const char *query = "SELECT ROWID, * FROM 'Entry'";
	char *zErrMsg = NULL; // hold error from sqlite3_exec
	int res;

	res = sqlite3_open(USER_DATA_PATH, &db);
	if(res) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return NULL;
	}
	
	// count rows in table
	res = sqlite3_exec(db, count_query, entry_count_callback, &output, &zErrMsg);
	if(res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return NULL;
	}

	// do select query
	callback_index = 0;
	res = sqlite3_exec(db, query, load_entries_callback, &output, &zErrMsg);
	if(res != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return NULL;
	}
	*entry_count = callback_index;

	sqlite3_close(db);
	return output;
}



int create_tables(const char *path) {
	sqlite3 *db;
	char queries[2][BUF_LEN]; 
	int num_queries = 2;
	char *zErrMsg = NULL; // hold error from sqlite3_exec
	int res;
	int i;

	// Group table - stores groups of entries
	// note: in sqlite, use rowid, don't create id column
	sprintf(queries[0], 
			"CREATE TABLE IF NOT EXISTS 'Group' ("
			"'Name' varchar(%d) NOT NULL, "
			"'Desc' varchar(%d) DEFAULT NULL, "
			"'Url' varchar(%d) DEFAULT NULL);",
			BUF_LEN, BUF_LEN, BUF_LEN);

	// Entry table - stores individual entries
	sprintf(queries[1],
			"CREATE TABLE IF NOT EXISTS 'Entry' ("
			"'Group_ID' int NOT NULL, " // FIXME might want foreign key constraint
			"'Due_date' date DEFAULT NULL, "
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

// callback functions
int group_count_callback(void *first_arg, int argc, char **argv, char **azColName) {
	Group **groups = (Group **) first_arg;
	*groups = malloc(sizeof(Group) * argc);

	return 0;
}

int entry_count_callback(void *first_arg, int argc, char **argv, char **azColName) {
	Entry **entries = (Entry **) first_arg;
	*entries = malloc(sizeof(Entry) * argc);

	return 0;
}

int load_groups_callback(void *first_arg, int argc, char **argv, char **azColName) {
	Group **groups = (Group **) first_arg;

	// check that enough arguments were passed
	if(argc < 4) {
		fprintf(stderr, "Error: not enough rows returned in 'Group' table\n");
		return 1;
	}

	group_set_id(&((*groups)[callback_index]), (argv[0] ? atoi(argv[0]) : 0));
	group_set_name(&((*groups)[callback_index]), (argv[1] ? argv[1] : ""));
	group_set_desc(&((*groups)[callback_index]), (argv[2] ? argv[2] : ""));
	group_set_url(&((*groups)[callback_index]), (argv[3] ? argv[3] : ""));

	++callback_index;
	return 0;
}

int load_entries_callback(void *first_arg, int argc, char **argv, char **azColName) {
	Entry **entries = (Entry **) first_arg;

	// check that enough arguments were passed
	if(argc < 7) {
		fprintf(stderr, "Error: not enough rows returned in 'Entry' table\n");
		return 1;
	}

	entry_set_id(&((*entries)[callback_index]), (argv[0] ? atoi(argv[0]) : 0));
	fprintf(stderr, "time format: %s\n", (argv[1] ? argv[1] : ""));
	//entry_set_due_date(&((*entries)[callback_index]), (argv[1] ? argv[1] : "")); // TODO
	entry_set_alt_due_date(&((*entries)[callback_index]), (argv[2] ? argv[2] : ""));
	entry_set_title(&((*entries)[callback_index]), (argv[3] ? argv[3] : ""));
	entry_set_color(&((*entries)[callback_index]), (argv[4] ? argv[4] : ""));
	entry_set_highlight(&((*entries)[callback_index]), (argv[5] ? argv[5] : ""));
	entry_set_done(&((*entries)[callback_index]), (argv[6] ? argv[6] : false));
	entry_set_url(&((*entries)[callback_index]), (argv[7] ? argv[7] : ""));

	++callback_index;
	return 0;
}
