# Orient
c++ program to automatically change screen orientation based on accelerometer data
* Requires xrandr ````sudo apt-get install xrandr````
* Tested on Ubuntu 14.04
* Should work on any linux distro running Xorg

## Compatibility
* HP Envy x360 - 15-u010dx
* HP Envy - 15t slim quad
* HP Pavillion 15 Gaming
* Other HP devices?
* If your device has an accelerometer and does not work, please send me the details and I will try to add compatilbility 

## Download, Build & Run
````bash
cd ~/
git clone https://github.com/leszakk/orient.git
g++ ~/orient/orient.cpp -o ~/orient/orient
~/orient/orient
````

## Future
* Daemon mode
* Read from config file
* Seperate laptop, tablet, and convertible modes
* More precision using all accelerometer axes to minimize accidental rotations
