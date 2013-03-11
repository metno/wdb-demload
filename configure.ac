#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(demLoad, 1.1.1, wdb@met.no)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([config/m4])

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
WDB_LIBWDBLOAD_CHECK
#WDB_USER_CREATE

WDB_BOOST_CHECK(1.33.1)

# LOG4CPP
WDB_LOG4CPP_CHECK(1.0)

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

# Print Out Summary of Configuration
AC_MSG_RESULT([ ])
AC_MSG_RESULT([$PACKAGE_NAME $PACKAGE_VERSION])
AC_MSG_RESULT([Configuration:])
AC_MSG_RESULT([-------------------------------------------------------------------------])
AC_MSG_RESULT([ ])
AC_MSG_RESULT([ Database Name:	  $DATABASE_NAME])
AC_MSG_RESULT([ Source Code:      $srcdir])
AC_MSG_RESULT([ Host System:      $host])
AC_MSG_RESULT([  ])
AC_MSG_RESULT([ Prefix:           $prefix])
AC_MSG_RESULT([ Binaries:         $exec_prefix])
AC_MSG_RESULT([ Manuals:          $mandir])
AC_MSG_RESULT([ Data:             $datadir])
AC_MSG_RESULT([ System Config:    $sysconfdir])
AC_MSG_RESULT([ ])
AC_MSG_RESULT([ CPPFLAGS:         $CPPFLAGS])
AC_MSG_RESULT([ LDFLAGS:          $LDFLAGS])
AC_MSG_RESULT([ LIBS:             $LIBS])
AC_MSG_RESULT([  ])
AC_MSG_RESULT([-------------------------------------------------------------------------])
AC_MSG_RESULT([ ])
