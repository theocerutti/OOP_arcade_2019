/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** CoreError
*/

#ifndef COREERROR_HPP_
#define COREERROR_HPP_

#include <iostream>

class CoreError : public std::exception {
    public:
        CoreError(std::string const &message);
        const char *what() const noexcept;
    protected:
        std::string _message;
};

#endif /* !COREERROR_HPP_ */