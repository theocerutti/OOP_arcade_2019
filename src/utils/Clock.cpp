/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Clock
*/

#include "Clock.hpp"

Arcade::Clock::Clock()
{
    this->clock = std::clock();
}

Arcade::Clock::~Clock()
{

}

double Arcade::Clock::getElapsedTime() const
{
    return (std::clock() - this->clock);
}

void Arcade::Clock::restart()
{
    this->clock = std::clock();
}
