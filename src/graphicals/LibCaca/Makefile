##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

SRC = LibCaca.cpp \
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

CXXFLAGS = -Wall -fPIC -lcaca++

LIBNAME = lib_arcade_libcaca.so

all: compi

compi: $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -shared -o $(LIBNAME) ; mv $(LIBNAME) ../../../lib/

clean:
	rm -f $(LIBNAME)
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE)

re : clean fclean all

.SILENT: fclean clean