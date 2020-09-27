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

  protected:
};

#endif