#include <SFML/Graphics.hpp>

int main()
{
	sf::VideoMode vm({ 1920, 1080 });

	sf::RenderWindow window(vm, "Zombie Shooter", sf::State::Fullscreen);

	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			else if (auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				switch (keyReleased->code)
				{
				case sf::Keyboard::Key::Escape:
					window.close();
					break;
				}
			}
		}

		window.clear(sf::Color::Black);

		window.display();
	}

	return 0;
}