APPNAME=orient
CFLAGS=`pkg-config --cflags gtk+-3.0`
GTKFLAGS=`pkg-config --libs gtk+-3.0`
FILES=src/orient.c src/touchpad.c
CC=gcc	-g	-Wall

all:	app

app:	$(FILES)
	$(CC)	$(CFLAGS)	-o	bin/$(APPNAME)	$(FILES)	$(GTKFLAGS)

clean:
	rm -rf build/

install:
	cp build/bin/orient /usr/bin/orient/
	cp schemas/apps.orient.gschema.xml /usr/share/glib-2.0/schemas/
	glib-compile-schemas /usr/share/glib-2.0/schemas/
	cp orient.desktop /usr/share/applications/
	cp orient.service /lib/systemd/system/
	cp orient.conf /etc/init/

uninstall:
	rm -rf /usr/bin/orient
	rm -f /usr/share/glib-2.0/schemas/app.orient.gschema.xml
	rm -f /usr/share/applications/orient.desktop
	rm -f /lib/systemd/system/orient.service
	rm -f /etc/init/orient.conf
	glib-compile-schemas /usr/share/glib-2.0/schemas/

