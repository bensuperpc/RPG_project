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
    // sf::Texture *texture = nullptr;

    double getLife();
    void setLife(double *);

    double getMeleeAttack();
    void setMeleeAttack(double *);
    void setMeleeAttack(const double &);

    double getMagicAttack();
    void setMagicAttack(double *);

    double getMagicDef();
    void setMagicDef(double *);

    double getMeleeDef();
    void setMeleeDef(double *);

    std::pair<double, double> distance(const Entity *);

    double distanceX(const Entity *);
    double distanceY(const Entity *);

    std::pair<double, double> distance(const std::unique_ptr<Entity> &);

    double distanceX(const std::unique_ptr<Entity> &);
    double distanceY(const std::unique_ptr<Entity> &);

  private:
    // Life, attack and def
    double life = 0.0;
    double mana = 0.0;
    double strength = 0.0;
    double speed = 0.0;
    double food = 0.0;


    double melee_attack = 0.0;
    double magic_attack = 0.0;
    double magic_defence = 0.0;
    double melee_defence = 0.0;
    // inventory
    std::vector<size_t> inventory {};

  protected:
};

#endif