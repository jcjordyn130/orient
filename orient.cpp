#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

#define JOY_DEV "/dev/input/js0" //device to read

using namespace std;

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


        sleep(0.5);
        if(axis[0] > 10000)
            system("xrandr -o right");
        else if(axis[0] < -10000)
            system("xrandr -o left");
        else system("xrandr -o normal");


	}while(1==1);

	close( joy_fd );
	return 0;
}
