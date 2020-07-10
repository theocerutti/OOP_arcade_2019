/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

#include "Color.hpp"
#include "Vector2.hpp"
#include "interfaces/IRect.hpp"

namespace Arcade {
    class Rect : public IRect {
        public:
            Rect(const Vector2f &pos, const Vector2f &dimension);
            Rect(float x = 0, float y = 0, float width = 0, float height = 0);
            ~Rect();

            void setFillColor(const Color &color);
            const Color &getColor() const;

            float getWidth() const;
            float getHeight() const;
            void setWidth(float width);
            void setHeight(float height);

            void setDimension(float width, float height);
            void setDimension(const Vector2f &dimension);
            const Vector2f &getDimension() const;

            bool contains(const Vector2f &point);
        private:
            Vector2f dimension;
            Color color;
    };
}

#endif /* !RECT_HPP_ */