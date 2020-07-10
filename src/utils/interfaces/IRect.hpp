/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** IRect
*/

#ifndef IRECT_HPP_
#define IRECT_HPP_

#include "../Vector2.hpp"
#include "../Color.hpp"
#include "AMovable.hpp"

namespace Arcade {
    class IRect : public AMovable {
        public:
            virtual ~IRect() = default;

            virtual void setFillColor(const Color &color) = 0;
            virtual const Color &getColor() const = 0;

            virtual float getWidth() const = 0;
            virtual float getHeight() const = 0;
            virtual void setWidth(float width) = 0;
            virtual void setHeight(float height) = 0;

            virtual void setDimension(float width, float height) = 0;
            virtual void setDimension(const Vector2f &dimension) = 0;
            virtual const Vector2f &getDimension() const = 0;

            virtual bool contains(const Vector2f &point) = 0;
    };
}

#endif /* !IRECT_HPP_ */
