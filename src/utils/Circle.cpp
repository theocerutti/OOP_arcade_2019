/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Circle
*/

#include "Circle.hpp"

Arcade::Circle::Circle(float posx, float posy, int radius) : ICircle()
{
    setPosition(posx, posy);
    setRadius(radius);
    setFillColor(Arcade::getColor(Arcade::Colors::WHITE));
}

Arcade::Circle::Circle(const Vector2f &pos, int radius) : ICircle()
{
    setPosition(pos);
    setRadius(radius);
    setFillColor(Arcade::getColor(Arcade::Colors::WHITE));
}

Arcade::Circle::~Circle()
{
}

void Arcade::Circle::setFillColor(const Color &color)
{
    this->color = color;
}

const Arcade::Color &Arcade::Circle::getColor(void) const
{
    return (this->color);
}

void Arcade::Circle::setRadius(int radius)
{
    this->radius = radius;
}

int Arcade::Circle::getRadius(void) const
{
    return (this->radius);
}

bool Arcade::Circle::contains(const Vector2f &point) const
{
    return (sqrt(pow(point.x - getPosition().x, 2) + (point.y - getPosition().y)) < this->radius);
}