#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_define([rc_major_version], [1])
m4_define([rc_minor_version], [9])
m4_define([rc_micro_version], [1])
m4_define([rc_version], [rc_major_version.rc_minor_version.rc_micro_version])

AC_PREREQ([2.61])
AC_INIT([RhythmCat], [rc_version], [https://github.com/supercatexpert/RhythmCat2/issues/])
AM_INIT_AUTOMAKE([RhythmCat], [1.9.1])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

RC_MAJOR_VERSION=rc_major_version
RC_MINOR_VERSION=rc_minor_version
RC_MICRO_VERSIOn=rc_micro_version
RC_VERSION=rc_version

AC_SUBST(RC_MAJOR_VERSION)
AC_SUBST(RC_MINOR_VERSION)
AC_SUBST(RC_MICRO_VERSION)
AC_SUBST(RC_VERSION)

AC_DEFINE(RC_MAJOR_VERSION, [rc_major_version],
    [Define to the RhythmCat major version])
AC_DEFINE(RC_MINOR_VERSION, [rc_minor_version],
    [Define to the RhythmCat minor version])
AC_DEFINE(RC_MICRO_VERSION, [rc_micro_version],
    [Define to the RhythmCat micro version])

# Set of available languages.
ALL_LINGUAS="zh_CN zh_TW ja_JP"

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AM_PROG_LIBTOOL
CFLAGS="-Wall -O3 -DINSTALL_PATH=\\\"$datadir/RhythmCat/\\\""

AC_PATH_PROG(DBUSBINDINGTOOL, dbus-binding-tool, no)
if test "$DBUSBINDINGTOOL" = no; then
    AC_MSG_ERROR([dbus-binding-tool not found!])
fi

AC_PATH_PROG(GLIB_GENMARSHAL, glib-genmarshal, no)
if test "$GLIB_GENMARSHAL" = no; then
    AC_MSG_ERROR([glib-genmarshal not found!])
fi

# Check for gtk-doc
GTK_DOC_CHECK([1.14], [--flavour no-tmpl])

# Checks for libraries.
PKG_CHECK_MODULES([GLIB2], [glib-2.0 >= 2.30, gthread-2.0 >= 2.30, \
    gmodule-2.0 >= 2.30, gio-2.0 >= 2.30])
PKG_CHECK_MODULES([GSTREAMER], [gstreamer-0.10 >= 0.10.30, \
    gstreamer-pbutils-0.10 >= 0.10.30 gstreamer-plugins-base-0.10 >= 0.10.30 \
    gstreamer-fft-0.10])
PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.0.0])
PKG_CHECK_MODULES([JSON], [json >= 0.9])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h stdio.h limits.h signal.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([bzero memset realpath strrchr strstr])

# Add the languages which your application supports to po/LINGUAS
GETTEXT_PACKAGE=RhythmCat
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", \
    [Define to the Gettext package name])
AM_GLIB_GNU_GETTEXT
AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])

# Checks for features
AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [enable debug mode]), \
    enable_debug=yes,)
AM_CONDITIONAL(DEBUG_MODE, test "x$enable_debug" = "xyes")

AC_CONFIG_FILES([rhythmcat-2.0.pc])
AC_OUTPUT([Makefile lib/Makefile ui/Makefile \
    docs/Makefile docs/reference/Makefile docs/reference/lib/Makefile \
    docs/reference/lib/version.xml \
    po/Makefile.in po/Makefile])

AC_CONFIG_MACRO_DIR(m4)
