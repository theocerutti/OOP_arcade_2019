/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** LibError
*/

#include "LibError.hpp"

LibError::LibError(std::string const &message) : _message(message)
{
}

const char *LibError::what() const noexcept
{
    return (_message.c_str());
}