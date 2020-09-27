/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Player.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "src/entities/entity.hpp"

#ifndef _PLAYER_H_
#    define _PLAYER_H_

class Player : public virtual Entity {
  public:
    Player();
    ~Player();
    Player operator<<(const Player &);

  private:
  protected:
};

#endif
