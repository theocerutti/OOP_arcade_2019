/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** FinishMenu
*/

#include "FinishMenu.hpp"

Arcade::FinishMenu::FinishMenu()
{
    _mapOffsetX = 200;
    _mapOffsetY = 120;
    _score = 0;
    _nbCircleBg = 50;
    _clock.restart();
    _texts.push_back(setText("- SCORE -", 95, 10, 50, Arcade::getColor(Arcade::WHITE), "./assets/fonts/Silicone.ttf"));
    _texts.push_back(setText("0000", 40, 160, 120, Arcade::getColor(Arcade::RED), "./assets/fonts/Silicone.ttf"));
    _texts.push_back(setText("Enter your pseudo ", -80, 400, 40, Arcade::getColor(Arcade::WHITE), "./assets/fonts/Silicone.ttf"));
    _texts.push_back(setText("XXX", 399, 397, 50, Arcade::getColor(Arcade::WHITE), "./assets/fonts/test.ttf"));
    _texts.push_back(setText("PRESS   ENTER   TO   CONFIRM", 59, 550, 25, Arcade::getColor(Arcade::WHITE), "./assets/fonts/ArcadeClassic.ttf"));
    _textArea.setDimension(130, 50);
    _textArea.setPosition(_mapOffsetX + 370, 405);
    _textArea.setFillColor(Arcade::getColor(Arcade::BBLACK));
    for (size_t i = 0; i < _nbCircleBg; i++)
        _circlesBg.push_back(Arcade::Circle());
    randomizeCircleBg();
}

Arcade::FinishMenu::~FinishMenu()
{
}

void Arcade::FinishMenu::randomizeCircleBg()
{
    std::uniform_int_distribution<int> radiusDistrub(3, 15);
    std::uniform_int_distribution<int> posXDistrib(0, 800);
    std::uniform_int_distribution<int> posYDistrib(0, 600);
    std::uniform_int_distribution<int> colorDistrib(Arcade::BLACK, Arcade::NONE - 1);

    for (Arcade::Circle &circle : _circlesBg) {
        circle.setRadius(circle.getRadius() - 1);
        if (circle.getRadius() <= 0) {
            circle.setRadius(radiusDistrub(_generator));
            circle.setPosition(posXDistrib(_generator), posYDistrib(_generator));
        }
        circle.setFillColor(Arcade::getColor(colorDistrib(_generator)));
    }
}

void Arcade::FinishMenu::setScore(int score)
{
    std::stringstream stream;

    _score = score;
    stream << std::setw(4) << std::setfill('0') << _score;
    _texts.at(1).setText(stream.str());
}

Arcade::Text Arcade::FinishMenu::setText(std::string text, int x, int y, size_t size, Arcade::Color color, std::string path)
{
    Arcade::Text txt = Arcade::Text(text);

    txt.setPosition(_mapOffsetX + x, y);
    txt.setTextSize(size);
    txt.setColor(color);
    txt.setPathFont(path);
    return (txt);
}

const Arcade::FinishEvent Arcade::FinishMenu::handleEvent(const Event &event, Arcade::ScoreSaver &score, const std::string &game)
{
    FinishEvent evt{false};

    if (event.type == Arcade::EventType::TEXT_ENTERED) {
        if (_texts.at(3).getText() == "XXX")
            _texts.at(3).setText("");
        std::string pseudo = _texts.at(3).getText();
        if (pseudo.length() != 0 && event.unicode == 8)
            pseudo.pop_back();
        else if (pseudo.length() < 3 && event.unicode >= 'a' && event.unicode <= 'z')
            pseudo += event.unicode;
        _texts.at(3).setText(pseudo);
    }
    if (event.type == Arcade::EventType::KEY_RELEASE) {
        switch (event.key) {
            case Arcade::EventKey::ENTER:
                if (_texts.at(3).getText().length() != 3) break;
                score.saveScore(_score, _texts.at(3).getText(), game);
                _texts.at(3).setText("XXX");
                evt.finish = true;
                break;
            default: break;
        }
    }
    return (evt);
}

void Arcade::FinishMenu::drawWith(ILibGFX *lib)
{
    for (Arcade::Circle &circle : _circlesBg)
        lib->drawCircle(circle);
    lib->drawRect(_textArea);
    for (auto text : _texts)
        lib->drawText(text);
}

void Arcade::FinishMenu::reload()
{
}

void Arcade::FinishMenu::updateWith(double deltaTime __attribute__((unused)))
{
    if (_clock.getElapsedTime()  / CLOCKS_PER_SEC > 0.4) {
        randomizeCircleBg();
        _clock.restart();
    }
}