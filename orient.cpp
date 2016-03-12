#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <string>

#define JOY_DEV "/dev/input/js0"

using namespace std;

class orient {
public:
    orient();
private:
    bool change = false;
    int state(int);
    int temp = 0;

};

int main()
{
    orient start;
    return 0;
}

orient::orient()
{
        int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
        char *button=NULL, name_of_joystick[80];
        struct js_event js;


	do
	{



        if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
        {
            printf( "Couldn't open joystick\n" );
        }

        ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
        ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
        ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

        axis = (int *) calloc( num_of_axis, sizeof( int ) );
        button = (char *) calloc( num_of_buttons, sizeof( char ) );


        fcntl( joy_fd, F_SETFL, O_NONBLOCK );




            	///read the joystick state
		read(joy_fd, &js, sizeof(struct js_event));

			///see what to do with the event
		switch (js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS:
				axis   [ js.number ] = js.value;
				break;
			case JS_EVENT_BUTTON:
				button [ js.number ] = js.value;
				break;
		}







    ////////////////////
    ///read the joystick state
    read(joy_fd, &js, sizeof(struct js_event));
        ///see what to do with the event
    switch (js.type & ~JS_EVENT_INIT)
    {
        case JS_EVENT_AXIS:
            axis   [ js.number ] = js.value;
            break;
        case JS_EVENT_BUTTON:
            button [ js.number ] = js.value;
            break;
    }
    ////////////////////
    usleep(10000);
    if(temp != state(axis[0]))
        change = true;
    else change = false;

    if(change)
    {
        if(state(axis[0]) == 1)
            system("xrandr -o right");
        else if(state(axis[0]) == 2)
            system("xrandr -o left");
        else if(state(axis[0]) == 0)
            system("xrandr -o normal");
    }
    temp = state(axis[0]);

    close( joy_fd );
    delete axis;
    delete button;

	}while(1==1);


}

int orient::state(int axis)
{
    if(axis > 10000) //right
            return 1;

    else if(axis < -10000) //left
            return 2;

    else return 0;
}
