##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

all: compi

compi:
	make -C SDL
	make -C SFML
	make -C NCurses
	make -C LibCaca

clean:
	make clean -C SDL
	make clean -C SFML
	make clean -C NCurses
	make clean -C LibCaca

fclean: clean
	rm -f *.so
	make fclean -C SDL
	make fclean -C SFML
	make fclean -C NCurses
	make fclean -C LibCaca

re : clean fclean all

.SILENT: clean fclean