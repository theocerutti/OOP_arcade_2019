##
## EPITECH PROJECT, 2019
## Makefile
## File description:
##
##

all: compi

compi:
	make -C Nibbler
	make -C Pacman
	make -C SolarFox
	make -C Qix
	make -C Centipede

clean:
	make clean -C Nibbler
	make clean -C Pacman
	make clean -C SolarFox
	make clean -C Qix
	make clean -C Centipede

fclean: clean
	rm -f *.so
	make fclean -C Nibbler
	make fclean -C Pacman
	make fclean -C SolarFox
	make fclean -C Qix
	make fclean -C Centipede

re : clean fclean all

.SILENT: clean fclean