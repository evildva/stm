#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([stm32f4_bin], [1.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([user/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall foreign])
# Checks for programs.
AC_PROG_CC([arm-none-eabi-gcc])
AM_PROG_AS

# Checks for libraries.
AC_PROG_RANLIB([libspl.a])
# Checks for header files.
AC_CHECK_HEADERS([stddef.h])
# Checks for typedefs, structures, and compiler characteristics.
AC_FUNC_OBSTACK
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_FSEEKO
AC_CONFIG_FILES([
 Makefile
 spl/src/Makefile
 user/Makefile
])
AC_CHECK_FUNCS([getdelim])

AC_OUTPUT
