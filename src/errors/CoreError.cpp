/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** CoreError
*/

#include "CoreError.hpp"

CoreError::CoreError(std::string const &message) : _message(message)
{
}

const char *CoreError::what() const noexcept
{
    return (_message.c_str());
}