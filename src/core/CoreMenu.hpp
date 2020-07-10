/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CoreMenu
*/

#ifndef COREMENU_HPP_
#define COREMENU_HPP_

#include <vector>
#include <dirent.h>
#include <random>
#include "DLLoader.hpp"
#include "../games/IGame.hpp"
#include "../graphicals/ILibGFX.hpp"
#include "../utils/Clock.hpp"
#include "Scoreboard.hpp"
#include "ScoreSaver.hpp"

#define BEFORE -1
#define AFTER 1

namespace Arcade {
    typedef struct MenuEvent_s {
        bool switchGame;
        unsigned int gameId;
    } MenuEvent;

    class CoreMenu {
        public:
            CoreMenu(ScoreSaver &saver, const std::vector<DLLoader<IGame>> &_gameLoaders);
            ~CoreMenu();
            const MenuEvent handleEvent(const Event &event);
            void drawWith(ILibGFX *lib);
            void reload();
            void updateWith(double deltaTime);
        private:
            void randomizeCircleBg();
            void setChooseText(int off);
        private:
            Vector2i _wDimension;
            std::vector<DLLoader<IGame>> _games;
            std::vector<Text> _texts;
            Text _title;
            int _chooseGameIndex;
            std::vector<Circle> _circlesBg;
            size_t _nbCircleBg;
            std::default_random_engine _generator;
            Clock _clock;
            Arcade::Image _arcadeLogo;
            Arcade::Rect _pointer;
            bool _menuInGame;
            int _selectedGame;
            Arcade::Text _titleGame;
            Arcade::Text _textHelp1;
            Arcade::Text _textHelp2;
            Arcade::Scoreboard _scoreboard;
    };
}

#endif /* !COREMENU_HPP_ */