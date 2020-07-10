/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"
#include "../graphicals/ILibGFX.hpp"

namespace Arcade {
    class AGame : public IGame {
        public:
            AGame();
            virtual ~AGame() = default;
            virtual void init() = 0; // init all variables
            virtual void stop() = 0; // free all varaibles
            virtual void handleEvent(const Arcade::Event &event) = 0;
            virtual void update(double delta) = 0;
            virtual void draw() = 0;
            void setGFXLibrary(ILibGFX *library) override;
            virtual int getScore() const = 0;
            virtual bool isFinished() const = 0;
        protected:
            ILibGFX *_graphicalLib;
    };
}

#endif /* !AGAME_HPP_ */