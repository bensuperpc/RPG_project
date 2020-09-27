/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Player.cpp
*/

#include "src/entities/player.hpp"

Player::Player()
{
}

Player::~Player()
{
}

Player Player::operator<<(const Player &player)
{
    Player p = Player();
    return p;
}
