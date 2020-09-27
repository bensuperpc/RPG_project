/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Game.hpp
*/

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "lib/convert_utils/sfml_utils.hpp"
#include "lib/texture/load_texture.hpp"
#include "lib/texture/load_texturemap.hpp"
#include "lib/texture/load_titlemap.hpp"
#include "lib/texture/sfml_screenshot.hpp"
#include "lib/time/chrono/chrono.hpp"
#include "lib/time/date/date.hpp"
#include "lib/utils/opengl/screen_save.hpp"
#include "texture/title.hpp"

#if __cplusplus >= 201703L
#    include <string_view>
#endif

// Default settings
#define DEFAULT_ZOOM 0.75f

#define DEFAULT_BACKGROUND sf::Color::Black

//#include <boost/multiprecision/float128.hpp>

class Game {
  public:
    Game();
    void Launch();
    ~Game();

  private:
    void load_texture(std::vector<sf::Texture> &, std::string &);
    void drawTitle_fn();
    void renderingThread(sf::RenderWindow *);
    unsigned int windowSizeX = sf::VideoMode::getDesktopMode().width;
    unsigned int windowSizeY = sf::VideoMode::getDesktopMode().height;
#if __cplusplus <= 201402L
    std::vector<Entity *> drawSprite {};
    std::vector<Entity *> drawBlock {};
    std::vector<Title *> drawTitle {};

    std::vector<std::pair<const std::string, sf::Texture *>> textureList {};
    std::map<const std::string, sf::Texture *> textureMap {};
    std::unordered_map<std::string, sf::Texture *> textureUMap {};

#elif __cplusplus >= 201703L
    std::vector<std::unique_ptr<Entity>> drawSprite {};
    std::vector<std::unique_ptr<Entity>> drawBlock {};
    std::vector<std::unique_ptr<Title>> drawTitle {};
    std::vector<std::pair<const std::string, std::unique_ptr<sf::Texture>>> textureList {};
    std::map<const std::string, std::unique_ptr<sf::Texture>> textureMap {};
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textureUMap {};

#else
#endif

    std::vector<std::vector<size_t>> title_map {};
    std::vector<std::vector<size_t>> myNumbers {};

    std::vector<sf::SoundBuffer> buffer {};
    sf::Sound sound = sf::Sound();

    std::map<const int, std::string> texturemap {};
    std::unordered_map<int, std::string> textureumap {};
    std::vector<std::pair<const int, const std::string>> texturelist {};

  protected:
};

#endif