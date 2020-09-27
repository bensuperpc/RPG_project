/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** bow.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "weapon.hpp"

#ifndef _BOW_HPP_
#    define _BOW_HPP_

class Bow : public virtual Weapon {
  public:
    Bow();
    ~Bow();

  private:
  protected:
};

#endif
