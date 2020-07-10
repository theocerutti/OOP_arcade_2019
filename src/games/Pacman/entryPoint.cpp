/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** entryPoint
*/

#include "Pacman.hpp"

extern "C" Arcade::IGame *entryPoint()
{
    return (new Pacman());
}