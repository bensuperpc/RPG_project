/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** People.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef _PEOPLE_HPP_
#    define _PEOPLE_HPP_

class People : public virtual sf::RectangleShape {
  public:
    People();
    ~People();
  bool is_contaminated = false;
  
  private:
  protected:
};

#endif