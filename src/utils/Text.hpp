/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <iostream>
#include "./interfaces/IText.hpp"

namespace Arcade {
    class Text : public IText {
        public:
            Text(const std::string &text);
            Text();
            ~Text();

            const std::string &getText() const;
            void setText(const std::string &text);

            void setColor(const Color &color);
            const Color &getColor() const;

            const std::string &getPathFont() const;
            void setPathFont(const std::string &pathFont);

            void setTextSize(unsigned short textSize);
            unsigned short getTextSize() const;

        protected:
            std::string text;
            Color color;
            unsigned short textSize;
            std::string pathFont;
    };
};

#endif /* !TEXT_HPP_ */