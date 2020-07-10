/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** ICircle
*/

#ifndef ICIRCLE_HPP_
#define ICIRCLE_HPP_

#include "../Vector2.hpp"
#include "../Color.hpp"
#include "AMovable.hpp"

namespace Arcade {
    class ICircle : public AMovable {
        public:
            virtual ~ICircle() = default;

            virtual void setFillColor(const Color &color) = 0;
            virtual const Color &getColor(void) const = 0;

            virtual void setRadius(int radius) = 0;
            virtual int getRadius(void) const = 0;

            virtual bool contains(const Vector2f &point) const = 0;
    };
}

#endif /* !ICIRCLE_HPP_ */
