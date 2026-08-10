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

    sf::VideoMode vm({resolution.x, resolution.y});

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
                switch (keyReleased->code)
                {
                case sf::Keyboard::Key::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Key::Enter:
                {
                    if (state == State::PLAYING)
                    {
                        state = State::PAUSED;
                    }
                    else if (state == State::PAUSED)
                    {
                        state = State::PLAYING;
                        clock.restart();
                    }
                    else if (state == State::GAME_OVER)
                    {
                        state = State::LEVELING_UP;
                    }
                    break;
                default:
                    break;
                }

                    if (state == State::PLAYING)
                    {
                        switch (keyReleased->code)
                        {
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
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}