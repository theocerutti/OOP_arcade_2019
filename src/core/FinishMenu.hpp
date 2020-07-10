/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** FinishMenu
*/

#ifndef FinishMenu_HPP_
#define FinishMenu_HPP_

#include <iostream>
#include <vector>
#include <dirent.h>
#include <random>
#include <sstream>
#include <iomanip>
#include "ScoreSaver.hpp"
#include "../graphicals/ILibGFX.hpp"
#include "../utils/Clock.hpp"

namespace Arcade {
    typedef struct FinishEvent_s {
        bool finish;
    } FinishEvent;

    class FinishMenu {
        public:
            FinishMenu();
            ~FinishMenu();
            void setScore(int score);
            const FinishEvent handleEvent(const Event &event, Arcade::ScoreSaver &score, const std::string &game);
            void drawWith(ILibGFX *lib);
            void reload();
            void updateWith(double deltaTime);
        private :
            void randomizeCircleBg();
            Arcade::Text setText(std::string text, int x, int y, size_t size, Arcade::Color color, std::string path);
            std::vector<Arcade::Text> _texts;
            Arcade::Rect _textArea;
            std::vector<Circle> _circlesBg;
            size_t _nbCircleBg;
            std::default_random_engine _generator;
            Clock _clock;
            int _mapOffsetX;
            int _mapOffsetY;
            int _score;

    };
}

#endif /* !FinishMenu_HPP_ */