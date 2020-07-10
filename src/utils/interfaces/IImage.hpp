/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Image
*/

#ifndef IIMAGE_HPP_
#define IIMAGE_HPP_

#include <memory>
#include <string>

#include "../Vector2.hpp"
#include "AMovable.hpp"

namespace Arcade {
    class IImage : public AMovable {
        public:
            virtual ~IImage() = default;

            virtual const Vector2i &getDimension() const = 0;

            virtual const unsigned char *getBufferRGBA(unsigned int id = 0) const = 0;
            virtual unsigned int countBuffers() = 0;
    };
}


#endif /* !IIMAGE_HPP_ */