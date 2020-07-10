/*
** EPITECH PROJECT, 2020
** TEK2
** File description:
** LibError
*/

#ifndef LIBERROR_HPP_
#define LIBERROR_HPP_

#include <iostream>

class LibError : public std::exception {
    public:
        LibError(std::string const &message);
        const char *what() const noexcept;
    protected:
        std::string _message;
};

#endif /* !LIBERROR_HPP_ */