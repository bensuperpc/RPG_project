/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** weapon.cpp
*/

#include "weapon.hpp"

Weapon::Weapon()
{
}

double Weapon::getMeleeAttack()
{
    return this->melee_attack;
}

void Weapon::setMeleeAttack(double *_melee_attack)
{
    this->melee_attack = *_melee_attack;
}

void Weapon::setMeleeAttack(const double &_melee_attack)
{
    this->melee_attack = _melee_attack;
}

double Weapon::getMagicAttack()
{
    return this->magic_attack;
}
void Weapon::setMagicAttack(double *_magic_attack)
{
    this->magic_attack = *_magic_attack;
}

Weapon::~Weapon()
{
}
