/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Rect
*/

#include "Rect.hpp"

Arcade::Rect::Rect(float x, float y, float width, float height) : IRect()
{
    setPosition(x, y);
    setDimension(width, height);
    setFillColor(Arcade::getColor(Arcade::Colors::WHITE));
}

Arcade::Rect::Rect(const Vector2f &pos, const Vector2f &dimension) : IRect()
{
    setPosition(pos);
    setDimension(dimension);
    setFillColor(Arcade::getColor(Arcade::Colors::WHITE));
    setOrigin(0, 0);
}

Arcade::Rect::~Rect()
{
}

void Arcade::Rect::setFillColor(const Color &color)
{
    this->color = color;
}

const Arcade::Color &Arcade::Rect::getColor() const
{
    return (color);
}

float Arcade::Rect::getWidth() const
{
    return (dimension.x);
}

float Arcade::Rect::getHeight() const
{
    return (dimension.y);
}

void Arcade::Rect::setWidth(float width)
{
    dimension.x = width;
}

void Arcade::Rect::setHeight(float height)
{
    dimension.y = height;
}

void Arcade::Rect::setDimension(float width, float height)
{
    setWidth(width);
    setHeight(height);
}

void Arcade::Rect::setDimension(const Vector2f &dimension)
{
    this->dimension.x = dimension.x;
    this->dimension.y = dimension.y;
}

const Arcade::Vector2f &Arcade::Rect::getDimension() const
{
    return (dimension);
}

bool Arcade::Rect::contains(const Vector2f &point)
{
    return (point.x >= getPosition().x && point.x <= getPosition().x + getWidth()
    && point.y >= getPosition().y && point.y <= getPosition().y + getHeight());
}