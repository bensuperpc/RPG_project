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
#include "convert_utils/sfml_utils.hpp"
#include "texture/load_texture.hpp"
#include "texture/load_texturemap.hpp"
#include "texture/load_title.hpp"
#include "texture/load_titlemap.hpp"
#include "texture/sfml_screenshot.hpp"
#include "texture/title.hpp"
#include "time/date/date.hpp"
#include "utils/opengl/screen_save.hpp"

// Entities
#include "entities/boss.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"

#if __cplusplus <= 201402L
#    include "std/std.hpp"
#endif
#if __cplusplus >= 201703L
#    include <string_view>
#endif

// Default settings
#define DEFAULT_ZOOM 1.0f

#define DEFAULT_BACKGROUND sf::Color::Black

//#include <boost/multiprecision/float128.hpp>

class Game {
  public:
    Game();
    void init();
    void run();
    ~Game();
    float speed = 1.0;
    const size_t texture_size = 64;
    sf::ContextSettings settings;

    // Shaders 1
    sf::Texture distortionMap;
    sf::Shader shader;
    float distortionFactor = .05f;
    float riseFactor = .3f;

    std::vector<sf::Texture> playerTexture = {};
    std::vector<sf::Texture> bossTexture = {};

  private:
    void load_texture(std::vector<sf::Texture> &, std::string &);
    void renderingThread(sf::RenderWindow *);
    unsigned int windowSizeX = sf::VideoMode::getDesktopMode().width;
    unsigned int windowSizeY = sf::VideoMode::getDesktopMode().height;
    // sf::RenderWindow window;
    sf::Font font;
    sf::Music music;

    // Drawing elements lists
    std::vector<std::unique_ptr<sf::Drawable>> drawGUI_unique = {};
    std::vector<std::shared_ptr<sf::Drawable>> drawGUI_shared = {};
    std::vector<std::unique_ptr<Entity>> drawPlayer = {};
    std::vector<std::unique_ptr<Entity>> drawEntity = {};
    std::vector<std::unique_ptr<sf::RectangleShape>> drawBlock = {};
    std::vector<std::unique_ptr<sf::RectangleShape>> drawTitle = {};

    // Current fps counter
    std::shared_ptr<sf::Text> FPS = std::make_shared<sf::Text>();

    std::vector<sf::SoundBuffer> buffer {};
    sf::Sound sound = sf::Sound();

    // Event
    sf::Event event;

    // List of position map texture
    std::vector<std::vector<size_t>> title_map {};

    // Associated int from title_map to texture path
    std::map<int, std::string> texturemap {};
    std::unordered_map<int, std::string> textureumap {};
    std::vector<std::pair<int, std::string>> texturelist {};

    // List Associated texture path to texture
    std::vector<std::pair<std::string, std::unique_ptr<sf::Texture>>> textureList = {};
    std::map<std::string, std::unique_ptr<sf::Texture>> textureMap = {};
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textureUMap = {};

  protected:
};

#endif