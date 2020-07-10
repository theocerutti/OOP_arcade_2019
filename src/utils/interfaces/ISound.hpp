/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Image
*/

#ifndef ISOUND_HPP_
#define ISOUND_HPP_

#include <iostream>

namespace Arcade {
    class ISound {
        public:
            virtual ~ISound() = default;
            virtual const std::string &getSound() const = 0;
            virtual size_t getVolume() const = 0;
    };
}


#endif /* !ISOUND_HPP_ */
