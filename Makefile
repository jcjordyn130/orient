APPNAME=orient
CFLAGS=`pkg-config --cflags gtk+-3.0`
GTKFLAGS=`pkg-config --libs gtk+-3.0`
FILES=src/orient.c src/touchpad.c
CC=gcc	-g	-Wall

all:	app

app:	$(FILES)
	$(CC)	$(CFLAGS)	-o	bin/$(APPNAME)	$(FILES)	$(GTKFLAGS)

clean:
	/bin/rm	-rf	bin/$(NAME);

install:
	mkdir /opt/orient/
	cp bin/orient /opt/orient/
	cp schemas/apps.orient.gschema.xml /usr/share/glib-2.0/schemas/
	glib-compile-schemas /usr/share/glib-2.0/schemas/
	cp orient.desktop ~/.config/autostart/
	cp orient.desktop /usr/share/applications/

uninstall:
	rm -rf /opt/orient/
	rm -f /usr/share/glib-2.0/schemas/app.orient.gschema.xml
	rm -f ~/.config/autostart/orient.desktop
	rm -f /usr/share/applications/orient.desktop
	glib-compile-schemas /usr/share/glib-2.0/schemas/

