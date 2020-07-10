/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibCaca
*/

#ifndef L_LIBCACA_HPP_
#define L_LIBCACA_HPP_

#include "../ILibGFX.hpp"
#include <memory>
#include <caca++.h>
#include "MyCaca.hpp"
class LibCaca : public Arcade::ILibGFX {
    public:
        LibCaca();
        ~LibCaca();

        void drawWindow();
        void clear();
        void drawRect(const Arcade::IRect &rect);
        void drawText(const Arcade::IText &text);
        void drawCircle(const Arcade::ICircle &circle);
        void drawImage(const Arcade::IImage &image);
        const Arcade::Event pollEvent();
        bool isOpen() const;
        void closeWindow();
        void initMusic(const Arcade::IMusic &music);
        void closeMusic();
        void playSound(const Arcade::ISound &sound);
        void createWindow(int x, int y, const std::string &title);
    private:
        Arcade::Colors getColorIdFromColor(const Arcade::Color &color);
        std::uint16_t from32To16Bits(const Arcade::Color &color);
    private:
        std::unique_ptr<Canvas> _window;
        std::unique_ptr<Caca> _caca;
        std::unique_ptr<Dither> _bmp;
        Arcade::Vector2f _sizeRatio;
        int _colorsCaca[17][2] = {
            { Arcade::BLACK,  CACA_BLACK },
            { Arcade::RED,  CACA_RED },
            { Arcade::GREEN,  CACA_GREEN },
            { Arcade::YELLOW, CACA_YELLOW },
            { Arcade::BLUE,   CACA_BLUE },
            { Arcade::MAGENTA, CACA_MAGENTA },
            { Arcade::CYAN,   CACA_CYAN },
            { Arcade::WHITE, CACA_WHITE },
            { Arcade::BBLACK, CACA_LIGHTGRAY },
            { Arcade::BRED,   CACA_DARKGRAY },
            { Arcade::BGREEN, CACA_LIGHTGREEN },
            { Arcade::BYELLOW, CACA_YELLOW },
            { Arcade::BBLUE, CACA_LIGHTBLUE },
            { Arcade::BMAGENTA, CACA_LIGHTMAGENTA },
            { Arcade::BCYAN, CACA_LIGHTCYAN },
            { Arcade::BWHITE, CACA_WHITE },
            { Arcade::NONE, CACA_TRANSPARENT }
        };
};

#endif /* !L_LIBCACA_HPP_ */