/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <chrono>
#include <ctime>

namespace Arcade {
    class Clock {
        public:
            Clock();
            ~Clock();
            double getElapsedTime() const;
            void restart();
        private:
            std::clock_t clock;
    };
}

#endif /* !CLOCK_HPP_ */