/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SFML
*/

#ifndef L_SFML_HPP_
#define L_SFML_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ILibGFX.hpp"
#include <unordered_map>

class SFML : public Arcade::ILibGFX {
    public:
        SFML();
        ~SFML();

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
        sf::RenderWindow _window;
        sf::Music _music;
        sf::Sound _sound;
        sf::SoundBuffer _buffer;
};

#endif /* !SFML_HPP_ */