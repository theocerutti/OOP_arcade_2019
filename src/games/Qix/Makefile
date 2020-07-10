##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

SRC = Qix.cpp

CC = g++

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -fPIC

LIBNAME = lib_arcade_qix.so

all: compi

compi: $(OBJ)
	$(CC)  $(OBJ) $(CXXFLAGS) -shared -o $(LIBNAME) ; mv $(LIBNAME) ../../../games/

clean:
	rm -f $(LIBNAME)
	rm -f $(OBJ)

fclean: clean
	rm -f $(FILE)

re : clean fclean all

.SILENT: clean fclean