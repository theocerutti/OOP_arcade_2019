/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "interfaces/ISound.hpp"

namespace Arcade {
    class Sound : public ISound {
        public:
            Sound();
            Sound(const std::string &path, size_t volume = 100);
            ~Sound();
            const std::string &getSound() const;
            size_t getVolume() const;
        private:
            std::string path;
            int volume;
    };
}

#endif /* !SOUND_HPP_ */
