/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** Virus.cpp
*/

#include "virus.hpp"

Virus::Virus()
{
}

void Virus::Launch()
{

    // this->sound.setBuffer(buffer);
    // this->sound.play();
    // this->sound.setLoop(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

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
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Benoit", sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);
    glEnable(GL_TEXTURE_2D);

    // window.setFramerateLimit(5);

    window.setActive(false);
    // window.setJoystickThreshold(100.0f);

    std::thread display_thread(&Virus::renderingThread, this, &window);
    display_thread.join();
}

Virus::~Virus()
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
    for (auto &&elem : this->drawGUI) {
        delete elem;
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

void Virus::renderingThread(sf::RenderWindow *window)
{
    sf::Clock timer;

    window->setActive(true);
    sf::View view1(sf::Vector2f(0, 0), sf::Vector2f(1920, 1080));
    view1.zoom(DEFAULT_ZOOM);
    window->setView(view1);

    sf::Font font;
    font.loadFromFile("../font/Almond_Caramel.ttf");
    // Create a text

#if __cplusplus <= 201402L
    sf::Text *text = new sf::Text("hello", font);
#elif __cplusplus >= 201703L
    std::unique_ptr<sf::Text> text = std::make_unique<sf::Text>("hello", font);
#else
#endif

    text->setCharacterSize(30);
    text->setStyle(sf::Text::Bold | sf::Text::Underlined);
    text->setFillColor(sf::Color::Blue);
#if __cplusplus <= 201402L
    this->drawGUI.emplace_back(text);
#elif __cplusplus >= 201703L
    this->drawGUI.emplace_back(std::move(text));
#else
#endif
    this->FPS.setFont(font);
    this->FPS.setPosition(-600.0, -400.0);
    this->FPS.setColor(sf::Color::Red);
    this->FPS.setCharacterSize(30);

    std::uniform_real_distribution<double> dist(-300.0, 300.0);
    std::uniform_real_distribution<double> distm(-5.0, 5.0);
    std::uniform_real_distribution<double> distb(0, 1000.0);

    std::mt19937 rng;
    rng.seed(std::random_device {}());

    for (size_t i = 0; i < 5000; i++) {
#if __cplusplus <= 201402L
        People *people = new People();
#elif __cplusplus >= 201703L
        std::unique_ptr<People> people = std::make_unique<People>();
#else
#endif
        people->setPosition(dist(rng), dist(rng));
        if(distb(rng) > 999.0) {
            people->is_contaminated = true;
            people->setFillColor(sf::Color(255, 0, 0));
            
        } else {
            people->setFillColor(sf::Color(0, 250, 0));
        }
        people->setSize(sf::Vector2f(10, 10));
        // sf::RectangleShape rectangle(sf::Vector2f(50, 50));
        // people->setTexture(&texture2);
        // people->setTextureRect(sf::IntRect(0, 0, 32, 32));

        //people->setOutlineThickness(1);
        //people->setOutlineColor(sf::Color(255, 0, 0));
#if __cplusplus <= 201402L
        this->drawSprite.emplace_back(people);
#elif __cplusplus >= 201703L
        this->drawSprite.emplace_back(std::move(people));
#else
#endif
    }
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
        ss << framerate * 1.001 << " FPS";
        this->FPS.setString(ss.str());
        
        for (auto &elemx : this->drawSprite) {
            for (auto &elemy : this->drawSprite) {
                if (elemx != elemy) {
                    if (elemx->getGlobalBounds().intersects(elemy->getGlobalBounds())) {
                        elemy->move(distm(rng), distm(rng));
                        if (elemy->is_contaminated == true || elemx->is_contaminated == true)
                        {
                            if(distb(rng) < 900.0) {
                                elemy->is_contaminated = true;
                                elemx->is_contaminated = true;
                                elemx->setFillColor(sf::Color(255, 0, 0));
                                elemy->setFillColor(sf::Color(255, 0, 0));
                            }
                        }
                    } else {
                        elemy->move(distm(rng)/5.0, distm(rng)/5.0);
                    }
                }
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
                    standard.move((x / 12.0) * this->speed / 1.25, (y / 12.0) * this->speed / 1.25);
                }
                if (event.type == sf::Event::JoystickButtonPressed) {
#ifdef DNDEBUG
                    std::cout << "joystick button pressed!" << std::endl;
                    std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
                    std::cout << "button: " << event.joystickButton.button << std::endl;
#endif
                }
            }
            for (size_t i = 0; i < this->drawPlayer.size(); i++) {
                if (sf::Joystick::isConnected(i)) {
                    const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                    const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

                    this->drawPlayer[i]->move((x / 12.0), (y / 12.0));
                    standard.move(x / 12.0, y / 12.0);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
                //Screen_save_gl::saveScreenshotToFile("../screenshot/screenshot_" + my::date::get_date() + ".png", window->getSize().x, window->getSize().y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) {
                standard.zoom(DEFAULT_ZOOM);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) {
                // sf::View view3(sf::Vector2f(300, 300), sf::Vector2f(1920, 1080));
                // sf::View view3(window->getView().getCenter(), sf::Vector2f(1280, 720));
                standard.rotate(5);
            }
            if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
#ifdef DNDEBUG
                    std::cout << "Left" << std::endl;
#endif
                    // riseFactor *= 2.f;
                    standard.move(-7.0 * this->speed, 0.0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
#ifdef DNDEBUG
                    std::cout << "Right " << std::endl;
#endif
                    // riseFactor /= 2.f;
                    standard.move(7.0 * this->speed, 0.0);
                }
            }
            if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
#ifdef DNDEBUG
                    std::cout << "Up" << std::endl;
#endif
                    // distortionFactor *= 2.f;
                    standard.move(0.0, -7.0 * this->speed);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
#ifdef DNDEBUG
                    std::cout << "Down" << std::endl;
#endif
                    // distortionFactor /= 2.f;
                    standard.move(0.0, 7.0 * this->speed);
                }
            }
            // Set view
            window->setView(standard);
            // Draw all Entities/Items ect...
            for (auto &elem : this->drawTitle)
                window->draw(*elem);
            for (auto &elem : this->drawBlock)
                window->draw(*elem);
            for (auto &elem : this->drawSprite)
                window->draw(*elem);
            for (auto &elem : this->drawPlayer)
                window->draw(*elem);
            // Gui
            window->setView(gui);
            for (auto &elem : this->drawGUI)
                window->draw(*elem);
            window->draw(this->FPS);
            window->setView(standard);
            // this->screen_save.add_frame(window);
            //
            // window->pushGLStates();
            // window->resetGLStates();
            window->display();
            // window->popGLStates();
            // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
    }
