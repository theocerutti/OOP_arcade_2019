/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman() : AGame()
{
    _score = 0;
    _mapOffsetX = 200;
    _mapOffsetY = 120;
}

Pacman::~Pacman()
{
}

void Pacman::setTexts(void)
{
    Arcade::Text text1 = Arcade::Text("SCORE :  0");
    text1.setPosition(_mapOffsetX, 75);
    text1.setTextSize(30);
    text1.setPathFont("./assets/fonts/Silicone.ttf");
    Arcade::Text life = Arcade::Text("LIFE");
    life.setPosition(_mapOffsetX + 250, 75);
    life.setTextSize(30);
    life.setPathFont("./assets/fonts/Silicone.ttf");
    Arcade::Text text2 = Arcade::Text("PACMAN");
    text2.setPosition(_mapOffsetX + 100, 10);
    text2.setTextSize(50);
    text2.setPathFont("./assets/fonts/Silicone.ttf");
    _texts.push_back(text1);
    _texts.push_back(text2);
    _texts.push_back(life);
}

void Pacman::initAttribute(void)
{
    std::ifstream file;
    std::string line;

    file.open("assets/levels/Pacman/map");
    while (file.is_open() && std::getline(file, line))
        _mapTxt.push_back(line);
    _isFinished = false;
    _score = 0;
    _life = 3;
    _direction = 'D';
    _invincible = false;
    _clock.restart();
    _colorClock.restart();
    _invincibleClock.restart();
    _mobColor = 1;
    _isFinished = false;
}

void Pacman::init()
{
    _graphicalLib->initMusic(Arcade::Music("./assets/musics/pacman-theme.ogg", 60));
    initAttribute();
    if (!_map.empty()) return;
    for (size_t i = 0; i < _mapTxt.size(); i++) {
        for (size_t j = 0; j < _mapTxt.size(); j++) {
            if (_mapTxt.at(i)[j] == 'x') {
                Arcade::Rect rect;
                rect.setFillColor(Arcade::getColor(Arcade::Colors::GREEN));
                rect.setPosition(j * 20 + _mapOffsetX, i * 20 + _mapOffsetY);
                rect.setDimension(20, 20);
                _map.push_back(rect);
            }
            Arcade::Circle circle;
            circle.setPosition(j * 20 + 7 + _mapOffsetX, i * 20 + 7 + _mapOffsetY);
            circle.setFillColor(Arcade::getColor(Arcade::Colors::YELLOW));
            if (_mapTxt.at(i)[j] == ' ' || _mapTxt.at(i)[j] == 'M' || _mapTxt.at(i)[j] == 'o') circle.setRadius(3);
            else circle.setRadius(0);
            if (_mapTxt.at(i)[j] == 'o') {
                circle.setPosition(j * 20 + _mapOffsetX, i * 20 + _mapOffsetY);
                circle.setFillColor(Arcade::getColor(Arcade::Colors::BWHITE));
                circle.setRadius(5);
            }
            _food.push_back(circle);
            if (_mapTxt.at(i)[j] == 'M') {
                Arcade::Rect mob;
                mob.setPosition(j * 20 + _mapOffsetX, i * 20 + _mapOffsetY);
                mob.setFillColor(Arcade::getColor(Arcade::Colors::RED));
                mob.setDimension(16, 16);
                _mobs.push_back(mob);
                _mobsDirection.push_back('D');
            }
        }
    }
    _player.setFillColor(Arcade::getColor(Arcade::Colors::MAGENTA));
    _player.setPosition(20 + _mapOffsetX, 20 + _mapOffsetY);
    _player.setRadius(10);
    setTexts();
}

void Pacman::stop()
{
    _graphicalLib->closeMusic();
    _mobs.clear();
    _mapTxt.clear();
    _mobsDirection.clear();
    _texts.clear();
    _food.clear();
    _map.clear();
}

void Pacman::handleEvent(const Arcade::Event &event)
{
    if (event.type == Arcade::EventType::KEY_PRESS || event.type == Arcade::EventType::KEY_RELEASE) {
        switch (event.key) {
            case Arcade::EventKey::D:
                _direction = 'D';
                break;
            case Arcade::EventKey::Z:
                _direction = 'Z';
                break;
            case Arcade::EventKey::S:
                _direction = 'S';
                break;
            case Arcade::EventKey::Q:
                _direction = 'Q';
                break;
            default: break;
        }
    }
}

void Pacman::updatePlayer(size_t x, size_t y)
{
    switch (_direction) {
        case 'D':
            if (x != 19 && _mapTxt.at(y)[x + 1] != 'x') _player.move(20, 0);
            break;
        case 'Z':
            if (y != 0 && _mapTxt.at(y - 1)[x] != 'x') _player.move(0, -20);
            break;
        case 'S':
            if (y != 19 && _mapTxt.at(y + 1)[x] != 'x') _player.move(0, 20);
            break;
        case 'Q':
            if (x != 0 && _mapTxt.at(y)[x - 1] != 'x') _player.move(-20, 0);
            break;
        default: break;
    }
}

void Pacman::updateMobDirection(Arcade::Rect mob, size_t x, size_t y, size_t index)
{
    size_t playerX = (_player.getPosition().x - _mapOffsetX) / 20;
    size_t playerY = (_player.getPosition().y - _mapOffsetY) / 20;
    std::string dir = "QDZS";
    std::vector<size_t> tabX;
    std::vector<size_t> tabY;

    if (!_invincible) {
        tabX.push_back(x - 1);
        tabX.push_back(x + 1);
        tabX.push_back(x);
        tabX.push_back(x);
        tabY.push_back(y);
        tabY.push_back(y);
        tabY.push_back(y - 1);
        tabY.push_back(y + 1);
    } else {
        tabX.push_back(x + 1);
        tabX.push_back(x - 1);
        tabX.push_back(x);
        tabX.push_back(x);
        tabY.push_back(y);
        tabY.push_back(y);
        tabY.push_back(y + 1);
        tabY.push_back(y - 1);
        dir = "DQSZ";
    }
    if (playerX < x && _mapTxt.at(tabY.at(0))[tabX.at(0)] != 'x') {
        _mobsDirection.at(index) = dir[0];
    } else if (playerX > x && _mapTxt.at(tabY.at(1))[tabX.at(1)] != 'x') {
        _mobsDirection.at(index) = dir[1];
    } else if (playerY < y && _mapTxt.at(tabY.at(2))[tabX.at(2)] != 'x') {
        _mobsDirection.at(index) = dir[2];
    } else if (playerY > y && _mapTxt.at(tabY.at(3))[tabX.at(3)] != 'x') {
        _mobsDirection.at(index) = dir[3];
    } else {
        switch (_mobsDirection.at(index)) {
            case 'D':
                if (x != 19 && _mapTxt.at(y)[x + 1] != 'x') return;
                break;
            case 'Z':
                if (y != 0 && _mapTxt.at(y - 1)[x] != 'x') return;
                break;
            case 'S':
                if (y != 19 && _mapTxt.at(y + 1)[x] != 'x') return;
                break;
            case 'Q':
                if (x != 0 && _mapTxt.at(y)[x - 1] != 'x') return;
                break;
            default: return;
        }
        if (_mobsDirection.at(index) == 'D') {
            _mobsDirection.at(index) = 'S';
            updateMobDirection(mob, x, y, index);
        } else if (_mobsDirection.at(index) == 'Z') {
            _mobsDirection.at(index) = 'D';
            updateMobDirection(mob, x, y, index);
        } else if (_mobsDirection.at(index) == 'S') {
            _mobsDirection.at(index) = 'Q';
            updateMobDirection(mob, x, y, index);
        } else {
            _mobsDirection.at(index) = 'Z';
            updateMobDirection(mob, x, y, index);
        }
    }
}

void Pacman::updateMobs(void)
{
    std::vector<size_t> mobX;
    std::vector<size_t> mobY;
    int index = 0;

    for (auto mob : _mobs) {
        mobX.push_back((mob.getPosition().x - _mapOffsetX) / 20);
        mobY.push_back((mob.getPosition().y - _mapOffsetY) / 20);
    }
    for (auto mob : _mobs) {
        updateMobDirection(mob, mobX.at(index), mobY.at(index), index);
        index++;
    }
    index = 0;
    for (auto directions : _mobsDirection) {
        switch (directions) {
            case 'D':
                if (mobX.at(index) != 19 && _mapTxt.at(mobY.at(index))[mobX.at(index) + 1] != 'x') _mobs.at(index).move(20, 0);
                break;
            case 'Z':
                if (mobY.at(index) != 0 && _mapTxt.at(mobY.at(index) - 1)[mobX.at(index)] != 'x') _mobs.at(index).move(0, -20);
                break;
            case 'S':
                if (mobY.at(index) != 19 && _mapTxt.at(mobY.at(index) + 1)[mobX.at(index)] != 'x') _mobs.at(index).move(0, 20);
                break;
            case 'Q':
                if (mobX.at(index) != 0 && _mapTxt.at(mobY.at(index))[mobX.at(index) - 1] != 'x') _mobs.at(index).move(-20, 0);
                break;
            default: break;
        }
        index++;
    }
}

void Pacman::superPower(size_t x, size_t y)
{
    if (_food.at((y * 20) + x).getRadius() == 5) {
        _invincibleClock.restart();
        _colorClock.restart();
        _invincible = true;
        _mobColor = 3;
    }
    if (_colorClock.getElapsedTime() / CLOCKS_PER_SEC >= 0.1 && _invincible == true) {
        if (_mobColor == 3) _mobColor = 2;
        else _mobColor = 3;
        _colorClock.restart();
    }
    if (_invincible == true && _invincibleClock.getElapsedTime() / CLOCKS_PER_SEC >= 5) {
        _invincible = false;
        _mobColor = 1;
    }
}

void Pacman::eatMob(void)
{
    size_t x = (_player.getPosition().x - _mapOffsetX) / 20;
    size_t y = (_player.getPosition().y - _mapOffsetY) / 20;
    size_t x1 = 0;
    size_t y1 = 0;

    for (size_t i = 0; i < _mobs.size(); i++) {
        x1 = (_mobs.at(i).getPosition().x - _mapOffsetX) / 20;
        y1 = (_mobs.at(i).getPosition().y - _mapOffsetY) / 20;
        if (x == x1 && y == y1 && _mobs.at(i).getDimension().x != 0) {
            _mobs.at(i).setDimension(0, 0);
            _score += 10;
            _texts.at(0).setText("SCORE :  " + std::to_string(_score));
        }
    }
}

void Pacman::mobRespawn(void)
{
    for (auto mob : _mobs)
        if (mob.getDimension().x != 0) return;
    for (size_t i = 0, idx = 0; i < _mapTxt.size(); i++) {
        for (size_t j = 0; j < _mapTxt.size(); j++) {
            if (_mapTxt.at(i)[j] == 'M') {
                _mobs.at(idx).setDimension(16, 16);
                _mobs.at(idx).setPosition(j * 20 + _mapOffsetX, i * 20 + _mapOffsetY);
                idx++;
            }
        }
    }
}

bool Pacman::isEaten(void)
{
    size_t x = (_player.getPosition().x - _mapOffsetX) / 20;
    size_t y = (_player.getPosition().y - _mapOffsetY) / 20;
    size_t x1 = 0;
    size_t y1 = 0;

    for (size_t i = 0; i < _mobs.size(); i++) {
        x1 = (_mobs.at(i).getPosition().x - _mapOffsetX) / 20;
        y1 = (_mobs.at(i).getPosition().y - _mapOffsetY) / 20;
        if (x == x1 && y == y1 && _mobs.at(i).getDimension().x != 0) {
            if (_life == 1) {
                _isFinished = true;
                return (true);
            }
            _life -= 1;
            _player.setPosition(20 + _mapOffsetX, 20 + _mapOffsetY);
            _direction = 'D';
            return (false);
        }
    }
    return (false);
}

void Pacman::update(double delta)
{
    size_t x = (_player.getPosition().x - _mapOffsetX) / 20;
    size_t y = (_player.getPosition().y - _mapOffsetY) / 20;

    if (!_isFinished) {
        mobRespawn();
        superPower(x, y);
        if (_food.at((y * 20) + x).getRadius() == 3 || _food.at((y * 20) + x).getRadius() == 5) {
            _graphicalLib->playSound(Arcade::Sound("./assets/sounds/wakawaka.wav"));
            _food.at((y * 20) + x).setRadius(0);
            _score += 1;
            _texts.at(0).setText("SCORE :  " + std::to_string(_score));
        }
        if (_clock.getElapsedTime() / CLOCKS_PER_SEC < 0.5) return;
        _clock.restart();
        updatePlayer(x, y);
        if (_invincible == true) eatMob();
        else isEaten();
    }
    if (!_isFinished) updateMobs();
}

void Pacman::draw()
{
    for (auto text : _texts)
        _graphicalLib->drawText(text);
    Arcade::Circle life;
    life.setRadius(8);
    life.setFillColor(Arcade::getColor(Arcade::Colors::RED));
    life.setPosition(_mapOffsetX + 330, 95);
    for (int i = 0; i <= _life; i++) {
        _graphicalLib->drawCircle(life);
        life.setPosition(_mapOffsetX + 330 + 30 * i, 95);
    }
    for (auto rect : _map)
        _graphicalLib->drawRect(rect);
    for (auto circle : _food) {
        if (circle.getRadius() == 5) {
            Arcade::Image potion("assets/images/Pacman/potion");
            potion.setPosition(circle.getPosition().x, circle.getPosition().y);
            _graphicalLib->drawImage(potion);
        } else
            _graphicalLib->drawCircle(circle);
    }
    for (auto rect : _mobs) {
        if (rect.getDimension().x != 0) {
            size_t x = rect.getPosition().x;
            size_t y = rect.getPosition().y;
            std::string pathImg = "assets/images/Pacman/mob";
            if (_mobColor == 2) pathImg = "assets/images/Pacman/green";
            if (_mobColor == 3) pathImg = "assets/images/Pacman/blue";
            Arcade::Image mob(pathImg);
            mob.setPosition(x, y);
            _graphicalLib->drawImage(mob);
        }
    }
    std::string path = "assets/images/Pacman/pacman";
    if (_direction == 'Z' && _mobColor == 1) path = "assets/images/Pacman/up";
    if (_direction == 'Q' && _mobColor == 1) path = "assets/images/Pacman/left";
    if (_direction == 'S' && _mobColor == 1) path = "assets/images/Pacman/down";
    if (_direction == 'D' && _mobColor == 2) path = "assets/images/Pacman/pac2";
    if (_direction == 'Z' && _mobColor == 2) path = "assets/images/Pacman/up3";
    if (_direction == 'Q' && _mobColor == 2) path = "assets/images/Pacman/left3";
    if (_direction == 'S' && _mobColor == 2) path = "assets/images/Pacman/down3";
    if (_direction == 'D' && _mobColor == 3) path = "assets/images/Pacman/pac3";
    if (_direction == 'Z' && _mobColor == 3) path = "assets/images/Pacman/up2";
    if (_direction == 'Q' && _mobColor == 3) path = "assets/images/Pacman/left2";
    if (_direction == 'S' && _mobColor == 3) path = "assets/images/Pacman/down2";
    Arcade::Image player(path);
    player.setPosition(_player.getPosition().x, _player.getPosition().y);
    _graphicalLib->drawImage(player);
}

int Pacman::getScore() const
{
    return (_score);
}

bool Pacman::isFinished() const
{
    return (_isFinished);
}