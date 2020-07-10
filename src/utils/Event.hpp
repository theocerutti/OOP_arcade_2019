/*
** EPITECH PROJECT, 2020
** arcade_interface_4all
** File description:
** Event.hpp
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

namespace Arcade {
    enum EventKey {
        KEY_UNKNOWN = -1,
        Z,
        Q,
        S,
        D,
        UP,
        DOWN,
        RIGHT,
        LEFT,
        ECHAP,
        ENTER,
        SPACE
    };

    enum EventType {
        TYPE_UNKNOWN = -1,
        CLOSE,
        KEY_RELEASE,
        KEY_PRESS,
        TEXT_ENTERED,
        MOUSE_MOVE
    };

    struct EventMouse {
        int x;
        int y;
    };

    struct Event {
        EventType type;
        EventKey key;
        unsigned char unicode;
        EventMouse mouse;
    };
}

#endif /* !EVENT_HPP_ */