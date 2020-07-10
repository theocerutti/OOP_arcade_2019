##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

SRC = SFML.cpp \
	entryPoint.cpp \
	../../errors/LibError.cpp \
	../../errors/CoreError.cpp \
	../../utils/Circle.cpp \
	../../utils/Rect.cpp \
	../../utils/Text.cpp \
	../../utils/Clock.cpp \
	../../utils/Image.cpp \
	../../utils/Sound.cpp \
	../../utils/Music.cpp \

CC = g++

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -fPIC -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

LIBNAME = lib_arcade_sfml.so

all: compi

compi: $(OBJ)
	g++ $(OBJ) $(CXXFLAGS) -shared -o $(LIBNAME) ; mv $(LIBNAME) ../../../lib/

clean:
	rm -f $(LIBNAME)
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE)

re : clean fclean all

.SILENT: fclean clean