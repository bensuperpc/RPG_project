/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Entity.cpp
*/

#include <SFML/Window.hpp>
#include <iostream>
#include "entity.hpp"

Entity::Entity()
{
}

double Entity::getLife()
{
    return life;
}

void Entity::setLife(double *_life)
{
    this->life = *_life;
}

double Entity::getMeleeAttack()
{
    return this->melee_attack;
}

void Entity::setMeleeAttack(double *_melee_attack)
{
    this->melee_attack = *_melee_attack;
}

void Entity::setMeleeAttack(const double &_melee_attack)
{
    this->melee_attack = _melee_attack;
}

double Entity::getMagicAttack()
{
    return this->magic_attack;
}
void Entity::setMagicAttack(double *_magic_attack)
{
    this->magic_attack = *_magic_attack;
}

double Entity::getMagicDef()
{
    return this->magic_defence;
}

void Entity::setMagicDef(double *_magic_defence)
{
    this->magic_defence = *_magic_defence;
}

double Entity::getMeleeDef()
{
    return this->melee_defence;
}
void Entity::setMeleeDef(double *_melee_defence)
{
    this->melee_defence = *_melee_defence;
}

double Entity::distanceX(const Entity *ent)
{
    return std::max(this->getPosition().x, ent->getPosition().x) - std::min(this->getPosition().x, ent->getPosition().x);
}

double Entity::distanceY(const std::unique_ptr<Entity> &ent)
{
    return std::max(this->getPosition().y, ent->getPosition().y) - std::min(this->getPosition().y, ent->getPosition().y);
}

double Entity::distanceX(const std::unique_ptr<Entity> &ent)
{
    return std::max(this->getPosition().x, ent->getPosition().x) - std::min(this->getPosition().x, ent->getPosition().x);
}

double Entity::distanceY(const Entity *ent)
{
    return std::max(this->getPosition().y, ent->getPosition().y) - std::min(this->getPosition().y, ent->getPosition().y);
}

std::pair<double, double> Entity::distance(const Entity *ent)
{
    return std::pair<double, double>(this->distanceX(ent), this->distanceY(ent));
}

std::pair<double, double> Entity::distance(const std::unique_ptr<Entity> &ent)
{
    return std::pair<double, double>(this->distanceX(ent), this->distanceY(ent));
}

Entity::~Entity()
{
}
