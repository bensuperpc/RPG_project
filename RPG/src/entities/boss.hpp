/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Boss.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

#ifndef _BOSS_HPP_
#    define _BOSS_HPP_

class Boss : public virtual Entity {
  public:
    Boss();
    ~Boss();
    Boss operator<<(const Boss &);

  private:
    int64_t stade = 0;

  protected:
};

#endif
