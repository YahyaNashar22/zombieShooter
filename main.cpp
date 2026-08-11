#include "Player.hpp"
#include <SFML/Graphics.hpp>

int main()
{
#pragma region
    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    // Start game with GAME_OVER state
    State state = State::GAME_OVER;

    sf::Vector2f resolution;

    resolution.x = sf::VideoMode::getDesktopMode().size.x;
    resolution.y = sf::VideoMode::getDesktopMode().size.y;

    sf::VideoMode vm({static_cast<unsigned>(resolution.x),
                      static_cast<unsigned>(resolution.y)});

    sf::RenderWindow window(vm, "Zombie Shooter", sf::State::Fullscreen);

    // Create an SFML view for the main action
    sf::View mainView(sf::FloatRect({0, 0}, {resolution.x, resolution.y}));

    // game clock
    sf::Clock clock;

    // how long has the PLAYING state been active
    sf::Time gameTimeTotal;

    // mousePosition in relation to world coordinates
    sf::Vector2f mouseWoldPosition;

    // mousePosition in relation to screen coordinate
    sf::Vector2i mouseScreenPosition;

    // create an instance of Player class
    Player player;

    // the boundaries of the arena
    sf::IntRect arena;

#pragma endregion

    // main game loop
    while (window.isOpen())
    {
        while (std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            else if (auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (state == State::PLAYING)
                {
                    switch (keyPressed->code)
                    {
                    case sf::Keyboard::Key::W:
                        player.moveUp();
                        break;

                    case sf::Keyboard::Key::S:
                        player.moveDown();
                        break;

                    case sf::Keyboard::Key::D:
                        player.moveRight();
                        break;

                    case sf::Keyboard::Key::A:
                        player.moveLeft();
                        break;

                    default:
                        break;
                    }
                }
            }

            else if (auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                // any state //////////////////////////////////
                if (keyReleased->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }

                // GAME_OVER State //////////////////////////////
                if (state == State::GAME_OVER)
                {
                    switch (keyReleased->code)
                    {
                    case sf::Keyboard::Key::Enter:
                        state = State::LEVELING_UP;
                        break;
                    }
                }

                // PAUSED State //////////////////////////////////
                if (state == State::PAUSED)
                {
                    switch (keyReleased->code)
                    {
                    case sf::Keyboard::Key::Enter:
                        state = State::PLAYING;
                        clock.restart();
                        break;
                    }
                }

                // PLAYING State //////////////////////////////////////
                // movement controls
                if (state == State::PLAYING)
                {
                    switch (keyReleased->code)
                    {
                    case sf::Keyboard::Key::Enter:
                        state == State::PAUSED;
                        break;

                    case sf::Keyboard::Key::W:
                        player.stopUp();
                        break;

                    case sf::Keyboard::Key::S:
                        player.stopDown();
                        break;

                    case sf::Keyboard::Key::D:
                        player.stopRight();
                        break;

                    case sf::Keyboard::Key::A:
                        player.stopLeft();
                        break;

                    default:
                        break;
                    }

                    // prepare the level
                    arena.size.x     = 500;
                    arena.size.y     = 500;
                    arena.position.x = 0;
                    arena.position.y = 0;

                    int tileSize = 50;
                    player.spawn(arena, resolution, tileSize);

                    // reset clock so there isn't a frame jump
                    clock.restart();
                }

                // LEVELING_UP State ////////////////////////////
                // leveling up controls
                if (state == State::LEVELING_UP)
                {
                    switch (keyReleased->code)
                    {
                    case sf::Keyboard::Key::Num1:
                        state = State::PLAYING;
                        break;
                    case sf::Keyboard::Key::Num2:
                        state = State::PLAYING;
                        break;
                    case sf::Keyboard::Key::Num3:
                        state = State::PLAYING;
                        break;
                    case sf::Keyboard::Key::Num4:
                        state = State::PLAYING;
                        break;
                    case sf::Keyboard::Key::Num5:
                        state = State::PLAYING;
                        break;
                    case sf::Keyboard::Key::Num6:
                        state = State::PLAYING;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        if (state == State::PLAYING)
        {
            // update delta time
            sf::Time dt = clock.restart();

            // update total game time
            gameTimeTotal += dt;

            // make a fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            // where is the mouse pointer
            mouseScreenPosition = sf::Mouse::getPosition();

            // convert mouse position to world based on coordinates of mainView
            mouseWoldPosition =
                window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

            // update the player
            player.update(dtAsSeconds, sf::Mouse::getPosition());

            // make a note of the players new position
            sf::Vector2f playerPosition(player.getCenter());

            mainView.setCenter(player.getCenter());

            window.clear(sf::Color::Black);

            window.setView(mainView);

            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP)
        {
        };

        if (state == State::PAUSED)
        {
        };

        if (state == State::GAME_OVER)
        {
        };

        window.display();
    }

    return 0;
}