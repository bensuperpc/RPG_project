/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Entity.cpp
*/

#include <SFML/Window.hpp>
#include <iostream>
#include "src/entities/entity.hpp"

Entity::Entity()
{
}

int64_t Entity::getLife()
{
    return life;
}

void Entity::setLife(int64_t *_life)
{
    this->life = *_life;
}

bool Entity::isOutWindow(sf::RenderWindow *window)
{
    return !this->isInWindow(window);
}

bool Entity::isInWindow(sf::RenderWindow *window)
{
    return true; // this->moveInWindow(4, 4 , 0.0, 0.0);
}

bool Entity::moveInWindow(unsigned int &sizeX, unsigned int &sizeY, const float &moveX, const float &moveY)
{
    const float &x1 = this->getPosition().x;
    const float &y1 = this->getPosition().y;
    const float &x2 = this->getLocalBounds().width;
    const float &y2 = this->getLocalBounds().height;

    std::cout << "PosX:" << x1 << std::endl;
    std::cout << "PosY:" << y1 << std::endl;
    if (x1 + moveX < 0.0 || (x1 + x2 + moveX) > sizeX) {
        std::cout << "Is out" << std::endl;
        return true;
    }
    if (y1 + moveY < 0.0 || (y1 + y2 + moveY) > sizeY) {
        std::cout << "Is out" << std::endl;
        return true;
    }
    std::cout << "Is in" << std::endl;
    return true;
}

Entity::~Entity()
{
}
