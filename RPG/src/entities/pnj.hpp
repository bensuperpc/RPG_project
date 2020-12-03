/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** PNJ.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.hpp"

#ifndef _PNJ_HPP_
#    define _PNJ_HPP_

class PNJ : public virtual Entity {
  public:
    PNJ();
    ~PNJ();
    PNJ operator<<(const PNJ &);

  private:
    std::vector<std::string> speech {};

  protected:
};

#endif
