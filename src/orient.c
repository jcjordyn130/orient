#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <gio/gio.h>
#include <linux/joystick.h>

#include "touchpad.h"

#define JOY_DEV "/dev/input/js0" //device to read

int main(void)
{
    int joy_fd;		// joystick file handle
    int *axis = NULL;
    int num_of_axis = 0;
    int axis_value_0;
    int axis_value_1;

    struct js_event js;
    //const char *schema_id = "org.gnome.settings-daemon.plugins.orientation";


    //checks if gnome-shell orientation plugin is activated
    GSettings *settings = g_settings_new("org.gnome.settings-daemon.plugins.orientation");
    char *name = "";
    if(g_settings_get_boolean(settings, "active"))
    {
        name = "orientation-lock";
        settings = g_settings_new ("org.gnome.settings-daemon.peripherals.touchscreen");
        printf("Gnome-Shell integration enabled\n");
    }
    else
    {
        name = "enable-autorotate";
        settings = g_settings_new ("apps.orient");
        printf("Gnome-Shell integration disabled\n");
    }


    if ((joy_fd = open( JOY_DEV , O_RDONLY)) == -1)
    {
        exit(EXIT_FAILURE);
    }

    // get the number of availble axis
    ioctl(joy_fd, JSIOCGAXES, &num_of_axis);

    // create and fill a variable size array
    axis = (int *) calloc( num_of_axis, sizeof( int ) );

    // use the non blocking mode
    fcntl(joy_fd, F_SETFL, O_NONBLOCK);

    while (1)
    {
        bool autorotate_enabled = g_settings_get_boolean(settings, name);
        //bool autorotate_enabled = g_settings_get_boolean(settings, "enable-autorotate");

        if (!autorotate_enabled)
        {
            //read the joystick state
            //printf("unlocked\n");
            read(joy_fd, &js, sizeof(struct js_event));

            // update the axis value array with the new value
            if ((js.type & ~JS_EVENT_INIT) == JS_EVENT_AXIS)
            {
                axis[js.number] = js.value;
            }

            axis_value_0 = axis[0];
            axis_value_1 = axis[1];

            if (axis_value_1 > 10000)
            {
                // invert the display
                system("xrandr -o inverted");

                // disable the touchpad when inverted
		        set_touchpad_sate("OFF");
            }
            else if (axis_value_0 > 10000)
            {
                // rotate right
                system("xrandr -o right");

                // disable the touchpad
		        set_touchpad_sate("OFF");
            }
            else if (axis_value_0 < -10000)
            {
                // rotate left
                system("xrandr -o left");

                // disable the touchpad
		        set_touchpad_sate("OFF");
            }
            else
            {
                // rotate the screen back to normal
                system("xrandr -o normal");

                // enable the touchpad when in normal mode
		        set_touchpad_sate("ON");
            }
            // 50 millisecond delay
            usleep(1000 * 1000);
        }
        else
        {
            //printf("locked\n");
            // 1 second delay
            usleep(1000 * 1000);
        }


    }

    close(joy_fd);
    free(axis);
    free(settings);

    exit(EXIT_SUCCESS);
}
