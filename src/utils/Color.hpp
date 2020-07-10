/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Color
*/

#ifndef COLOR_HPP_
#define COLOR_HPP_

#define CAST(type, x) (    type    )x
#define COLOR(r, g, b, a) {r, g, b, a}

typedef unsigned char byte;

namespace Arcade {
    typedef struct Color_t {
        byte r;
        byte g;
        byte b;
        byte a;
    } Color;

    enum Colors {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BBLACK,
        BRED,
        BGREEN,
        BYELLOW,
        BBLUE,
        BMAGENTA,
        BCYAN,
        BWHITE,
        NONE,
    };

    static const Color getColor(int color)
    {
        switch (color) {
            case 0:
                return CAST(Color, COLOR(0, 0, 0, 255));
            case 1:
                return CAST(Color, COLOR(222, 56, 43, 255));
            case 2:
                return CAST(Color, COLOR(57, 181, 174, 255));
            case 3:
                return CAST(Color, COLOR(255, 199, 6, 255));
            case 4:
                return CAST(Color, COLOR(0, 111, 184, 255));
            case 5:
                return CAST(Color, COLOR(118, 38, 113, 255));
            case 6:
                return CAST(Color, COLOR(44, 181, 233, 255));
            case 7:
                return CAST(Color, COLOR(204, 204, 204, 255));
            case 8:
                return CAST(Color, COLOR(128, 128, 128, 255));
            case 9:
                return CAST(Color, COLOR(255, 0, 0, 255));
            case 10:
                return CAST(Color, COLOR(0, 255, 0, 255));
            case 11:
                return CAST(Color, COLOR(255, 255, 0, 255));
            case 12:
                return CAST(Color, COLOR(0, 0, 255, 255));
            case 13:
                return CAST(Color, COLOR(255, 0, 255, 255));
            case 14:
                return CAST(Color, COLOR(0, 255, 255, 255));
            case 15:
                return CAST(Color, COLOR(255, 255, 255, 255));
            default:
                return CAST(Color, COLOR(0, 0, 0, 0));
        }
    };
}

#endif /* !COLOR_HPP_ */