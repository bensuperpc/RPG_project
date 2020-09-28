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
#include "../entities/entity.hpp"

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
    std::string ownerName = "";

    // Life, attack and def
    double life = 0.0;
    double durability = 0.0;    // if under 0.0, weapon break or other things.
    double repairability = 0.0; // Less, weapon it harder to repair, under 0.0, weapon can't repair

    int64_t level = 0;   // Level of item
    double weight = 0.0; // weight
    double size = 0.0;   // IN meter
    double value = 0.0;  // in $

    int64_t repair_count = 0;

  protected:
};

#endif