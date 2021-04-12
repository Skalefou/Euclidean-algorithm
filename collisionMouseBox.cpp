#include <SFML/Graphics.hpp>

bool collisionShape(sf::RenderWindow &window, sf::IntRect rect) 
{
	sf::Vector2i CoordsMouse(sf::Mouse::getPosition(window));
	if ((CoordsMouse.x >= rect.left)
		&& (CoordsMouse.x <= rect.left + rect.width)
		&& (CoordsMouse.y >= rect.top)
		&& (CoordsMouse.y <= rect.top + rect.height))
		return true;
	return false;
}

int main(void) 
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Collision Mouse Box");
	sf::IntRect rect(((512 / 2) - 50), ((512 / 2) - 50), 100, 100);
	sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));

	rectangle.setPosition(sf::Vector2f(((512 / 2) - 50), (512 / 2) - 50));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (collisionShape(window, rect))
			rectangle.setFillColor(sf::Color::Green);
		else
			rectangle.setFillColor(sf::Color::Red);

		window.draw(rectangle);
		window.display();
	}
	return 0;
}