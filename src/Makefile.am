bin_PROGRAMS = pprompt

pprompt_CFLAGS = \
	-I$(top_srcdir) \
	-DPACKAGE_LIB_DIR=\""$(libdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/pprompt"\" \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

pprompt_SOURCES = pprompt.c

pprompt_includedir = $(includedir)/pprompt

pprompt_include_HEADERS =

pprompt_LDFLAGS = $(DYNAMIC_FLAGS)
pprompt_DEPENDENCIES_EXTRA = $(BUILTIN_PLUGINS)

pprompt_LDADD = \
		$(BUILTIN_PLUGINS) \
		$(PACKAGE_LIBS) \
		$(X11_LIBS) \
		$(INTLLIBS)

EXTRA_DIST =
