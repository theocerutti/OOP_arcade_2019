/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** entryPoint
*/

#include "SDL.hpp"

extern "C" Arcade::ILibGFX *entryPoint()
{
    return (new SDL());
}