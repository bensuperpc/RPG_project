/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Entity.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#ifndef _ENTITY_H_
#    define _ENTITY_H_

class Entity : public virtual sf::RectangleShape {
  public:
    Entity();
    ~Entity();
    // virtual bool canMove() = 0;
    // virtual bool canMove() = 0;
    // void SetTexture(const sf::Texture* texture);

    bool isOutWindow(sf::RenderWindow *);
    bool isInWindow(sf::RenderWindow *);

    bool moveInWindow(unsigned int &, unsigned int &, const float &, const float &);

    int64_t getLife();
    // void setLife(int64_t&);
    void setLife(int64_t *);

  private:
    int64_t life = 0;

  protected:
};

#endif