/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** MyCaca
*/

#ifndef MYCACA_HPP_
#define MYCACA_HPP_

#include "caca++.h"

class MyCaca
{
 public:
    MyCaca();
    MyCaca(Canvas *cv);
    ~MyCaca();

    void Attach(Canvas *cv);
    void Detach();
    void setDisplayTime(unsigned int);

    void Display();
    unsigned int getDisplayTime();
    unsigned int getWidth();
    unsigned int getHeight();
    int setTitle(char const *);
    int getEvent(unsigned int, Event*, int);
    unsigned int getMouseX();
    unsigned int getMouseY();
    void setMouse(int);

    static char const * getVersion();
    caca_display_t *dp;
};

#endif /* !MYCACA_HPP_ */
