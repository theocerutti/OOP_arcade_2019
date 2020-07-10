/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ILibGFXrary
*/

#ifndef ILibGFXRARY_HPP_
#define ILibGFXRARY_HPP_

#include <iostream>
#include <memory>
#include "../errors/LibError.hpp"
#include "../errors/CoreError.hpp"
#include "../utils/Circle.hpp"
#include "../utils/Rect.hpp"
#include "../utils/Text.hpp"
#include "../utils/Event.hpp"
#include "../utils/Vector2.hpp"
#include "../utils/Image.hpp"
#include "../utils/Music.hpp"
#include "../utils/Sound.hpp"

namespace Arcade {
    class ILibGFX {
        public:
            virtual ~ILibGFX() = default;

            virtual void drawWindow() = 0;
            virtual void clear() = 0;
            virtual void drawRect(const IRect &rect) = 0;
            virtual void drawCircle(const ICircle &circle) = 0;
            virtual void drawText(const IText &text) = 0;
            virtual void drawImage(const IImage &image) = 0;
            virtual const Event pollEvent() = 0;
            virtual bool isOpen() const = 0;
            virtual void closeWindow() = 0;
            virtual void initMusic(const IMusic &music) = 0;
            virtual void closeMusic() = 0;
            virtual void playSound(const ISound &sound) = 0;
            virtual void createWindow(int x, int y, const std::string &title) = 0;
    };
}

#endif /* !ILibGFXRARY_HPP_ */