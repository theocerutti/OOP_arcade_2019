/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** NCurses
*/

#ifndef L_NCURSES_HPP_
#define L_NCURSES_HPP_

#include "../ILibGFX.hpp"
#include <ncurses.h>

#define TEXT_MODE(colorId) (colorId + Arcade::BWHITE)

class NCurses : public Arcade::ILibGFX {
    public:
        NCurses();
        ~NCurses();

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
        void init_colors() const;
        Arcade::Colors getColorIdFromColor(const Arcade::Color &color);
    private:
        WINDOW *_window;
        const Arcade::Vector2i _sizeRatio;
};

#endif /* !NCURSES_HPP_ */