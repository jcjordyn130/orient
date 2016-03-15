# Orient
This application will automatically change screen orientation for gnome shell and other desktop environments
* Disables touchpad when rotated
* Rotation can be locked with button in Gnome Shell
* Automatically starts after login

###Compatibility
* HP Envy x360 - 15-u010dx
* HP Envy - 15t slim quad
* HP Pavillion 15 Gaming Laptop

###Package Requirements
* X11 for xinput and xrandr
* gio for gsettings

###Building
Run make in the cloned directory
````bash
cd ./orient/
make

````

###Installing the application
To install run:
````bash
sudo make install

````

To remove run
````bash
sudo make uninstall

````

###Locking Orientation

#####With Gnome Shell
Run this to enable the lock button in the top right corner menu of gnome shell
````bash
gsettings set org.gnome.settings-daemon.plugins.orientation active true
````

#####With other desktop environment
To lock in current orientation, run the commando below.
````bash
gsettings set apps.orient lock-orientation true

````

To disable orientation lock, run the command below.
````bash
gsettings set apps.orient lock-orientation false

````

###Todo
* Seperate laptop, tablet, and convertible mode
* More precision using all accelerometers to minimize accidental rotations
* Gnome shell extention that exposes the gsettings and indicates if the
  application is running
* Create a AUR package
* Create a ubuntu and debian package
* Wayland support
