/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGame
*/

#include "AGame.hpp"

Arcade::AGame::AGame() : IGame(), _graphicalLib(nullptr)
{
}

void Arcade::AGame::setGFXLibrary(ILibGFX *graphicalLib)
{
    _graphicalLib = graphicalLib;
}