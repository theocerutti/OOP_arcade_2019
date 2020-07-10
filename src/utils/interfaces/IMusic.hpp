/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Image
*/

#ifndef IMUSIC_HPP_
#define IMUSIC_HPP_

#include <iostream>

namespace Arcade {
    class IMusic {
        public:
            virtual ~IMusic() = default;
            virtual const std::string &getMusic() const = 0;
            virtual size_t getVolume() const = 0;
            virtual bool isLooping() const = 0;
    };
}

#endif /* !IMUSIC_HPP_ */
