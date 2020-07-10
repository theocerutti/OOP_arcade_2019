/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sound
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include "interfaces/IMusic.hpp"

namespace Arcade {
    class Music : public IMusic {
        public:
            Music();
            Music(const std::string &path, size_t volume = 100, bool isLooping = true);
            ~Music();
            const std::string &getMusic() const;
            size_t getVolume() const;
            bool isLooping() const;
        private :
            std::string path;
            int volume;
            bool looping;
    };
}

#endif /* !MUSIC_HPP_ */
