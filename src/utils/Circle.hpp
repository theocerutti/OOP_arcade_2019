/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Ellipse
*/

#ifndef ELLIPSE_HPP_
#define ELLIPSE_HPP_

#include <cmath>
#include "Vector2.hpp"
#include "Color.hpp"
#include "interfaces/ICircle.hpp"

namespace Arcade {
    class Circle : public ICircle {
        public:
            Circle(float posx = 0, float posy = 0, int radius = 0);
            Circle(const Vector2f &pos, int radius = 0);
            ~Circle();

            void setFillColor(const Color &color);
            const Color &getColor(void) const;

            void setRadius(int radius);
            int getRadius(void) const;

            bool contains(const Vector2f &point) const;
        private:
            int radius;
            Color color;
    };
};

#endif /* !ELLIPSE_HPP_ */