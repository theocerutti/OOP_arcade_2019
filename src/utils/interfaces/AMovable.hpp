/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** IMovable
*/

#ifndef IMOVABLE_HPP_
#define IMOVABLE_HPP_

#include "../Vector2.hpp"

namespace Arcade {
    class AMovable {
        public:
            virtual ~AMovable() = default;

            void setPosition(float x, float y) {
                this->pos.x = x;
                this->pos.y = y;
            }
            void setPosition(const Vector2f &pos) {
                this->pos.x = pos.x;
                this->pos.y = pos.y;
            }
            const Vector2f &getPosition() const {
                return this->pos;
            }

            void setRotation(float angle) {
                this->angle = angle;
            }
            float getRotation() const {
                return this->angle;
            }

            const Vector2f &getOrigin() const {
                return this->origin;
            }
            void setOrigin(const Vector2f &point) {
                this->origin.x = point.x;
                this->origin.y = point.y;
            }
            void setOrigin(float x, float y) {
                this->origin.x = x;
                this->origin.y = y;
            }

            void move(float decalx, float decaly) {
                this->pos.x += decalx;
                this->pos.y += decaly;
            }
            void move(const Vector2f &decal) {
                this->pos.x += decal.x;
                this->pos.y += decal.y;
            }

        private:
            float angle = 0;
            Vector2f origin = Vector2f(0.f, 0.f);
            Vector2f pos = Vector2f(0.f, 0.f);
    };
}

#endif /* !IMOVABLE_HPP_ */