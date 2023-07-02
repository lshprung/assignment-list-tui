AC_INIT([assignment-list-tui], [0.1], [lshprung@tutanota.com])
AC_CONFIG_SRCDIR([src/group.h])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AX_WITH_CURSES
if test "x$ax_cv_curses" != xyes; then
	AC_MSG_ERROR([requires an X/Open-compatible Curses library])
fi

AX_LIB_SQLITE3
# TODO consider erroring out if sqlite3 does not exist

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
#AC_CHECK_FUNCS([mkdir])

# Setting default buffer size
bufsize=1024
AC_ARG_ENABLE([custom-bufsize],
			  [AS_HELP_STRING([--enable-custom-bufsize],
							  [set buffer size (default is 1024)])],
							  [bufsize=$enableval])
AC_DEFINE_UNQUOTED([BUF_LEN], [${bufsize}], ["Buffer Size"])

# Setting default user data dir and file name
default_user_data_dir="$HOME/.local/share/${PACKAGE_NAME}"
AC_DEFINE_UNQUOTED([USER_DATA_DIR], ["${default_user_data_dir}"], ["User Data Directory"])
default_user_data_path="${default_user_data_dir}/data.db"
AC_DEFINE_UNQUOTED([USER_DATA_PATH], ["${default_user_data_path}"], ["User Data Path"])

# Setting default db to use
default_db="sqlite3"
AC_DEFINE_UNQUOTED([DB], ["${default_db}"], ["Default Database to use"])
AC_SUBST([default_db], [${default_db}])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT

# Print helpful message
cat << EOF

** Configuration summary for ${PACKAGE_NAME} ${PACKAGE_VERSION}

               Prefix: ${prefix}
             Compiler: ${CC} ${CFLAGS} ${CPPFLAGS}
            Libraries: ${LIBS}
          Buffer Size: ${bufsize}
Default User Data Dir: ${default_user_data_dir}
             Database: ${default_db}
EOF
