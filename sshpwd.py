from pathlib import Path

# If the flag doesn't exist
if not Path("/run/sshwarn").exists():
    # Exit early
    raise SystemExit

# Init gettext
from gettext import gettext, bindtextdomain
bindtextdomain('pprompt')

# Load Gtk
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk, Gio, GLib

from getpass import getuser


# Callback for clicked link
def activate(label, uri, dlg):
    # We only handle links to 'config', let Gtk handle anything else
    if uri != 'config':
        return False

    # We are launching 'rc_gui'
    app = Gio.AppInfo.create_from_commandline('rc_gui', None, 0)
    # On the current display
    screen = label.get_screen()
    if screen:
        display = screen.get_display()
    else:
        display = Gdk.Display.get_default()
    ctx = display.get_app_launch_context()
    if screen:
        ctx.set_screen(screen)

    try:
        # Start the program
        app.launch([], ctx)

        # Close the dialog
        def close():
            dlg.destroy()
            return GLib.SOURCE_REMOVE
        GLib.idle_add(close)
    except:
        # Error message when rc_gui failed to start
        msg = gettext('Failed to start Raspberry Pi Configuration')
        # Modal error dialog
        err = Gtk.MessageDialog(dlg,
                                Gtk.DialogFlags.MODAL,
                                Gtk.MessageType.ERROR,
                                Gtk.ButtonsType.CLOSE,
                                msg)
        # Close when button pressed
        err.connect("response", lambda d, r: d.destroy())
        # Close parent with this one
        err.connect("destroy", lambda d: dlg.destroy())
        # Show this dialog
        err.show()
    # We handled the link
    return True


# Dialog title
title = gettext('Change Password')
# Main message
msg = gettext('SSH is enabled and the default password for the \'pi\' user '
              'has not been changed')
# Check the current user
if getuser() == 'pi':
    # They are pi, include link to open rc_gui
    info = gettext('This is a <b>security risk</b>, please run '
                   '<a href="config">Raspberry Pi Configuration</a> '
                   'to set a new password.')
else:
    # They aren't pi, tell them to switch to pi and run rc_gui
    info = gettext('This is a <b>security risk</b>, please login as the '
                   '\'pi\' user and run Raspberry Pi Configuration to set a '
                   'new password.')


# Setup the dialog, we don't have a parent so a warning will be logged
# It's a warning with a [Close] button, pango text & 400 wide
dlg = Gtk.MessageDialog(message_type=Gtk.MessageType.WARNING,
                        buttons=Gtk.ButtonsType.CLOSE,
                        text=title,
                        secondary_text="{}\n\n{}".format(msg, info),
                        secondary_use_markup=True,
                        width_request=400)
# When closed quit the program
dlg.connect("destroy", Gtk.main_quit)
# When a button is clicked close the dialog
dlg.connect("response", lambda d, r: d.destroy())


def connect_activate(lbl):
    lbl.connect('activate-link', activate, dlg)


# Connect to activate-link on the label
dlg.get_message_area().foreach(connect_activate)

# Show the dialog
dlg.show()
# Start the mainloop
Gtk.main()
