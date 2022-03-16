.PHONY = all run install

OUT = mines
COMPILER = g++
FILES = ./framework/framework.cpp ./gameObject/gameObject.cpp ./button/button.cpp ./field/field.cpp ./map/map.cpp
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

all:
	${COMPILER} ${LIBS} ${FILES} ./main.cpp -o ./${OUT}

run: all
	./${OUT}

install: all
	cp ./${OUT} /usr/bin

clean:
	rm ./${OUT}

debug: all
	gdb ./${OUT}
