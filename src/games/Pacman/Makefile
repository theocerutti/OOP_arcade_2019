##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

SRC = Pacman.cpp \
	entryPoint.cpp \
	../AGame.cpp \
	../../errors/GameError.cpp \
	../../utils/Circle.cpp \
	../../utils/Rect.cpp \
	../../utils/Text.cpp \
	../../utils/Clock.cpp \
	../../utils/Image.cpp \

CC = g++

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -fPIC

LIBNAME = lib_arcade_pacman.so

all: compi

compi: $(OBJ)
	$(CC) $(OBJ) $(CXXFLAGS) -shared -o $(LIBNAME) ; mv $(LIBNAME) ../../../games/

clean:
	rm -f $(LIBNAME)
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE)

re : clean fclean all

.SILENT: clean fclean
