/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** item.hpp
*/

#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Item : public virtual sf::RectangleShape {
  public:
    Item();
    ~Item();
    // std::shared_ptr<sf::Texture> texture = nullptr;
    // sf::Texture *texture = nullptr;

    double getLife();
    void setLife(double *);

    uint64_t itemID = 0;

  private:
    // Life, attack and def
    double life = 0.0;

  protected:
};

#endif