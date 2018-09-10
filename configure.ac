AC_PREREQ(2.53)
AC_CONFIG_MACRO_DIR([m4])
AC_INIT(pprompt,0.10,http://raspberrypi.org/)
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects no-dist-gzip dist-xz])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Support silent build rules. Disable by either passing --disable-silent-rules
# to configure or passing V=1 to make
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_INSTALL
AC_PROG_LN_S
IT_PROG_INTLTOOL([0.40.0], [no-xml])
AM_PROG_CC_C_O
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

# Checks for libraries.
pkg_modules="$pkg_modules gtk+-3.0 >= 3.10.0"

PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

PACKAGE_CFLAGS="$PACKAGE_CFLAGS $ADDITIONAL_FLAGS"
PACKAGE_LIBS="$PACKAGE_LIBS"

# Generate po/LINGUAS on the fly rather than relying on translators
# to maintain it manually. This also overcome the problem that Transifex
# cannot add a language to po/LINGUAS if a new po file is submitted.
rm -f $srcdir/po/LINGUAS
for po_file in `ls $srcdir/po/*.po | sort`;
do
    lang=`echo "$po_file" | sed "s|.*/po/\(.*\)\.po|\1|g"`
    echo $lang >> $srcdir/po/LINGUAS
done

GETTEXT_PACKAGE=pprompt
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])

AM_GLIB_GNU_GETTEXT

dnl Fix invalid sysconfdir when --prefix=/usr
if test `eval "echo $sysconfdir"` = /usr/etc
then
    sysconfdir=/etc
fi

AC_CONFIG_FILES([
    Makefile
    po/Makefile.in
])
AC_OUTPUT

echo
echo pprompt ......................... : Version $VERSION
echo
echo Prefix........................... : $prefix
echo System config directory.......... : `eval "echo $sysconfdir"`
echo

if test x"$sysconfdir" != x'/etc'; then
    echo
    echo 'Warning: sysconfdir is not /etc. It might be not what you want.'
    echo 'Please consider passing --sysconfdir=/etc to configure.'
fi
