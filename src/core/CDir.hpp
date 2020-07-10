/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CDir
*/

#ifndef CDIR_HPP_
#define CDIR_HPP_

#include <dirent.h>
#include <iostream>

class CDir {
    public:
        CDir();
        std::string getNextFileName();
        bool getNextFileName(std::string &s);
        bool open(const std::string &directory);
        void close();
        ~CDir();
    private:
        DIR *_dir;
        struct dirent *_ent;
};

#endif /* !CDIR_HPP_ */