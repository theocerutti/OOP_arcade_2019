/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include "Nibbler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Nibbler::Nibbler() :
    AGame(),
    _generator(time(0))
{
    _mapOffsetX = 150;
    _mapOffsetY = 110;
}

Nibbler::~Nibbler()
{
}

void Nibbler::setTexts(void)
{
    Arcade::Text text1 = Arcade::Text("SCORE :  0");
    text1.setPosition(_mapOffsetX, 60);
    text1.setTextSize(30);
    text1.setPathFont("./assets/fonts/Silicone.ttf");
    Arcade::Text text2 = Arcade::Text("NIBBLER");
    text2.setPosition(_mapOffsetX + 140, -10);
    text2.setTextSize(50);
    text2.setPathFont("./assets/fonts/Silicone.ttf");
    _texts.push_back(text1);
    _texts.push_back(text2);
}

void Nibbler::init()
{
    std::ifstream file;
    std::string line;

    _graphicalLib->initMusic(Arcade::Music("./assets/musics/snake-theme.ogg", 60));
    file.open("assets/levels/Nibbler/map.txt");
    while (file.is_open() && std::getline(file, line))
        _mapTxt.push_back(line);
    setTexts();
    _clock.restart();
    _score = 0;
    _speed = 0.3;
    _size = 20;
    _lastPosition = {0, 0};
    _lastPosition2 = {0, 0};
    _isFinished = false;
    for (size_t i = 0; i < _mapTxt.size(); i++) {
        for (size_t j = 0; j < _mapTxt.at(0).size(); j++) {
            if (_mapTxt.at(i)[j] == 'x') {
                Arcade::Rect rect;
                rect.setFillColor(Arcade::getColor(Arcade::Colors::BBLACK));
                rect.setPosition(j * _size + _mapOffsetX, i * _size + _mapOffsetY);
                rect.setDimension(_size, _size);
                _map.push_back(rect);
            }
        }
    }
    Arcade::Rect player;
    player.setDimension(_size, 10);
    player.setPosition(_size + _mapOffsetX, _size + _mapOffsetY);
    player.setFillColor(Arcade::getColor(Arcade::Colors::BRED));
    _player.push_back(std::pair<Arcade::Rect, char>(player, 'D'));
    _last.push_back('D');
    addApple(_apples, 10);
    addApple(_powers, 3);
}

void Nibbler::stop()
{
    _graphicalLib->closeMusic();
    _isFinished = false;
    _map.clear();
    _apples.clear();
    _texts.clear();
    _mapTxt.clear();
    _player.clear();
    _last.clear();
    _directions.clear();
    _powers.clear();
}

void Nibbler::handleEvent(const Arcade::Event &event)
{
    int x = _player.at(0).first.getPosition().x;
    int y = _player.at(0).first.getPosition().y;

    if (event.type == Arcade::EventType::KEY_PRESS || event.type == Arcade::EventType::KEY_RELEASE) {
        switch (event.key) {
            case Arcade::EventKey::Q:
                _directions.push_back(std::pair<char, Arcade::Vector2i>('Q', {x, y}));
                break;
            case Arcade::EventKey::S:
                _directions.push_back(std::pair<char, Arcade::Vector2i>('S', {x, y}));
                break;
            case Arcade::EventKey::Z:
                _directions.push_back(std::pair<char, Arcade::Vector2i>('Z', {x, y}));
                break;
            case Arcade::EventKey::D:
                _directions.push_back(std::pair<char, Arcade::Vector2i>('D', {x, y}));
                break;
            default: break;
        }
    }
}

void Nibbler::manageBody(int index)
{
    char dir = _player.at(_player.size() - 1).second;

    if (index == 1) {
        Arcade::Rect player;
        player.setDimension(_size, 10);
        player.setPosition(_lastPosition.x, _lastPosition.y);
        player.setFillColor(Arcade::getColor(Arcade::Colors::BRED));
        _player.push_back(std::pair<Arcade::Rect, char>(player, dir));
        _last.push_back(dir);
    } else if (index == 2) {
        std::vector<std::pair<Arcade::Rect, char>> tmp;
        for (auto elem : _player)
            tmp.push_back(std::pair<Arcade::Rect, char>(elem.first, elem.second));
        _player.clear();
        for (size_t i = 0; i < tmp.size() - 1; i++)
            _player.push_back(std::pair<Arcade::Rect, char>(tmp.at(i).first, tmp.at(i).second));
    }
}

void Nibbler::removeAtPosition(size_t index, std::vector<Arcade::Rect> &vect)
{
    std::vector<Arcade::Rect> tmp;

    for (auto elem : vect)
        tmp.push_back(elem);
    vect.clear();
    for (size_t i = 0; i < tmp.size(); i++) {
        if (i == index) continue;
        vect.push_back(tmp.at(i));
    }
}

void Nibbler::removeApple(size_t index)
{
    std::vector<Arcade::Rect> tmp;

    for (auto elem : _apples)
        tmp.push_back(elem);
    _apples.clear();
    for (size_t i = 0; i < tmp.size(); i++) {
        if (i == index) continue;
        _apples.push_back(tmp.at(i));
    }
}

bool Nibbler::onWall(int x, int y)
{
    Arcade::Vector2f pos;

    for (auto &wall : _map) {
        pos = wall.getPosition();
        if (pos == Arcade::Vector2f(x * _size + _mapOffsetX, y * _size + _mapOffsetY))
            return (true);
    }
    return (false);
}

void Nibbler::addApple(std::vector<Arcade::Rect> &vect, int dim)
{
    std::vector<std::pair<int, int>> posIndexEmpty;
    Arcade::Vector2f pos;
    bool posApple = false;
    bool posPlayer = false;
    bool posPower = false;

    for (size_t y = 1; y < _mapTxt.size() - 2; y++) {
        posApple = false;
        posPlayer = false;
        posPower = false;
        for (size_t x = 1; x < _mapTxt.at(y).size() - 2; x++) {
            if (!onWall(x, y)) {
                for (auto &apple : vect) {
                    pos = apple.getPosition();
                    if (pos != Arcade::Vector2f(x * _size + _mapOffsetX, y * _size + _mapOffsetY))
                        posApple = true;
                }
                for (auto &playerBlock : _player) {
                    pos = playerBlock.first.getPosition();
                    if (pos != Arcade::Vector2f(x * _size + _mapOffsetX, y * _size + _mapOffsetY))
                        posPlayer = true;
                }
                for (auto &powerBlock : _powers) {
                    pos = powerBlock.getPosition();
                    if (pos != Arcade::Vector2f(x * _size + _mapOffsetX, y * _size + _mapOffsetY))
                        posPower = true;
                }
                if (_powers.size() == 0)
                    posPower = true;
                if (vect.size() == 0)
                    posApple = true;
                if (posApple && posPlayer && posPower)
                    posIndexEmpty.push_back(std::pair<int, int>(x, y));
            }
        }
    }
    std::shuffle(std::begin(posIndexEmpty), std::end(posIndexEmpty), _generator);
    vect.push_back(Arcade::Rect(posIndexEmpty.at(0).first * _size + _mapOffsetX,
                                   posIndexEmpty.at(0).second * _size + _mapOffsetY,
                                   _size,
                                   dim));
}

bool Nibbler::eat(void)
{
    int x = _player.at(0).first.getPosition().x;
    int y = _player.at(0).first.getPosition().y;
    std::uniform_int_distribution<int> nbApple(1, 4);
    std::uniform_int_distribution<int> show(1, 3);

    for (size_t i = 0; i < _apples.size(); i++) {
        if (_apples.at(i).getPosition().x == x && _apples.at(i).getPosition().y == y) {
            _score += 1;
            _texts.at(0).setText("SCORE :  " + std::to_string(_score));
            if (_speed >= 0.04) _speed -= 0.02;
            manageBody(1);
            removeApple(i);
            _graphicalLib->playSound(Arcade::Sound("./assets/sounds/apple-crunch.wav"));
            if (_apples.size() == 0)
                for (int j = 0; j < nbApple(_generator); j++)
                    addApple(_apples, 10);
            return (true);
        }
    }
    for (size_t i = 0; i < _powers.size(); i++) {
        if (_powers.at(i).getPosition().x == x && _powers.at(i).getPosition().y == y) {
            if (_powers.at(i).getDimension().y == 1) {
                if (_player.size() == 2) {
                    _isFinished = true;
                    return (true);
                }
                _score -= 1;
                _texts.at(0).setText("SCORE :  " + std::to_string(_score));
                removeAtPosition(i, _powers);
                _graphicalLib->playSound(Arcade::Sound("./assets/sounds/apple-crunch.wav"));
                manageBody(2);
            } else if (_powers.at(i).getDimension().y == 2) {
                _speed += 0.04;
                removeAtPosition(i, _powers);
                _graphicalLib->playSound(Arcade::Sound("./assets/sounds/apple-crunch.wav"));
            } else if (_powers.at(i).getDimension().y == 3) {
                _score += 2;
                _texts.at(0).setText("SCORE :  " + std::to_string(_score));
                if (_speed >= 0.04) _speed -= 0.02;
                manageBody(1);
                _lastPosition = _lastPosition2;
                manageBody(1);
                _lastPosition = {_player.at(_player.size() - 1).first.getPosition().x, _player.at(_player.size() - 1).first.getPosition().y};
                removeAtPosition(i, _powers);
                _graphicalLib->playSound(Arcade::Sound("./assets/sounds/apple-crunch.wav"));
            }
            if (_powers.size() != 0) return (true);
            for (int j = 0; j < nbApple(_generator); j++)
                addApple(_powers, show(_generator));
            return (true);
        }
    }
    return (false);
}

bool Nibbler::eatSelf(void)
{
    int x = _player.at(0).first.getPosition().x;
    int y = _player.at(0).first.getPosition().y;

    for (size_t i = 1; i < _player.size(); i++) {
        if (x == _player.at(i).first.getPosition().x && y == _player.at(i).first.getPosition().y) {
            _isFinished = true;
            return (true);
        }
    }
    return (false);
}

void Nibbler::updatePlayer(void)
{
    int x = (_player.at(0).first.getPosition().x - _mapOffsetX) / 20;
    int y = (_player.at(0).first.getPosition().y - _mapOffsetY) / 20;

    _lastPosition = {_player.at(_player.size() - 1).first.getPosition().x, _player.at(_player.size() - 1).first.getPosition().y};
    if (_player.at(0).second == 'Z' && _mapTxt.at(y - 1)[x] != 'x')
        _player.at(0).first.move(0, -1 * _size);
    else if (_player.at(0).second == 'Q' && _mapTxt.at(y)[x - 1] != 'x')
        _player.at(0).first.move(-1 * _size, 0);
    else if (_player.at(0).second == 'S' && _mapTxt.at(y + 1)[x] != 'x')
        _player.at(0).first.move(0, _size);
    else if (_player.at(0).second == 'D' && _mapTxt.at(y)[x + 1] != 'x')
        _player.at(0).first.move(_size, 0);
    else return;
    if (eatSelf())
        return;
    for (size_t i = 1; i < _player.size(); i++) {
        if (_player.at(i).second == 'Z') {
            _player.at(i).first.move(0, -1 * _size);
        } else if (_player.at(i).second == 'Q') {
            _player.at(i).first.move(-1 * _size, 0);
        } else if (_player.at(i).second == 'S') {
            _player.at(i).first.move(0, _size);
        } else if (_player.at(i).second == 'D') {
            _player.at(i).first.move(_size, 0);
        }
    }
    eat();
    _lastPosition2 = _lastPosition;
}

void Nibbler::removeDir(size_t index)
{
    std::vector<std::pair<char, Arcade::Vector2i>> tmp;

    for (auto elem : _directions)
        tmp.push_back(std::pair<char, Arcade::Vector2i>(elem.first, elem.second));
    _directions.clear();
    for (size_t i = 0; i < tmp.size(); i++) {
        if (i == index) continue;
        _directions.push_back(std::pair<char, Arcade::Vector2i>(tmp.at(i).first, tmp.at(i).second));
    }
}

void Nibbler::updateDirections(void)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < _directions.size(); i++) {
        for (size_t j = 0; j < _player.size(); j++) {
            x = _player.at(j).first.getPosition().x;
            y = _player.at(j).first.getPosition().y;
            if (_directions.at(i).second.x == x && _directions.at(i).second.y == y) {
                _player.at(j).second = _directions.at(i).first;
                if (j == _player.size() - 1) {
                    removeDir(i);
                    updateDirections();
                }
                break;
            }
        }
    }
}

void Nibbler::update(double delta)
{
    if (_clock.getElapsedTime() / CLOCKS_PER_SEC >= _speed && !_isFinished) {
        updateDirections();
        updatePlayer();
        if (_player.size() == 1) {
            Arcade::Rect player;
            player.setDimension(_size, 10);
            player.setPosition(_size + _mapOffsetX, _size + _mapOffsetY);
            player.setFillColor(Arcade::getColor(Arcade::Colors::BRED));
            _player.push_back(std::pair<Arcade::Rect, char>(player, 'D'));
            _last.push_back('D');
        }
        _clock.restart();
    }
}

void Nibbler::draw()
{
    for (auto rect : _map)
        _graphicalLib->drawRect(rect);
    for (auto text : _texts)
        _graphicalLib->drawText(text);
    for (auto apple : _apples) {
        Arcade::Image ap("assets/images/Nibbler/apple");
        ap.setPosition(apple.getPosition().x, apple.getPosition().y);
        _graphicalLib->drawImage(ap);
    }
    std::string powerPath = "assets/images/Nibbler/bad";
    for (auto power : _powers) {
        if (power.getDimension().y == 1) powerPath = "assets/images/Nibbler/bad";
        if (power.getDimension().y == 2) powerPath = "assets/images/Nibbler/pilule";
        if (power.getDimension().y == 3) powerPath = "assets/images/Nibbler/banane";
        Arcade::Image powerImg(powerPath);
        powerImg.setPosition(power.getPosition().x, power.getPosition().y);
        _graphicalLib->drawImage(powerImg);
    }
    for (size_t i = 0; i < _player.size(); i++) {
        int x = _player.at(i).first.getPosition().x;
        int y = _player.at(i).first.getPosition().y;
        bool set = false;
        std::string path = "assets/images/Nibbler/body";
        if (_player.at(i).second == 'Z' || _player.at(i).second == 'S')
            path = "assets/images/Nibbler/down";
        for (auto dir : _directions) {
            if (dir.second.x == x && dir.second.y == y) {
                if (i == _player.size() - 1) {
                    if (dir.first == 'Z') path = "assets/images/Nibbler/tail2";
                    else if (dir.first == 'Q') path = "assets/images/Nibbler/tail1";
                    else if (dir.first == 'S') path = "assets/images/Nibbler/tail4";
                    else if (dir.first == 'D') path = "assets/images/Nibbler/tail3";
                    set = true;
                } else if (_last.at(i) == 'Z' && dir.first == 'D') path = "assets/images/Nibbler/angle1";
                else if (_last.at(i) == 'Q' && dir.first == 'S') path = "assets/images/Nibbler/angle1";
                else if (_last.at(i) == 'D' && dir.first == 'S') path = "assets/images/Nibbler/angle2";
                else if (_last.at(i) == 'Z' && dir.first == 'Q') path = "assets/images/Nibbler/angle2";
                else if (_last.at(i) == 'D' && dir.first == 'Z') path = "assets/images/Nibbler/angle3";
                else if (_last.at(i) == 'S' && dir.first == 'Q') path = "assets/images/Nibbler/angle3";
                else if (_last.at(i) == 'S' && dir.first == 'D') path = "assets/images/Nibbler/angle4";
                else if (_last.at(i) == 'Q' && dir.first == 'Z') path = "assets/images/Nibbler/angle4";
            }
        }
        if (i == 0) {
            if (_player.at(i).second == 'Z') path = "assets/images/Nibbler/head3";
            else if (_player.at(i).second == 'Q') path = "assets/images/Nibbler/head2";
            else if (_player.at(i).second == 'S') path = "assets/images/Nibbler/head1";
            else if (_player.at(i).second == 'D') path = "assets/images/Nibbler/head4";
        } else if (i == _player.size() - 1 && !set) {
            if (_player.at(i).second == 'Z') path = "assets/images/Nibbler/tail2";
            else if (_player.at(i).second == 'Q') path = "assets/images/Nibbler/tail1";
            else if (_player.at(i).second == 'S') path = "assets/images/Nibbler/tail4";
            else if (_player.at(i).second == 'D') path = "assets/images/Nibbler/tail3";
        }
        Arcade::Image snake(path);
        snake.setPosition(x, y);
        _graphicalLib->drawImage(snake);
        _last.at(i) = _player.at(i).second;
    }
}

bool Nibbler::isFinished() const
{
    return (_isFinished);
}

int Nibbler::getScore() const
{
    return (_score);
}