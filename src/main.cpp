/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** main
*/

#include "core/Engine.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "./arcade path_to_graphical_library.so" << std::endl;
        return (84);
    }
    Arcade::Engine engine(av[1]);
    return (engine.run());
}