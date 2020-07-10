/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CoreMenu
*/

#include "CoreMenu.hpp"

Arcade::CoreMenu::CoreMenu(ScoreSaver &saver, const std::vector<DLLoader<IGame>> &gameLoaders)
    : _wDimension(Arcade::Vector2i(800, 600)),
      _games(gameLoaders),
      _texts(),
      _title(),
      _chooseGameIndex(0),
      _circlesBg(),
      _nbCircleBg(50),
      _generator(time(0)),
      _clock(),
      _arcadeLogo("./assets/images/CoreMenu/arcadeLogo"),
      _pointer(),
      _menuInGame(false),
      _selectedGame(0),
      _titleGame(),
      _textHelp1(),
      _textHelp2(),
      _scoreboard(saver)
{
    int paddingY = 150;
    int allFontSize = 35;

    _title.setPathFont("./assets/fonts/ArcadeClassic.ttf");
    _title.setTextSize(allFontSize + 20);
    _title.setText("Arcade");
    _title.setPosition(300, 20);
    for (size_t i = 0; i < _games.size(); i++) {
        Arcade::Text text(_games.at(i).getName());
        text.setPosition(320, (40 * i) + paddingY);
        text.setColor(Arcade::getColor(Arcade::WHITE));
        text.setPathFont("./assets/fonts/ArcadeClassic.ttf");
        text.setTextSize(allFontSize);
        if (i == _chooseGameIndex)
            text.setColor(Arcade::getColor(Arcade::RED));
        else
            text.setColor(Arcade::getColor(Arcade::WHITE));
        _texts.push_back(text);
    }
    for (size_t i = 0; i < _nbCircleBg; i++)
        _circlesBg.push_back(Arcade::Circle());
    randomizeCircleBg();
    _pointer.setDimension(8, 8);
    _pointer.setFillColor(Arcade::getColor(Arcade::RED));
    _arcadeLogo.setPosition(730, 50);
    _arcadeLogo.setOrigin(50 / 2, 80 / 2);
    _textHelp1.setText("Press  ENTER  to  Play");
    _textHelp1.setPosition(250, 100);
    _textHelp1.setPathFont("./assets/fonts/ArcadeClassic.ttf");
    _textHelp2.setText("Press  Q  to  Back");
    _textHelp2.setPosition(280, 550);
    _textHelp2.setPathFont("./assets/fonts/ArcadeClassic.ttf");
    _titleGame.setPathFont("./assets/fonts/ArcadeClassic.ttf");
    _titleGame.setPosition(300, 20);
    _titleGame.setTextSize(55);
}

Arcade::CoreMenu::~CoreMenu()
{
}

void Arcade::CoreMenu::randomizeCircleBg()
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

const Arcade::MenuEvent Arcade::CoreMenu::handleEvent(const Arcade::Event &event)
{
    MenuEvent menuEvent{false, 0};

    if (event.type == Arcade::EventType::MOUSE_MOVE)
        _pointer.setPosition(event.mouse.x, event.mouse.y);
    if (event.type == Arcade::EventType::KEY_RELEASE) {
        switch (event.key) {
            case Arcade::EventKey::ENTER:
                if (_menuInGame) {
                    menuEvent.switchGame = true;
                    menuEvent.gameId = _chooseGameIndex;
                } else {
                    _menuInGame = true;
                    _selectedGame = _chooseGameIndex;
                    _titleGame.setText(_texts.at(_chooseGameIndex).getText());
                    _scoreboard.setScoreGameToDisplay(_texts.at(_chooseGameIndex).getText());
                }
                break;
            case Arcade::EventKey::Q:
                if (_menuInGame)
                    _menuInGame = false;
                break;
            default: break;
        }
        if (!_menuInGame) {
            switch (event.key) {
                case Arcade::EventKey::D:
                    break;
                case Arcade::EventKey::Z:
                    setChooseText(BEFORE);
                    break;
                case Arcade::EventKey::S:
                    setChooseText(AFTER);
                    break;
                case Arcade::EventKey::Q:
                    break;
                default: break;
            }
        }
    }
    return (menuEvent);
}

void Arcade::CoreMenu::reload()
{
    _menuInGame = false;
    _selectedGame = 0;
    _chooseGameIndex = 0;
    for (Arcade::Text &text : _texts)
        text.setColor(Arcade::getColor(Arcade::WHITE));
    _texts.at(_chooseGameIndex).setColor(Arcade::getColor(Arcade::RED));
}

void Arcade::CoreMenu::setChooseText(int off)
{
    _texts.at(_chooseGameIndex).setColor(Arcade::getColor(Arcade::WHITE));
    _chooseGameIndex += off;
    if (_chooseGameIndex >= static_cast<int>(_texts.size()))
        _chooseGameIndex = 0;
    if (_chooseGameIndex < 0)
        _chooseGameIndex = _texts.size() - 1;
    _texts.at(_chooseGameIndex).setColor(Arcade::getColor(Arcade::RED));
}

void Arcade::CoreMenu::updateWith(double deltaTime)
{
    if (_clock.getElapsedTime() / CLOCKS_PER_SEC > 0.4) {
        randomizeCircleBg();
        _clock.restart();
    }
    if (_arcadeLogo.getRotation() >= 360)
        _arcadeLogo.setRotation(0);
    _arcadeLogo.setRotation(_arcadeLogo.getRotation() + 1000 * deltaTime);
}

void Arcade::CoreMenu::drawWith(ILibGFX *lib)
{
    for (Arcade::Circle &circle : _circlesBg)
        lib->drawCircle(circle);
    if (_menuInGame) {
        lib->drawText(_titleGame);
        lib->drawText(_textHelp1);
        lib->drawText(_textHelp2);
        _scoreboard.drawWith(lib);
    } else {
        for (Arcade::Text &text : _texts)
            lib->drawText(text);
        lib->drawText(_title);
    }
    lib->drawImage(_arcadeLogo);
    lib->drawRect(_pointer);
}