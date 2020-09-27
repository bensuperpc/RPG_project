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
    double distance_attack = 0.0;

    double durability = 0.0;    // if under 0.0, weapon break or other things.
    double repairability = 0.0; // Less, weapon it harder to repair, under 0.0, weapon can't repair

    int64_t level = 0;   // Level of weapon
    double weight = 0.0; // weight
    double value = 0.0;  // in $

    int64_t repair_count = 0;
    int64_t attack_count = 0;
    int64_t def_count = 0;

  protected:
};

#endif