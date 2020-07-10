/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "../utils/Event.hpp"
#include "../errors/GameError.hpp"
#include "../graphicals/ILibGFX.hpp"
#include <iostream>
#include <memory>

namespace Arcade {
    class IGame {
        public:
            virtual ~IGame() = default;

            virtual void init() = 0; // init all variables
            virtual void stop() = 0; // free all varaibles
            virtual void handleEvent(const Event &event) = 0;
            virtual void update(double delta) = 0;
            virtual void draw() = 0;
            virtual void setGFXLibrary(ILibGFX *library) = 0;
            virtual int getScore() const = 0;
            virtual bool isFinished() const = 0;
    };
}

#endif /* !IGAME_HPP_ */