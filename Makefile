##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

SRC = src/main.cpp \
	src/errors/GameError.cpp \
	src/errors/LibError.cpp \
	src/errors/CoreError.cpp \
	src/core/CoreMenu.cpp \
	src/core/Scoreboard.cpp \
	src/core/Engine.cpp \
	src/core/CDir.cpp \
	src/core/DLLoader.cpp \
	src/core/FinishMenu.cpp \
	src/core/ScoreSaver.cpp \
	src/games/AGame.cpp \
	src/utils/Circle.cpp \
	src/utils/Clock.cpp \
	src/utils/Image.cpp \
	src/utils/Rect.cpp \
	src/utils/Text.cpp \
	src/utils/Sound.cpp \
	src/utils/Music.cpp \

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -Wall -Wextra -W -ldl -g -fPIC

CFLAGS = -Wall -Wextra -W -ldl -g

CC = g++

FILE = arcade

all: compi

compi: $(OBJ) graphicals games
	$(CC) $(OBJ) -o $(FILE) $(CFLAGS)

core: $(OBJ)
	$(CC) $(OBJ) -o $(FILE) $(CFLAGS)

games:
	make -C src/games

graphicals:
	make -C src/graphicals

clean:
	rm -f $(OBJ)
	make clean -C src/games
	make clean -C src/graphicals

fclean: clean
	rm -f $(FILE)
	rm -f games/*.so
	rm -f lib/*.so
	make fclean -C src/games
	make fclean -C src/graphicals

re : clean fclean all

.SILENT: clean fclean games graphicals
.PHONY: compi core games graphicals clean fclean re