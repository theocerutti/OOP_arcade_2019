/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** entryPoint
*/

#include "LibCaca.hpp"

extern "C" Arcade::ILibGFX *entryPoint(void)
{
    return (new LibCaca());
}