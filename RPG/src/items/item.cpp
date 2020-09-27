/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** item.cpp
*/

#include "item.hpp"

Item::Item()
{
}

double Item::getLife()
{
    return life;
}

void Item::setLife(double *_life)
{
    this->life = *_life;
}

Item::~Item()
{
}
