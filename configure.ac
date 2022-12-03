AC_INIT([assignment-list-tui], [0.1], [lshprung@tutanota.com])
AC_CONFIG_SRCDIR([src/group.h])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Setting default buffer size
bufsize=1024
AC_ARG_ENABLE([custom-bufsize],
			  [AS_HELP_STRING([--enable-custom-bufsize],
							  [set buffer size (default is 1024)])],
							  [bufsize=$enableval])
AC_DEFINE_UNQUOTED([BUF_LEN], [1024], ["Buffer Size"])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT
