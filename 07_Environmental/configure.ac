#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [0.0.1], [])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init], [], [AC_MSG_ERROR([Failed to find rhash_library_init])])
AC_CHECK_LIB([rhash], [rhash_file], [], [AC_MSG_ERROR([Failed to find rhash_file])])
AC_CHECK_LIB([rhash], [rhash_msg], [], [AC_MSG_ERROR([Failed to find rhash_msg])])
AC_CHECK_LIB([rhash], [rhash_print_bytes], [], [AC_MSG_ERROR([Failed to find rhash_print_bytes])])
AC_CHECK_LIB([rhash], [rhash_get_digest_size], [], [AC_MSG_ERROR([Failed to find rhash_get_digest_size])])
AC_CHECK_LIB([rhash], [rhash_get_name], [], [AC_MSG_ERROR([Failed to find rhash_get_name])])
AC_CHECK_LIB([readline], [readline], [], [AC_MSG_ERROR([Failed to find readline])])

# Checks for header files.
AC_CHECK_HEADERS([rhash.h], [], [AC_MSG_ERROR([Failed to locate rhash.h])])
AC_CHECK_HEADERS([readline/readline.h readline/history.h], [], [AC_MSG_ERROR([Failed to locate readline.h])])
AC_CHECK_HEADERS([strings.h], [], [AC_MSG_ERROR([Failed to locate strings.h])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])

AC_ARG_ENABLE([readline], AS_HELP_STRING([--enable-readline], [use readline]), AC_DEFINE(USE_READLINE, [1], [readline mode]), [use_readline="false"])
AS_IF([test "$use_readline" = "false"], [AC_SUBST(LIBS, ["-lrhash"])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
