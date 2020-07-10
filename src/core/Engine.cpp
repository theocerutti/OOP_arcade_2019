/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Engine
*/

#include "Engine.hpp"

Arcade::Engine::Engine(const std::string &currentGraphicalArg)
    : _vLibLoader(),
      _vGameLoader(),
      _currentGame(nullptr),
      _currentLib(nullptr),
      _libIndex(0),
      _gameIndex(0),
      _inMenu(true),
      _inFinishGame(false),
      _scoreSaver("./assets/scores/score.txt")
{
    try {
        scanGraphicalLib();
        setLibIndex(currentGraphicalArg);
        scanGames();
    } catch (const CoreError &e) {
        std::cout << e.what() << std::endl;
        std::exit(84);
    }
    _currentLib = _vLibLoader.at(_libIndex).getInstance();
}

Arcade::Engine::~Engine()
{
    if(_currentGame)
        _currentGame->stop();
    _currentLib->closeWindow();
    for (auto &loader : _vGameLoader) {
        loader.getInstance()->setGFXLibrary(nullptr);
        loader.close();
    }
    for (auto &loader : _vLibLoader)
        loader.close();
}

void Arcade::Engine::setLibIndex(const std::string &libPath)
{
    std::regex libRegex("lib_arcade_([\\w]+)\\.so$");
    std::smatch matchs;
    std::regex_search(libPath, matchs, libRegex);
    std::string nameLib = matchs.str(1);
    int i = 0;

    for (auto &loader : _vLibLoader) {
        if (loader.getName() == nameLib) {
            _libIndex = i;
            return;
        }
        i += 1;
    }
    throw CoreError("Can't find library index");
}


void Arcade::Engine::setLibIndex(int newLibIndex)
{
    if (newLibIndex >= static_cast<int>(_vLibLoader.size()))
        newLibIndex = 0;
    if (newLibIndex < 0)
        newLibIndex = _vLibLoader.size() - 1;
    _libIndex = newLibIndex;
}

int Arcade::Engine::getLibIndex() const
{
    return (_libIndex);
}

void Arcade::Engine::scanGames()
{
    CDir dirHandler;
    std::smatch matchs;
    std::regex isLib("^lib_arcade_([\\w]+)\\.so$");
    std::string libName;

    if (dirHandler.open("./games/")) {
        while (dirHandler.getNextFileName(libName)) {
            if (std::regex_match(libName, matchs, isLib)) {
                try {
                    DLLoader<IGame> loader = DLLoader<IGame>("./games/" + libName, matchs.str(1));
                    _vGameLoader.push_back(loader);
                } catch (const CoreError &e) {
                    std::cout << "Game: Error loading: ./games/" + libName + ". " + std::string(e.what()) << std::endl;
                }
            }
        }
        dirHandler.close();
    } else
        throw CoreError("Engine: Can't open ./games/ directory!");
    if (_vGameLoader.size() == 0)
        throw CoreError("Engine: 'games' directory must contain at least one game.");
}

void Arcade::Engine::scanGraphicalLib()
{
    CDir dirHandler;
    std::smatch matchs;
    std::string libName;
    std::regex isLib("^lib_arcade_([\\w]+)\\.so$");

    if (dirHandler.open("./lib/")) {
        while (dirHandler.getNextFileName(libName)) {
            if (std::regex_match(libName, matchs, isLib)) {
                try {
                    DLLoader<ILibGFX> loader = DLLoader<ILibGFX>("./lib/" + libName, matchs.str(1));
                    _vLibLoader.push_back(loader);
                } catch (const CoreError &e) {
                    std::cout << "Library: Error loading: ./lib/" + libName + ". " + std::string(e.what()) << std::endl;
                }
            }
        }
        dirHandler.close();
    } else
        throw CoreError("Engine: Can't open ./lib/ directory!");
    if (_vLibLoader.size() == 0)
        throw CoreError("Engine: 'lib' directory must contain at least one game.");
}

void Arcade::Engine::switchGraphicalLibrary(const Arcade::LibMove &move)
{
    _currentLib->closeWindow();
    setLibIndex(getLibIndex() + move);
    _currentLib = _vLibLoader.at(_libIndex).getInstance();
    _currentLib->createWindow(800, 600, "Arcade");
    if (_currentGame)
        _currentGame->setGFXLibrary(_currentLib);
}

void Arcade::Engine::switchGame(unsigned int gameId)
{
    if (_currentGame)
        _currentGame->stop();
    _gameIndex = gameId;
    _currentGame = _vGameLoader.at(gameId).getInstance();
    _currentGame->setGFXLibrary(_currentLib);
    _currentGame->init();
}

void Arcade::Engine::goToMenu(Arcade::CoreMenu &menu)
{
    if (_currentGame)
        _currentGame->stop();
    _currentGame = nullptr;
    _inMenu = true;
    menu.reload();
}

int Arcade::Engine::run()
{
    Arcade::Clock clock;
    Arcade::MenuEvent menuEvent;
    Arcade::Event eventGame;
    Arcade::CoreMenu menu(_scoreSaver, _vGameLoader);
    Arcade::FinishMenu menuFinish;
    Arcade::FinishEvent finishEvent;

    _currentLib->createWindow(800, 600, "Arcade");
    clock.restart();
    while (true) {
        eventGame = _currentLib->pollEvent();
        if (eventGame.type == Arcade::EventType::CLOSE)
            break;
        if (eventGame.type == Arcade::KEY_RELEASE && eventGame.key == Arcade::ECHAP) {
            if (_inMenu)
                break;
            else
                goToMenu(menu);
        }
        if (eventGame.type == Arcade::EventType::KEY_RELEASE && eventGame.key == Arcade::EventKey::RIGHT)
            switchGraphicalLibrary(Arcade::LibMove::After);
        if (eventGame.type == Arcade::EventType::KEY_RELEASE && eventGame.key == Arcade::EventKey::LEFT)
            switchGraphicalLibrary(Arcade::LibMove::Before);
        if (_inMenu) {
            menuEvent = menu.handleEvent(eventGame);
            if (menuEvent.switchGame == true) {
                switchGame(menuEvent.gameId);
                _inMenu = false;
            }
            menu.updateWith(clock.getElapsedTime()  / CLOCKS_PER_SEC);
            _currentLib->clear();
            menu.drawWith(_currentLib);
            _currentLib->drawWindow();
        } else if (_inFinishGame) {
            menuFinish.setScore(_currentGame->getScore());
            finishEvent = menuFinish.handleEvent(eventGame, _scoreSaver, _vGameLoader.at(_gameIndex).getName());
            if (finishEvent.finish == true) {
                _inFinishGame = false;
                goToMenu(menu);
            }
            menuFinish.updateWith(clock.getElapsedTime()  / CLOCKS_PER_SEC);
            _currentLib->clear();
            menuFinish.drawWith(_currentLib);
            _currentLib->drawWindow();
        } else {
            if (_currentGame->isFinished()) {
                _inFinishGame = true;
            } else {
                _currentGame->handleEvent(eventGame);
                _currentGame->update(clock.getElapsedTime() / CLOCKS_PER_SEC);
                _currentLib->clear();
                _currentGame->draw();
                _currentLib->drawWindow();
            }
        }
        clock.restart();
    }
    return (0);
}