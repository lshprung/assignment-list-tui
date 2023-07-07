AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = assignment-list-tui
assignment_list_tui_SOURCES = main.c db/$(default_db)/db.c db/$(default_db)/db.h draw.c draw.h entry.c entry.h group.c group.h tui_text.c tui_text.h
assignment_list_tui_LDADD = @CURSES_LIBS@ @SQLITE3_LDFLAGS@
assignment_list_tui_CPPFLAGS = @CURSES_CFLAGS@ @SQLITE3_CFLAGS@ -Idb/$(default_db)
