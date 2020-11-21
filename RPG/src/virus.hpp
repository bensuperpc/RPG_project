/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Virus.hpp
*/

#ifndef _VIRUS_HPP_
#define _VIRUS_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <thread>
#include "entities/people.hpp"

#if __cplusplus >= 201703L
#    include <string_view>
#endif

// Default settings
#define DEFAULT_ZOOM 0.75f

#define DEFAULT_BACKGROUND sf::Color::Black

//#include <boost/multiprecision/float128.hpp>

class Virus {
  public:
    Virus();
    void Launch();
    ~Virus();
    float speed = 1.0;

  private:
    void renderingThread(sf::RenderWindow *);
    unsigned int windowSizeX = sf::VideoMode::getDesktopMode().width;
    unsigned int windowSizeY = sf::VideoMode::getDesktopMode().height;
#if __cplusplus <= 201402L
    std::vector<sf::Drawable *> drawGUI = {};
    std::vector<sf::RectangleShape *> drawPlayer = {};
    std::vector<People> drawSprite = {};
    std::vector<sf::RectangleShape *> drawBlock = {};
    std::vector<sf::RectangleShape *> drawTitle = {};

#elif __cplusplus >= 201703L
    std::vector<std::unique_ptr<sf::Drawable>> drawGUI = {};
    std::vector<std::unique_ptr<sf::RectangleShape>> drawPlayer = {};
    std::vector<std::unique_ptr<People>> drawSprite = {};
    std::vector<std::unique_ptr<sf::RectangleShape>> drawBlock = {};
    std::vector<std::unique_ptr<sf::RectangleShape>> drawTitle = {};

#else
#endif
    sf::Text FPS;

    std::vector<sf::SoundBuffer> buffer {};
    sf::Sound sound = sf::Sound();

  protected:
};

#endif