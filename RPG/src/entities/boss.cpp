/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** boss.cpp
*/

#include "boss.hpp"

Boss::Boss()
{
}

Boss::~Boss()
{
}

Boss Boss::operator<<(const Boss &player)
{
    Boss p = Boss();
    return p;
}
