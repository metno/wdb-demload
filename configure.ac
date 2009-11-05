#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(demLoad, 0.9.5, wdb@met.no)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADER([config.h])

AC_PROG_LIBTOOL

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S


# Checks for libraries.
WDB_CHECK
WDB_LOADERBASE_CHECK


WDB_BOOST_CHECK(1.33.1)

# LOG4CPP
WDB_LOG4CPP_CHECK(0.3.5rc3)

WDB_PROJ_CHECK

WDB_PQXX_CHECK(2.6.8)


WDB_DOCBOOK_CHECK

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T


AM_INIT_AUTOMAKE(-Wall -Werror subdir-objects)

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
