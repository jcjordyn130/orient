#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <string>

//#include <iostream>

#define JOY_DEV "/dev/input/js0" //device to read

using namespace std;

string state(int);
bool change = false;
string temp;

int main()
{
	int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];
	struct js_event js;

	if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
	{
		printf( "Couldn't open joystick\n" );
		return -1;
	}

	ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
	ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

	axis = (int *) calloc( num_of_axis, sizeof( int ) );
	button = (char *) calloc( num_of_buttons, sizeof( char ) );


	fcntl( joy_fd, F_SETFL, O_NONBLOCK );

	do
	{


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


        //cout << state(axis[0]);

        while(temp == state(axis[0]))
        {
            temp = state(axis[0]);
            sleep(1);
        }


            if(state(axis[0]) == "right")
                system("xrandr -o right");
            else if(state(axis[0]) == "left")
                system("xrandr -o left");
            else if(state(axis[0]) == "normal")
                system("xrandr -o normal");



	}while(1==1);

	close( joy_fd );
	return 0;
}

string state(int axis)
{


    if(axis > 10000)
            return "right";

    else if(axis < -10000)
            return "left";

    else return "normal";

}

