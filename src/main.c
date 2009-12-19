/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <unistd.h>

#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <gdk/gdkx.h>

#include "demo.h"

char tmp_rc_file[] = "/tmp/gtkrc-2.0-XXXXXX";
GtkWidget* main_dlg = NULL;

gboolean under_lxsession = FALSE;	/* wether lxsession-xsettings daemon is active */

Atom lxsession_atom = 0;

static void check_lxsession()
{
	lxsession_atom = XInternAtom( GDK_DISPLAY(), "_LXSESSION", True );
	if( lxsession_atom != None )
	{
		XGrabServer( GDK_DISPLAY() );
		if( XGetSelectionOwner( GDK_DISPLAY(), lxsession_atom ) )
			under_lxsession = TRUE;
		XUngrabServer( GDK_DISPLAY() );
	}
}

int main (int argc, char *argv[])
{
#ifdef ENABLE_NLS
    bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
#endif

    if( argc >= 3 && strcmp( argv[1], "demo" ) == 0 )
    {
        char* files[] = { argv[3], NULL };
        gtk_rc_set_default_files(files);

        gtk_set_locale ();
        gtk_init (&argc, &argv);

        check_lxsession();
        if( under_lxsession )
        	return 1;

        show_demo( (GdkNativeWindow)atoi( argv[2] ) );
        gtk_main();
        return 0;
    }

    gtk_set_locale ();
    gtk_init (&argc, &argv);

	/* Dirty hack: check if we are under lxsession */
	check_lxsession();

	if( ! under_lxsession )
		mkstemp( tmp_rc_file );

    /* Dirty hack: "gtk-toolbar-style" is installed in class_init of GtkToolbar */
    gtk_widget_destroy( gtk_toolbar_new() );

    main_dlg = main_dlg_new();
    gtk_window_set_icon_name( (GtkWindow*)main_dlg, "preferences-desktop-theme" );

    gtk_main ();

	if( ! under_lxsession )
		unlink( tmp_rc_file );

    return 0;
}

