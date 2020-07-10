/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Text
*/

#ifndef ITEXT_HPP_
#define ITEXT_HPP_

#include <string>
#include "../Color.hpp"
#include "../Vector2.hpp"
#include "AMovable.hpp"

namespace Arcade {
    class IText : public AMovable {
        public:
            virtual ~IText() = default;

            virtual const std::string &getText() const = 0;
            virtual void setText(const std::string &text) = 0;

            virtual void setColor(const Color &color) = 0;
            virtual const Color &getColor() const = 0;

            virtual const std::string &getPathFont() const = 0;
            virtual void setPathFont(const std::string &pathFont) = 0;

            virtual void setTextSize(unsigned short textSize) = 0;
            virtual unsigned short getTextSize() const = 0;
    };
};

#endif /* !ITEXT_HPP_ */