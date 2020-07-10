/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Text
*/

#include "Text.hpp"

Arcade::Text::Text(const std::string &text) : IText(), text(text)
{
    setColor(Arcade::getColor(Arcade::Colors::WHITE));
    setPosition(0, 0);
    setPathFont("");
    setTextSize(30);
}

Arcade::Text::Text() : IText()
{
    setText("");
    setColor(Arcade::getColor(Arcade::Colors::WHITE));
    setPosition(0, 0);
    setPathFont("");
    setTextSize(30);
}

Arcade::Text::~Text()
{
}

const std::string &Arcade::Text::getText() const
{
    return (text);
}

void Arcade::Text::setText(const std::string &text)
{
    this->text = text;
}

void Arcade::Text::setColor(const Color &color)
{
    this->color = color;
}

const Arcade::Color &Arcade::Text::getColor() const
{
    return (color);
}

const std::string &Arcade::Text::getPathFont() const
{
    return (pathFont);
}

void Arcade::Text::setPathFont(const std::string &pathFont)
{
    this->pathFont = pathFont;
}

void Arcade::Text::setTextSize(unsigned short textSize)
{
    this->textSize = textSize;
}

unsigned short Arcade::Text::getTextSize() const
{
    return (textSize);
}