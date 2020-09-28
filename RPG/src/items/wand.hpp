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

#ifndef _WAND_HPP_
#    define _WAND_HPP_

class Wand : public virtual Weapon {
  public:
    Wand();
    ~Wand();

  private:
  protected:
};

#endif