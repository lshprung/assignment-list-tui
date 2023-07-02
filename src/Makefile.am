AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = assignment-list-tui
assignment_list_tui_SOURCES = main.c draw.c draw.h entry.c entry.h group.c group.h db/$(default_db)/db.c db/$(default_db)/db.h
assignment_list_tui_LDADD = @CURSES_LIBS@ @SQLITE3_LDFLAGS@
assignment_list_tui_CPPFLAGS = @CURSES_CFLAGS@ @SQLITE3_CFLAGS@ -Idb/$(default_db)
