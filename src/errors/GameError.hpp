/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** GameError
*/

#ifndef GAMEERROR_HPP_
#define GAMEERROR_HPP_

#include <iostream>

class GameError : public std::exception {
    public:
        GameError(std::string const &message);
        const char *what() const noexcept;
    protected:
        std::string _message;
};

#endif /* !GAMEERROR_HPP_ */