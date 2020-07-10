/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pos
*/

#ifndef POS_HPP_
#define POS_HPP_

namespace Arcade {
    template <class T>
    class Vector2 {
        public:
            Vector2() { this->x = 0; this->y = 0; }
            Vector2(T x, T y) { this->x = x; this->y = y; }
            T x;
            T y;
    };

    template <typename T>
    Vector2<T> operator-(const Vector2<T> &right)
    {
        right.x = -right.x;
        right.y = -right.y;
    }

    template <typename T>
    Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right)
    {
        left.x += right.x;
        left.y += right.y;
    }

    template <typename T>
    Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right)
    {
        left.x -= right.x;
        left.y -= right.y;
    }

    template <typename T>
    Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right)
    {
        return (Vector2<T>(left.x + right.x, left.y + right.y));
    }

    template <typename T>
    Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right)
    {
        return (Vector2<T>(left.x - right.x, left.y - right.y));
    }

    template <typename T>
    Vector2<T> operator*(const Vector2<T> &left, T right)
    {
        return (Vector2<T>(left.x * right, left.y * right));
    }

    template <typename T>
    Vector2<T> operator*(T left, const Vector2<T> &right)
    {
        return (Vector2<T>(left * right.x, left * right.y));
    }

    template <typename T>
    Vector2<T> &operator*=(Vector2<T> &left, T right)
    {
        left.x *= right;
        left.y *= right;
    }

    template <typename T>
    Vector2<T> operator/(const Vector2<T> &left, T right)
    {
        return (Vector2<T>(left.x / right, left.y / right));
    }

    template <typename T>
    Vector2<T> &operator/=(Vector2<T> &left, T right)
    {
        left.x /= right;
        left.y /= right;
    }

    template <typename T>
    bool operator==(const Vector2<T> &left, const Vector2<T> &right)
    {
        return (left.x == right.x && left.y == right.y);
    }

    template <typename T>
    bool operator!=(const Vector2<T> &left, const Vector2<T> &right)
    {
        return !(left == right);
    }

    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
}

#endif /* !POS_HPP_ */