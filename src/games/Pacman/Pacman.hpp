/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include "../AGame.hpp"
#include "../../utils/Clock.hpp"

class Pacman : public Arcade::AGame {
    public:
        Pacman();
        ~Pacman();
        void init(); // init all variables
        void stop(); // free all varaibles
        void handleEvent(const Arcade::Event &event);
        void update(double delta);
        bool isFinished() const;
        int getScore() const;
        void draw();
    private :
        void updatePlayer(size_t x, size_t y);
        void updateMobs(void);
        void setTexts(void);
        void updateMobDirection(Arcade::Rect mob, size_t x, size_t y, size_t index);
        void superPower(size_t x, size_t y);
        void eatMob(void);
        bool isEaten(void);
        void mobRespawn(void);
        void initAttribute(void);
        Arcade::Circle _player;
        char _direction;
        std::vector<Arcade::Rect> _mobs;
        std::vector<char> _mobsDirection;
        std::vector<Arcade::Rect> _map;
        std::vector<Arcade::Circle> _food;
        std::vector<Arcade::Text> _texts;
        std::vector<std::string> _mapTxt;
        Arcade::Clock _invincibleClock;
        Arcade::Clock _colorClock;
        Arcade::Clock _clock;
        Arcade::Clock _soundClock;
        int _mapOffsetX;
        int _mapOffsetY;
        int _score;
        bool _invincible;
        int _mobColor;
        bool _isFinished;
        int _life;

};

#endif /* !PACMAN_HPP_ */