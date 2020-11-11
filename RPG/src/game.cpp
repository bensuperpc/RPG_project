/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Game.cpp
*/

#include "game.hpp"

Game::Game()
{
}

void Game::Launch()
{
    
    /*
    this->buffer.emplace_back(sf::SoundBuffer());
     if (!buffer.loadFromFile("../music/Supertask_Orchestra_version.ogg"))
        return;
    */

    title::load_titlemap(this->title_map, "../title_map/title_map_1.txt");

    const std::string path = "../texture/rpg-pack/tiles/";

    my::texture::load_texture(this->textureUMap, path);
    // my::texture::load_texture(this->textureMap, path);
    // my::texture::load_texture(this->textureList, path);

#if __cplusplus <= 201402L
    my::texture::load_texturemap(this->textureumap, "../texture_map/texture_map_0.csv");
    // my::texture::load_texturemap(this->texturemap, "../texture_map/texture_map_0.csv");
    // my::texture::load_texturemap(this->texturelist, "../texture_map/texture_map_0.csv");

#elif __cplusplus >= 201703L
    my::texture::load_texturemap<std::string>(this->textureumap, "../texture_map/texture_map_0.csv");
    // my::texture::load_texturemap<std::string>(this->texturemap, "../texture_map/texture_map_0.csv");
    // my::texture::load_texturemap<std::string>(this->texturelist, "../texture_map/texture_map_0.csv");
#else
#endif

    // this->sound.setBuffer(buffer);
    // this->sound.play();
    // this->sound.setLoop(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    /*
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(  desktopMode.width/4,
                                            desktopMode.height/4,
                                            desktopMode.bitsPerPixel),
                            "SFML part 5",
                            sf::Style::Fullscreen);
    */
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Benoit", sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);
    glEnable(GL_TEXTURE_2D);

    // window.setFramerateLimit(5);

    window.setActive(false);
    // window.setJoystickThreshold(100.0f);

    std::thread display_thread(&Game::renderingThread, this, &window);
    display_thread.join();
}

Game::~Game()
{
#if __cplusplus >= 201703L
    /*
    for (auto &&elem : this->drawSprite) {
        elem.release();
        elem.reset();
    }*/
#else
    for (auto &&elem : this->drawPlayer) {
        delete elem;
    }
    for (auto &&elem : this->drawSprite) {
        delete elem;
    }
    for (auto &&elem : this->drawTitle) {
        delete elem;
    }
    for (auto &&elem : this->drawBlock) {
        delete elem;
    }
    for (auto &&elem : this->textureList) {
        delete elem.second;
    }
    textureList.clear();
    textureList.shrink_to_fit();
    for (const auto &element : textureMap) {
        delete element.second;
    }
    textureMap.clear();

    for (const auto &element : textureUMap) {
        delete element.second;
    }
    textureUMap.clear();
#endif
}

void Game::drawTitle_fn()
{
    const size_t &texture_size = 64;
    for (size_t x = 0; x < this->title_map.size(); x++) {
        for (size_t y = 0; y < this->title_map[x].size(); y++) {
            try {
#if __cplusplus <= 201402L
                Title *title = new Title();
#elif __cplusplus >= 201703L
                std::unique_ptr<Title> title = std::make_unique<Title>();
#else
#endif
                auto &&its = this->textureumap.find(title_map[x][y]);
                if (its != this->textureumap.end()) {
                    auto &&it = this->textureUMap.find(its->second);
                    if (it == this->textureUMap.end()) {
                        std::cout << "Key-value pair not present in map" << std::endl;
                    } else {
#if __cplusplus <= 201402L
                        title->setTexture(it->second);
#elif __cplusplus >= 201703L
                        title->setTexture(it->second.get());
#else
#endif
                    }
                }
                /*
                const int &&X = title_map[x][y];
                auto its = std::find_if(this->texturelist.begin(), this->texturelist.end(), [&X](const std::pair<const int, const std::string &> &p)
                {
                    return p.first == X;
                    });
                if (its != this->texturelist.end()) {
                    const std::string Y = its->second;
                    auto &&it
                        = std::find_if(this->textureList.begin(), this->textureList.end(), [&Y](const std::pair<const std::string, sf::Texture *> &t)
                        {
                            return t.first == Y;
                        });
                    if (it == this->textureList.end()) {
                        std::cout << "Key-value pair not present in map:" << Y << std::endl;
                    } else {
                        title->setTexture(it->second);
                    }
                }
                */
                title->setPosition(static_cast<float>(texture_size * y), static_cast<float>(texture_size * x));
                title->setSize(sf::Vector2f(static_cast<float>(texture_size), static_cast<float>(texture_size)));
                // title->setTextureRect(sf::IntRect(0, 0, (int)texture->getSize().x, (int)texture->getSize().y);
#if __cplusplus <= 201402L
                this->drawTitle.emplace_back(title);
#elif __cplusplus >= 201703L
                this->drawTitle.emplace_back(std::move(title));
#else
#endif
            }
            catch (...) {
                std::cout << "failed to load texture, wrong texture ID !" << std::endl;
            }
        }
    }
}

void Game::renderingThread(sf::RenderWindow *window)
{
    sf::Music music;
    if (music.openFromFile("../music/Supertask_Orchestra_version.ogg"))
    {
        std::cout << "Music: OK" << std::endl;
        music.play();
        music.setLoop(true);
    } else {
        std::cout << "Music: KO" << std::endl;
    }
    /*
    //music.setLoop(true);
    while (music.getStatus() == sf::Music::Playing)
    {
    }*/
    sf::Clock timer;
    if (!sf::Shader::isAvailable()) {
        std::cout << "Shader are not available" << std::endl;
    }
    sf::Shader shader;
    if (!shader.loadFromFile("../shaders/example_001.frag", sf::Shader::Fragment)) {
        std::cout << "Error while shaders" << std::endl;
        return;
    }
    /*
    sf::Shader shader2;
    if (!shader2.loadFromFile("../shaders/example_002.frag", sf::Shader::Fragment)) {
        std::cout << "Error while shaders" << std::endl;
        return;
    }*/

    sf::Texture distortionMap;

    if (!distortionMap.loadFromFile("../shaders/distortion_map.png")) {
        sf::err() << "Error while loading distortion map" << std::endl;
        return;
    }

    distortionMap.setRepeated(true);
    distortionMap.setSmooth(true);

    shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
    shader.setUniform("distortionMapTexture", distortionMap);

    // sf::Vector2<float> res = sf::Vector2<float>(1280, 720);
    // shader2.setUniform("resolution", res);
    // shader2.setUniform("currentTexture", sf::Shader::CurrentTexture);

    float distortionFactor = .05f;
    float riseFactor = .3f;

    window->setActive(true);
    sf::View view1(sf::Vector2f(200, 200), sf::Vector2f(1920, 1080));
    view1.zoom(DEFAULT_ZOOM);
    window->setView(view1);

    sf::Font font;
    font.loadFromFile("../font/Almond_Caramel.ttf");
    // Create a text
   
#if __cplusplus <= 201402L
    sf::Text  *text = new sf::Text("hello", font);
#elif __cplusplus >= 201703L
    std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>("hello", font);
#else
#endif

    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    text->setFillColor(sf::Color::Blue);
    this->drawGUI.emplace_back(std::move(text));

    this->FPS.setFont(font);
    this->FPS.setPosition(-400.0, -200.0);
    this->FPS.setColor(sf::Color::Red);
    this->FPS.setCharacterSize(30);
    //
    //  LoadTectures
    //
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../texture/PIPOYA FREE RPG Character Sprites 32x32/Female/Female 01-1.png")) {
        std::cout << "Texture not found !" << std::endl;
    }
    playerTexture.setSmooth(true);

    sf::Texture texture2;
    if (!texture2.loadFromFile("../texture/rpg-pack/mobs/boss_bee.png")) {
        std::cout << "Texture not found !" << std::endl;
    }
    texture2.setSmooth(true);


    this->drawTitle_fn();

#if __cplusplus <= 201402L
    Entity *player = new Entity();
#elif __cplusplus >= 201703L
    std::unique_ptr<Entity> player = std::make_unique<Entity>();
#else
#endif
    player->setPosition(100.0, 100.0);
    player->setSize(sf::Vector2f(32, 32));
    // sf::RectangleShape rectangle(sf::Vector2f(50, 50));
    player->setTexture(&playerTexture);
    player->setTextureRect(sf::IntRect(0, 0, 32, 32));
    player->setMeleeAttack(1.0f);
    player->setOutlineThickness(1);
    player->setOutlineColor(sf::Color(255, 0, 0));
    this->drawPlayer.emplace_back(std::move(player));
    // player.release();

#if __cplusplus <= 201402L
    Entity *enemy = new Entity();
#elif __cplusplus >= 201703L
    std::unique_ptr<Entity> enemy = std::make_unique<Entity>();
#else
#endif
    enemy->setPosition(0.0, 0.0);
    enemy->setSize(sf::Vector2f(100, 100));
    // sf::RectangleShape rectangle(sf::Vector2f(50, 50));
    enemy->setTexture(&texture2);
    // enemy->setTextureRect(sf::IntRect(0, 0, 32, 32));
    enemy->setOutlineThickness(1);
    enemy->setOutlineColor(sf::Color(255, 0, 0));
    this->drawSprite.emplace_back(std::move(enemy));
    // enemy.release();

#if __cplusplus <= 201402L
    Entity *shape2 = new Entity();
#elif __cplusplus >= 201703L
    std::unique_ptr<Entity> shape2 = std::make_unique<Entity>();
#else
#endif
    shape2->setSize(sf::Vector2f(100, 100));
    shape2->setPosition(-10.0, -10.0);
    shape2->setFillColor(sf::Color(0, 255, 0));
    this->drawBlock.emplace_back(std::move(shape2));
    // shape2.release();
    // this->drawSprite.ewindow.draw(text);mplace_back(std::make_unique(player));
    sf::View gui = window->getView();

    sf::Clock clock;
    // the rendering loop
    while (window->isOpen()) {
        window->clear(DEFAULT_BACKGROUND);
        sf::View standard = window->getView();

        sf::Time frameTime = clock.restart();
        float framerate = 1 / (frameTime.asMilliseconds() * 0.001);
        this->speed = 120.0 / framerate;
#ifdef DNDEBUG
        std::cout << "FPS:" << framerate << std::endl;
#endif
        std::ostringstream ss;
        ss << framerate << " FPS";
        this->FPS.setString(ss.str());

        if (!this->drawPlayer[0]->getGlobalBounds().intersects(this->drawSprite[0]->getGlobalBounds())) {
#if __cplusplus <= 201402L
            auto Sprite = this->drawSprite[0];
#elif __cplusplus >= 201703L
            auto Sprite = this->drawSprite[0].get();
#else
#endif
            const auto &&diffx = Sprite->distanceX(this->drawPlayer[0]);
            const auto &&diffy = Sprite->distanceY(this->drawPlayer[0]);
            if (Sprite->getPosition().x + 35.0 > this->drawPlayer[0]->getPosition().x) {
                Sprite->move(-1.0 * diffx * 0.025 * this->speed, 0.0);
            } else {
                Sprite->move(1.0 * diffx * 0.025 * this->speed, 0.0);
            }
            if (Sprite->getPosition().y + 35.0 > this->drawPlayer[0]->getPosition().y) {
                Sprite->move(0.0, -1.0 * diffy * 0.025 * this->speed);
            } else {
                Sprite->move(0.0, 1.0 * diffy * 0.025 * this->speed);
            }
        }
        for (auto &elem : this->drawPlayer) {
            if (elem->getGlobalBounds().intersects(this->drawBlock[0]->getGlobalBounds())) {
#ifdef DNDEBUG
                std::cout << "Boom" << std::endl;
#endif
#if __cplusplus <= 201402L
                auto ent = this->drawBlock[0];
#elif __cplusplus >= 201703L
                auto ent = this->drawBlock[0].get();
#else
#endif
                ent->setFillColor(sf::Color(255, 255, 255));
                ent->setSize(sf::Vector2f(100, 100));
                // ent->setRadius(40);
            } else {
#if __cplusplus <= 201402L
                Entity *ent = this->drawBlock[0];
#elif __cplusplus >= 201703L
                Entity *ent;
                ent = this->drawBlock[0].get();
#else
#endif
                ent->setFillColor(sf::Color(0, 255, 0));
                ent->setSize(sf::Vector2f(100, 100));
            }
        }
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::Resized) {
                this->windowSizeX = sf::VideoMode::getDesktopMode().width;
                this->windowSizeY = sf::VideoMode::getDesktopMode().height;
                glViewport(0, 0, (int)event.size.width, (int)event.size.height);
            }

            if (event.type == sf::Event::LostFocus) {
#ifdef DNDEBUG
                std::cout << "LostFocus" << std::endl;
#endif
            }

            if (event.type == sf::Event::GainedFocus) {
#ifdef DNDEBUG
                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
#endif
                /*drawGUI
                    view2.zoom(1.0f);
                } else {
                    view2.zoom(0.25f);
                }
                window->setView(view2);
                */
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
#ifdef DNDEBUG
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
#endif
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
#ifdef DNDEBUG
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
#endif
                }
            }
            if (event.type == sf::Event::MouseMoved) {
#ifdef DNDEBUG
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "nesf::Soundw mouse y: " << event.mouseMove.y << std::endl;
#endif
            }
            if (event.type == sf::Event::MouseEntered) {
#ifdef DNDEBUG
                std::cout << "the mouse cursor has entered the window" << std::endl;
#endif
            }

            if (event.type == sf::Event::MouseLeft) {
#ifdef DNDEBUG
                std::cout << "the mouse cursor has left the window" << std::endl;
#endif
            }
            if (event.type == sf::Event::JoystickMoved) {
                if (event.joystickMove.axis == sf::Joystick::X) {
#ifdef DNDEBUG
                    std::cout << "X axis moved!" << std::endl;
                    std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << event.joystickMove.position << std::endl;
#endif
                }
            }
            if (event.joystickMove.axis == sf::Joystick::X || event.joystickMove.axis == sf::Joystick::Y) {
                const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                this->drawPlayer[0]->move((x / 12.0) * this->speed/1.25, (y / 12.0) * this->speed/1.25);
                standard.move((x / 12.0) * this->speed / 1.25, (y / 12.0) * this->speed/1.25);
            }
            if (event.type == sf::Event::JoystickButtonPressed) {
#ifdef DNDEBUG
                std::cout << "joystick button pressed!" << std::endl;
                std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
                std::cout << "button: " << event.joystickButton.button << std::endl;
#endif
            }
        }
        for (size_t i = 0; i < this->drawPlayer.size(); i++)
        {
            if (sf::Joystick::isConnected(i)) {
                const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

                this->drawPlayer[i]->move((x / 12.0), (y / 12.0));
                standard.move(x / 12.0, y / 12.0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            Screen_save_gl::saveScreenshotToFile("../screenshot/screenshot_" + my::date::get_date() + ".png", window->getSize().x, window->getSize().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            standard.zoom(DEFAULT_ZOOM);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) {
            // sf::View view3(sf::Vector2f(300, 300), sf::Vector2f(1920, 1080));
            //sf::View view3(window->getView().getCenter(), sf::Vector2f(1280, 720));
            standard.rotate(5);
        }
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
#ifdef DNDEBUG
                std::cout << "Left" << std::endl;
#endif
                // riseFactor *= 2.f;
                this->drawPlayer[0]->move(-7.0 * this->speed, 0.0);
                this->drawPlayer[0]->setTexture(&playerTexture);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 32, 32, 32));
                standard.move(-7.0 * this->speed, 0.0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
#ifdef DNDEBUG
                std::cout << "Right " << std::endl;
#endif
                // riseFactor /= 2.f;
                this->drawPlayer[0]->move(7.0 * this->speed, 0.0);
                this->drawPlayer[0]->setTexture(&playerTexture);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 64, 32, 32));
                standard.move(7.0 * this->speed, 0.0);
            }
        }
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
#ifdef DNDEBUG
                std::cout << "Up" << std::endl;
#endif
                // distortionFactor *= 2.f;
                this->drawPlayer[0]->move(0.0, -7.0 * this->speed);
                this->drawPlayer[0]->setTexture(&playerTexture);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 96, 32, 32));
                standard.move(0.0, -7.0 * this->speed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
#ifdef DNDEBUG
                std::cout << "Down" << std::endl;
#endif
                // distortionFactor /= 2.f;
                this->drawPlayer[0]->move(0.0, 7.0 * this->speed);
                this->drawPlayer[0]->setTexture(&playerTexture);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 0, 32, 32));
                standard.move(0.0, 7.0 * this->speed);
            }
        }
        // Set view
        window->setView(standard);
        // Draw all Entities/Items ect...
        for (auto &elem : this->drawTitle)
            window->draw(*elem, &shader);
        for (auto &elem : this->drawBlock)
            window->draw(*elem);
        for (auto &elem : this->drawSprite)
            window->draw(*elem);
        for (auto &elem : this->drawPlayer)
            window->draw(*elem);
        //Gui
        window->setView(gui);
        for (auto &elem : this->drawGUI)
            window->draw(*elem);
        window->draw(this->FPS);
        window->setView(standard);
        // this->screen_save.add_frame(window);
        //
        // window->pushGLStates();
        // window->resetGLStates();
        shader.setUniform("time", timer.getElapsedTime().asSeconds());
        // shader2.setUniform("time", timer.getElapsedTime().asSeconds());
        shader.setUniform("distortionFactor", distortionFactor);
        shader.setUniform("riseFactor", riseFactor);
        window->display();
        // window->popGLStates();
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
