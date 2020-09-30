/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** item.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "item.hpp"

#ifndef _WEAPON_HPP_
#    define _WEAPON_HPP_

class Weapon : public virtual Item {
  public:
    Weapon();
    ~Weapon();

    double getMeleeAttack();
    void setMeleeAttack(double *);
    void setMeleeAttack(const double &);

    double getMagicAttack();
    void setMagicAttack(double *);

  private:
    double melee_attack = 0.0;
    double magic_attack = 0.0;
    double magic_defence = 0.0;
    double melee_defence = 0.0;
    double distance_attack = 0.0;
    double attack_speed = 0.0;

    bool isTwoHand = false;
#    pragma GCC diagnostic ignored "-Wpadded"
    int64_t attack_count = 0;
    int64_t def_count = 0;

  protected:
};

#endif