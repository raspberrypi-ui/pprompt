
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#include <libintl.h>

/* Command strings */
#define CHANGE_PASSWD   "echo pi:%s | sudo chpasswd"

/* Controls */
GtkWidget *dlg, *pwentry1_tb, *pwentry2_tb, *pwok_btn, *pwcancel_btn;

/* Password setting */

static void set_passwd (GtkEntry *entry, gpointer ptr)
{
    if (!strlen (gtk_entry_get_text (GTK_ENTRY (pwentry1_tb))) || strcmp (gtk_entry_get_text (GTK_ENTRY (pwentry1_tb)), gtk_entry_get_text (GTK_ENTRY(pwentry2_tb))))
        gtk_widget_set_sensitive (GTK_WIDGET (pwok_btn), FALSE);
    else
        gtk_widget_set_sensitive (GTK_WIDGET (pwok_btn), TRUE);
}


/* The dialog... */

int main (int argc, char *argv[])
{
    GtkWidget *hbox1, *hbox2, *hbox3;
    GtkWidget *lbl1, *lbl2, *lbl3;
    char buffer[128];

#ifdef ENABLE_NLS
    setlocale (LC_ALL, "");
    bindtextdomain ( GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR );
    bind_textdomain_codeset ( GETTEXT_PACKAGE, "UTF-8" );
    textdomain ( GETTEXT_PACKAGE );
#endif

    // GTK setup
    gdk_threads_init ();
    gdk_threads_enter ();
    gtk_init (&argc, &argv);
    gtk_icon_theme_prepend_search_path (gtk_icon_theme_get_default(), PACKAGE_DATA_DIR);

    // create the window
    dlg = gtk_dialog_new ();
    gtk_window_set_title (GTK_WINDOW (dlg), _("Change Password"));
    gtk_window_set_resizable (GTK_WINDOW (dlg), FALSE);
    gtk_window_set_icon_name (GTK_WINDOW (dlg), "dialog-warning");

	// create the message label
    hbox1 = gtk_hbox_new (TRUE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (hbox1), 10);
    lbl1 = gtk_label_new (_("The default password for the 'pi' user is 'raspberry'.\nWe recommend you change this - enter your new password below."));
    gtk_label_set_line_wrap (GTK_LABEL (lbl1), TRUE);
    gtk_label_set_justify (GTK_LABEL (lbl1), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (hbox1), lbl1, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dlg)->vbox), hbox1, TRUE, TRUE, 0);

    // create the first text entry
    hbox2 = gtk_hbox_new (TRUE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (hbox2), 10);
    lbl2 = gtk_label_new (_("Enter new password:"));
    gtk_misc_set_alignment (GTK_MISC (lbl2), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (hbox2), lbl2, TRUE, TRUE, 0);
	pwentry1_tb = gtk_entry_new ();
    g_signal_connect (pwentry1_tb, "changed", G_CALLBACK (set_passwd), NULL);
    gtk_box_pack_start (GTK_BOX (hbox2), pwentry1_tb, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dlg)->vbox), hbox2, TRUE, TRUE, 0);

	// create the second text entry
    hbox3 = gtk_hbox_new (TRUE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (hbox3), 10);
    lbl3 = gtk_label_new (_("Confirm new password:"));
    gtk_misc_set_alignment (GTK_MISC (lbl3), 0, 0.5);
    gtk_box_pack_start (GTK_BOX (hbox3), lbl3, TRUE, TRUE, 0);
    pwentry2_tb = gtk_entry_new ();
    g_signal_connect (pwentry2_tb, "changed", G_CALLBACK (set_passwd), NULL);
    gtk_box_pack_start (GTK_BOX (hbox3), pwentry2_tb, TRUE, TRUE, 5);
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dlg)->vbox), hbox3, TRUE, TRUE, 0);

	// create the buttons
	pwcancel_btn = gtk_dialog_add_button (GTK_DIALOG (dlg), GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
	pwok_btn = gtk_dialog_add_button (GTK_DIALOG (dlg), GTK_STOCK_OK, GTK_RESPONSE_OK);
    gtk_widget_set_sensitive (GTK_WIDGET (pwok_btn), FALSE);
    
    // run the dialog
    gtk_widget_show_all (dlg);
    if (gtk_dialog_run (GTK_DIALOG (dlg)) == GTK_RESPONSE_OK)
    {
        sprintf (buffer, CHANGE_PASSWD, gtk_entry_get_text (GTK_ENTRY (pwentry1_tb)));
        printf ("system this %s\n", buffer);
        //system (buffer);
    }
    gtk_widget_destroy (dlg);
    gdk_threads_leave ();
    printf ("update autostart\n");

    return 0;
}
