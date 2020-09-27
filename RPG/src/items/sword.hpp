/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** item.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "weapon.hpp"

#ifndef _SWORD_HPP_
#    define _SWORD_HPP_

class Sword : public virtual Weapon {
  public:
    Sword();
    ~Sword();

  private:
  protected:
};

#endif