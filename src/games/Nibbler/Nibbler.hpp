 /*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "../AGame.hpp"
#include "../../utils/Clock.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <list>

class Nibbler : public Arcade::AGame {
    public:
        Nibbler();
        ~Nibbler();
        void init(); // init all variables
        void stop(); // free all varaibles
        void handleEvent(const Arcade::Event &event);
        void update(double delta);
        bool isFinished() const;
        int getScore() const;
        void draw();
    private:
        void addApple(std::vector<Arcade::Rect> &vect, int dim);
        bool eatSelf(void);
        void manageBody(int index);
        bool eat(void);
        void setTexts(void);
        void updatePlayer(void);
        void updateDirections(void);
        void removeDir(size_t index);
        void removeAtPosition(size_t index, std::vector<Arcade::Rect> &vect);
        void removeApple(size_t index);
        void searchForEmptySpace(const std::vector<Arcade::Rect> &search, std::vector<std::pair<int, int>> &container);
        bool onWall(int x, int y);
    private:
        std::vector<Arcade::Rect> _map;
        std::vector<Arcade::Rect> _apples;
        std::vector<Arcade::Rect> _powers;
        std::vector<Arcade::Text> _texts;
        std::vector<std::string> _mapTxt;
        std::vector<std::pair<Arcade::Rect, char>> _player;
        std::vector<char> _last;
        std::vector<std::pair<char, Arcade::Vector2i>> _directions;
        Arcade::Clock _clock;
        Arcade::Vector2f _lastPosition;
        Arcade::Vector2f _lastPosition2;
        bool _isFinished;
        int _mapOffsetX;
        int _mapOffsetY;
        int _score;
        float _speed;
        int _size;
        std::default_random_engine _generator;
};

#endif /* !NIBBLER_HPP_ */