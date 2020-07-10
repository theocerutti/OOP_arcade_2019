/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Scoreboard
*/

#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include <iostream>
#include <deque>
#include "../graphicals/ILibGFX.hpp"
#include "ScoreSaver.hpp"

namespace Arcade {
    class Scoreboard {
        public:
            Scoreboard(ScoreSaver &scoreSaver);
            Scoreboard(ScoreSaver &scoreSaver, const std::string &gameTitle);
            ~Scoreboard();
            void drawWith(ILibGFX *lib);
            void setScoreGameToDisplay(const std::string &gameTitle);
        private:
            void initTextNumber();
        private:
            std::string _game;
            ScoreSaver &_scoreSaver;
            std::vector<Arcade::Text> _textNumber;
            std::vector<std::pair<Arcade::Text, Arcade::Text>> _scoreLineTexts;
            Arcade::Text _noScore;
            Arcade::Rect _line1;
            Arcade::Rect _line2;
            Arcade::Rect _line3;
            Arcade::Text _scoreText;
            Arcade::Text _nameText;
            Arcade::Text _nbText;
    };
}

#endif /* !SCOREBOARD_HPP_ */