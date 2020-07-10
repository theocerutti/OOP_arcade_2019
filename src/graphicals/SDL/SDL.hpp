/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDL
*/

#ifndef SDL_HPP_
#define SDL_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../ILibGFX.hpp"
#include <map>

class SDL : public Arcade::ILibGFX {
    public:
        SDL();
        ~SDL();
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
        SDL_Color getColorFromArcadeColor(const Arcade::Color &color) const;
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
};

#endif /* !SDL_HPP_ */