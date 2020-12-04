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

void Game::init()
{
    //  Load default font
    this->font.loadFromFile("../font/Almond_Caramel.ttf");

    //  Load title map
    title::load_titlemap(this->title_map, "../title_map/title_map_1.txt");

    //  Load texture
    const std::string path = "../texture/rpg-pack/tiles/";

    my::texture::load_texture(this->textureUMap, path);
    my::texture::load_texture(this->textureMap, path);
    my::texture::load_texture(this->textureList, path);
    
    //  Link texture path and title map
    my::texture::load_texturemap<std::string>(this->textureumap, "../texture_map/texture_map_0.csv");
    my::texture::load_texturemap<std::string>(this->texturemap, "../texture_map/texture_map_0.csv");
    my::texture::load_texturemap<std::string>(this->texturelist, "../texture_map/texture_map_0.csv");
    
    //  Emplace texture
    // my::title::emplaceTitle(this->drawTitle, this->title_map, this->textureUMap, this->textureumap, this->texture_size);
    // my::title::emplaceTitle(this->drawTitle, this->title_map, this->textureMap, this->texturemap, this->texture_size);
    my::title::emplaceTitle(this->drawTitle, this->title_map, this->textureList, this->texturelist, this->texture_size);
    
    //  Windows settings
    this->settings.antialiasingLevel = 8;
    this->settings.depthBits = 24;
    this->settings.stencilBits = 8;
    this->settings.majorVersion = 3;
    this->settings.minorVersion = 0;

    //  Shaders
        if (!this->shader.loadFromFile("../shaders/example_001.frag", sf::Shader::Fragment)) {
        std::cout << "Error while shaders" << std::endl;
        return;
    }

    if (!this->distortionMap.loadFromFile("../shaders/distortion_map.png")) {
        sf::err() << "Error while loading distortion map" << std::endl;
        return;
    }

    this->distortionMap.setRepeated(true);
    this->distortionMap.setSmooth(true);

    this->shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
    this->shader.setUniform("distortionMapTexture", this->distortionMap);

}

void Game::run()
{

    /*
    this->buffer.emplace_back(sf::SoundBuffer());
     if (!buffer.loadFromFile("../music/Supertask_Orchestra_version.ogg"))
        return;
    */

    // this->sound.setBuffer(buffer);
    // this->sound.play();
    // this->sound.setLoop(true);

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    /*
    sf::RenderWindow window(sf::VideoMode(desktopMode.width/4,
                                            desktopMode.height/4,
                                            desktopMode.bitsPerPixel),
                            "SFML part 5",
                            sf::Style::Fullscreen);
    */
    /*
     sf::RenderWindow window(
         sf::VideoMode(desktopMode.width / 2, desktopMode.height / 2, desktopMode.bitsPerPixel), "SFML part 5", sf::Style::Default, settings);*/
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Benoit", sf::Style::Default, this->settings);

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
}

void Game::renderingThread(sf::RenderWindow *window)
{

    if (this->music.openFromFile("../music/Supertask_Orchestra_version.ogg")) {
        std::cout << "Music: OK" << std::endl;
        this->music.play();
        this->music.setLoop(true);
    } else {
        std::cout << "Music: KO" << std::endl;
    }
    
    sf::Clock timer;
    if (!sf::Shader::isAvailable()) {
        std::cout << "Shader are not available" << std::endl;
    }


    // sf::Vector2<float> res = sf::Vector2<float>(1280, 720);
    // shader2.setUniform("resolution", res);
    // shader2.setUniform("currentTexture", sf::Shader::CurrentTexture);



    window->setActive(true);
    sf::View view(sf::Vector2f(300, 300), sf::Vector2f(1920, 1080));
    view.zoom(DEFAULT_ZOOM);
    window->setView(view);

    // Create a text

    std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>("hello", this->font);

    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    text->setFillColor(sf::Color::Blue);
    this->drawGUI_unique.emplace_back(std::move(text));


    this->FPS->setFont(this->font);
    this->FPS->setPosition(-650.0, -240.0);
    this->FPS->setColor(sf::Color::Red);
    this->FPS->setCharacterSize(30);
    this->drawGUI_shared.emplace_back(this->FPS);
    //
    //  LoadTectures
    //
    this->playerTexture.emplace_back(sf::Texture());
    if (!this->playerTexture[0].loadFromFile("../texture/PIPOYA FREE RPG Character Sprites 32x32/Female/Female 01-1.png")) {
        std::cout << "Texture not found !" << std::endl;
    }
    this->playerTexture[0].setSmooth(true);


    this->bossTexture.emplace_back(sf::Texture());
    if (!this->bossTexture[0].loadFromFile("../texture/rpg-pack/mobs/boss_bee.png")) {
        std::cout << "Texture not found !" << std::endl;
    }
    this->bossTexture[0].setSmooth(true);

    sf::Texture life0 = sf::Texture();
    if (!life0.loadFromFile("../texture/rpg-pack/props n decorations/generic-rpg-flower02.png")) {
        std::cout << "Texture not found !" << std::endl;
    }

    sf::Texture life1 = sf::Texture();
    if (!life1.loadFromFile("../texture/rpg-pack/props n decorations/generic-rpg-flower01.png")) {
        std::cout << "Texture not found !" << std::endl;
    }

    for(size_t x = 0; x < 10; x++)
    {
        std::unique_ptr<Entity> _life = std::make_unique<Entity>();
        _life->setPosition(-650.0 + (float)x * 45, -200.0);
        _life->setSize(sf::Vector2f(40, 35));
        _life->setTexture(&life0);
        this->drawGUI_shared.emplace_back(std::move(_life));
    }

    for(size_t x = 0; x < 10; x++)
    {
        std::unique_ptr<Entity> _life = std::make_unique<Entity>();
        _life->setPosition(-650.0 + (float)x * 45, -160.0);
        _life->setSize(sf::Vector2f(40, 35));
        _life->setTexture(&life1);
        this->drawGUI_shared.emplace_back(std::move(_life));
    }

    
    std::unique_ptr<Player> player = std::make_unique<Player>();
    player->setPosition(100.0, 100.0);
    player->setSize(sf::Vector2f(32, 32));
    player->setTexture(&this->playerTexture[0]);
    player->setTextureRect(sf::IntRect(0, 0, 32, 32));
    player->setMeleeAttack(1.0f);
    player->setOutlineThickness(1);
    player->setOutlineColor(sf::Color(255, 0, 0));
    this->drawPlayer.emplace_back(std::move(player));

    std::unique_ptr<Boss> enemy = std::make_unique<Boss>();

    enemy->setPosition(0.0, 0.0);
    enemy->setSize(sf::Vector2f(100, 100));
    enemy->setTexture(&this->bossTexture[0]);
    // enemy->setTextureRect(sf::IntRect(0, 0, 32, 32));
    enemy->setOutlineThickness(1);
    enemy->setOutlineColor(sf::Color(255, 0, 0));
    this->drawEntity.emplace_back(std::move(enemy));
    
    std::unique_ptr<Boss> enemy2 = std::make_unique<Boss>();
    enemy2->setPosition(10.3, 10.0);
    enemy2->setSize(sf::Vector2f(100, 100));
    enemy2->setTexture(&this->bossTexture[0]);
    // enemy->setTextureRect(sf::IntRect(0, 0, 32, 32));
    enemy2->setOutlineThickness(1);
    enemy2->setOutlineColor(sf::Color(255, 0, 0));
    this->drawEntity.emplace_back(std::move(enemy2));

    std::unique_ptr<Boss> enemy3 = std::make_unique<Boss>();
    enemy3->setPosition(20.3, 20.0);
    enemy3->setSize(sf::Vector2f(100, 100));
    enemy3->setTexture(&this->bossTexture[0]);
    // enemy->setTextureRect(sf::IntRect(0, 0, 32, 32));
    enemy3->setOutlineThickness(1);
    enemy3->setOutlineColor(sf::Color(255, 0, 0));
    this->drawEntity.emplace_back(std::move(enemy3));
    // enemy.release();
    
    std::unique_ptr<Entity> shape2 = std::make_unique<Entity>();

    shape2->setSize(sf::Vector2f(100, 100));
    shape2->setPosition(-10.0, -10.0);
    shape2->setFillColor(sf::Color(0, 255, 0));
    this->drawBlock.emplace_back(std::move(shape2));
    sf::View gui = window->getView();
    
    sf::Clock clock;
    sf::View playerOneView = window->getView();
    // the rendering loop
    while (window->isOpen()) {
        window->clear(DEFAULT_BACKGROUND);
#ifdef DNDEBUG
        if (this->music.getStatus() == sf::Music::Playing) {
            std::cout << "Music : Playing" << std::endl;
        }
#endif
        // FPS counter
        sf::Time frameTime = clock.restart();
        float framerate = 1 / (frameTime.asMilliseconds() * 0.001);
        this->speed = 120.0 / framerate;
#ifdef DNDEBUG
        std::cout << "FPS:" << framerate << std::endl;
#endif
        std::ostringstream ss;
        ss << framerate * 1.001 << " FPS";
        this->FPS->setString(ss.str());

        // Move boss
        for(size_t x = 0; x < this->drawEntity.size(); x++)
        {
            if (!this->drawPlayer[0]->getGlobalBounds().intersects(this->drawEntity[x]->getGlobalBounds())) {
                const auto &&diffx = this->drawEntity[x]->distanceX(this->drawPlayer[0]);
                const auto &&diffy = this->drawEntity[x]->distanceY(this->drawPlayer[0]);
                if (this->drawEntity[x]->getPosition().x + 35.0 > this->drawPlayer[0]->getPosition().x) {
                    this->drawEntity[x]->move(-1.0 * diffx * 0.015 * this->speed * (x + 1) * 0.6, 0.0);
                } else {
                    this->drawEntity[x]->move(1.0 * diffx * 0.015 * this->speed * (x + 1)  * 0.6, 0.0);
                }    // sf::RectangleShape rectangle(sf::Vector2f(50, 50));
                if (this->drawEntity[x]->getPosition().y + 35.0 > this->drawPlayer[0]->getPosition().y) {
                    this->drawEntity[x]->move(0.0, -1.0 * diffy * 0.015 * this->speed * (x + 1)  * 0.6);
                } else {
                    this->drawEntity[x]->move(0.0, 1.0 * diffy * 0.015 * this->speed * (x + 1)  * 0.6);
                }
            }
        }
        for (auto &elem : this->drawPlayer) {
            if (elem->getGlobalBounds().intersects(this->drawBlock[0]->getGlobalBounds())) {
#ifdef DNDEBUG
                std::cout << "Boom" << std::endl;
#endif
                auto ent = this->drawBlock[0].get();
                ent->setFillColor(sf::Color(255, 255, 255));
                ent->setSize(sf::Vector2f(100, 100));
                // ent->setRadius(40);
            } else {
                auto ent = this->drawBlock[0].get();
                ent->setFillColor(sf::Color(0, 255, 0));
                ent->setSize(sf::Vector2f(100, 100));
            }
        }

        while (window->pollEvent(this->event)) {
            if (this->event.type == sf::Event::Closed)
                window->close();
            if (this->event.type == sf::Event::Resized) {
                this->windowSizeX = sf::VideoMode::getDesktopMode().width;
                this->windowSizeY = sf::VideoMode::getDesktopMode().height;
                glViewport(0, 0, (int)this->event.size.width, (int)this->event.size.height);
            }

            if (this->event.type == sf::Event::LostFocus) {
#ifdef DNDEBUG
                std::cout << "LostFocus" << std::endl;
#endif
            }

            if (this->event.type == sf::Event::GainedFocus) {
#ifdef DNDEBUG
                std::cout << "wheel movement: " << this->event.mouseWheel.delta << std::endl;
#endif
            }
            if (this->event.type == sf::Event::MouseButtonPressed) {
                if (this->event.mouseButton.button == sf::Mouse::Right) {
#ifdef DNDEBUG
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << this->event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << this->event.mouseButton.y << std::endl;
#endif
                }
                if (this->event.mouseButton.button == sf::Mouse::Left) {
#ifdef DNDEBUG
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << this->event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << this->event.mouseButton.y << std::endl;
#endif
                }
            }
            if (this->event.type == sf::Event::MouseMoved) {
#ifdef DNDEBUG
                std::cout << "new mouse x: " << this->event.mouseMove.x << std::endl;
                std::cout << "nesf::Soundw mouse y: " << this->event.mouseMove.y << std::endl;
#endif
            }
            if (this->event.type == sf::Event::MouseEntered) {
#ifdef DNDEBUG
                std::cout << "the mouse cursor has entered the window" << std::endl;
#endif
            }

            if (this->event.type == sf::Event::MouseLeft) {
#ifdef DNDEBUG0
                std::cout << "the mouse cursor has left the window" << std::endl;
#endif
            }
            if (this->event.type == sf::Event::JoystickMoved) {
                if (this->event.joystickMove.axis == sf::Joystick::X) {
#ifdef DNDEBUG
                    std::cout << "X axis moved!" << std::endl;
                    std::cout << "joystick id: " << this->event.joystickMove.joystickId << std::endl;
                    std::cout << "new position: " << this->event.joystickMove.position << std::endl;
#endif
                }
            }
            if (this->event.joystickMove.axis == sf::Joystick::X || this->event.joystickMove.axis == sf::Joystick::Y) {
                const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                this->drawPlayer[0]->move((x / 12.0) * this->speed / 1.25, (y / 12.0) * this->speed / 1.25);
                playerOneView.move((x / 12.0) * this->speed / 1.25, (y / 12.0) * this->speed / 1.25);
            }
            if (this->event.type == sf::Event::JoystickButtonPressed) {
#ifdef DNDEBUG
                std::cout << "joystick button pressed!" << std::endl;
                std::cout << "joystick id: " << this->event.joystickButton.joystickId << std::endl;
                std::cout << "button: " << this->event.joystickButton.button << std::endl;
#endif
            }
        }
        for (size_t i = 0; i < this->drawPlayer.size(); i++) {
            if (sf::Joystick::isConnected(i)) {
                const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

                this->drawPlayer[i]->move((x / 12.0), (y / 12.0));
                playerOneView.move(x / 12.0, y / 12.0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            Screen_save_gl::saveScreenshotToFile("../screenshot/screenshot_" + my::date::get_date() + ".png", window->getSize().x, window->getSize().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
            playerOneView.zoom(DEFAULT_ZOOM);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) {
            playerOneView.rotate(5);
        }
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
#ifdef DNDEBUG
                std::cout << "Left" << std::endl;
#endif
                this->drawPlayer[0]->move(-7.0 * this->speed, 0.0);
                this->drawPlayer[0]->setTexture(&this->playerTexture[0]);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 32, 32, 32));
                playerOneView.move(-7.0 * this->speed, 0.0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
#ifdef DNDEBUG
                std::cout << "Right " << std::endl;
#endif
                this->drawPlayer[0]->move(7.0 * this->speed, 0.0);
                this->drawPlayer[0]->setTexture(&this->playerTexture[0]);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 64, 32, 32));
                playerOneView.move(7.0 * this->speed, 0.0);
            }
        }
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
#ifdef DNDEBUG
                std::cout << "Up" << std::endl;
#endif
                this->drawPlayer[0]->move(0.0, -7.0 * this->speed);
                this->drawPlayer[0]->setTexture(&this->playerTexture[0]);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 96, 32, 32));
                playerOneView.move(0.0, -7.0 * this->speed);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
#ifdef DNDEBUG
                std::cout << "Down" << std::endl;
#endif
                this->drawPlayer[0]->move(0.0, 7.0 * this->speed);
                this->drawPlayer[0]->setTexture(&this->playerTexture[0]);
                this->drawPlayer[0]->setTextureRect(sf::IntRect(0, 0, 32, 32));
                playerOneView.move(0.0, 7.0 * this->speed);
            }
        }

        // Set view
        //playerOneView.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
        playerOneView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        window->setView(playerOneView);
        // Draw all Entities/Items ect...
        for (auto &elem : this->drawTitle)
            window->draw(*elem, &this->shader);
        for (auto &elem : this->drawBlock)
            window->draw(*elem);
        for (auto &elem : this->drawEntity)
            window->draw(*elem);
        for (auto &elem : this->drawPlayer)
            window->draw(*elem);
        
        auto minimap = playerOneView;
        minimap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
        window->setView(minimap);
        for (auto &elem : this->drawTitle)
            window->draw(*elem, &this->shader);
        for (auto &elem : this->drawBlock)
            window->draw(*elem);
        for (auto &elem : this->drawEntity)
            window->draw(*elem);
        for (auto &elem : this->drawPlayer)
            window->draw(*elem);
        /*
        playerOneView.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
        window->setView(playerOneView);
                for (auto &elem : this->drawTitle)
        window->draw(*elem, &this->shader);*/
        // Gui
        window->setView(gui);
        for (auto &elem : this->drawGUI_unique)
            window->draw(*elem);
        for (auto &elem : this->drawGUI_shared)
            window->draw(*elem);        
        // this->screen_save.add_frame(window);
        //
        // window->pushGLStates();
        // window->resetGLStates();
        this->shader.setUniform("time", timer.getElapsedTime().asSeconds());
        // shader2.setUniform("time", timer.getElapsedTime().asSeconds());
        this->shader.setUniform("distortionFactor", this->distortionFactor);
        this->shader.setUniform("riseFactor", this->riseFactor);
        window->display();
        // window->popGLStates();
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
