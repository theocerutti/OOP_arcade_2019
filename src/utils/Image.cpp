/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Image
*/

#include "Image.hpp"

Arcade::Image::Image(const std::string &path) : IImage(), _pixels_rgba(nullptr)
{
    std::string dimensionX;
    std::string dimensionY;
    std::string line;
    std::ifstream file(path, std::ifstream::binary);
    std::ostringstream ss;
    std::string buf;

    if (!file.is_open())
        throw std::runtime_error("Image: can't open '" + path + "'!");
    ss << file.rdbuf();
    buf = ss.str();
    _dimension.x = buf.at(0) | (buf.at(1) << 8);
    _dimension.y = buf.at(2) | (buf.at(3) << 8);
    dimensionX = std::to_string(_dimension.x);
    dimensionY = std::to_string(_dimension.y);
    _pixels_rgba = new unsigned char[_dimension.x * _dimension.y * 4];
    for (size_t i = 0; i < buf.size() - 4; i++)
        _pixels_rgba[i] = buf.at(i + 4);
    if (_dimension.x == 0 || _dimension.y == 0)
        throw std::runtime_error("Image: " + path + ", Width or Height must be positive! (>=0)");
    file.close();
}

Arcade::Image::~Image()
{
}

const Arcade::Vector2i &Arcade::Image::getDimension() const
{
    return (_dimension);
}

const unsigned char *Arcade::Image::getBufferRGBA(unsigned int id) const
{
    id = id;
    return (_pixels_rgba);
}

unsigned int Arcade::Image::countBuffers()
{
    return (_dimension.x / _dimension.y);
}