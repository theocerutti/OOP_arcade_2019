/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Engine
*/

#ifndef Engine_HPP_
#define Engine_HPP_

#include <iostream>
#include <vector>
#include <dirent.h>
#include <regex>
#include "CDir.hpp"
#include "ScoreSaver.hpp"
#include "DLLoader.hpp"
#include "CoreMenu.hpp"
#include "FinishMenu.hpp"
#include "../errors/CoreError.hpp"
#include "../errors/GameError.hpp"
#include "../errors/LibError.hpp"
#include "../utils/Clock.hpp"

namespace Arcade {
    enum LibMove {
        After = 1,
        Before = -1
    };
    class Engine {
        public:
            Engine(const std::string &currentGraphicalArg);
            ~Engine();
            int run();
        private:
            void scanGraphicalLib();
            void scanGames();
            int getLibIndex() const;
            void setLibIndex(int newLibIndex);
            void setLibIndex(const std::string &libPath);
            void switchGraphicalLibrary(const Arcade::LibMove &move);
            void switchGame(unsigned int gameId);
            void goToMenu(Arcade::CoreMenu &menu);
        private:
            std::vector<DLLoader<ILibGFX>> _vLibLoader;
            std::vector<DLLoader<IGame>> _vGameLoader;
            IGame *_currentGame;
            ILibGFX *_currentLib;
            int _libIndex;
            int _gameIndex;
            bool _inMenu;
            bool _inFinishGame;
            Arcade::ScoreSaver _scoreSaver;
    };
}

#endif /* !Engine_HPP_ */