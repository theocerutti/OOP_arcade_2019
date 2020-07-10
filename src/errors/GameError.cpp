/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** GameError
*/

#include "GameError.hpp"

GameError::GameError(std::string const &message) : _message(message)
{
}

const char *GameError::what() const noexcept
{
    return (_message.c_str());
}