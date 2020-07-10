/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "interfaces/IImage.hpp"
#include "Vector2.hpp"
#include "Color.hpp"

namespace Arcade {
    class Image : public IImage {
        public:
            Image(const std::string &path);
            ~Image();

            const Vector2i &getDimension() const;

            const unsigned char *getBufferRGBA(unsigned int id = 0) const;
            unsigned int countBuffers();
        private:
            Vector2i _dimension;
            unsigned char *_pixels_rgba;
    };
}

#endif /* !IMAGE_HPP_ */
