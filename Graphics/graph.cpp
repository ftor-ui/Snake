#include "graph.h"
#include <cstring>

Window::Window(int const WIDTH, int const HEIGHT, char const *title)
{
	renderWindow.create(sf::VideoMode(WIDTH, HEIGHT), title);
	renderWindow.setFramerateLimit(60);
}

Window::~Window()
{}

bool Window::isOpen()
{
	return renderWindow.isOpen();
}

void Window::render()
{
	sf::Event event;
	while (renderWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			renderWindow.close();
	}
	renderWindow.display();
}

void printSquare(Window &window, int x, int y, int const SIZE, char const *color)
{
	sf::ConvexShape square;
	square.setPointCount(4);
	square.setPoint(0, sf::Vector2f(x, y));
	square.setPoint(1, sf::Vector2f(x+SIZE, y));
	square.setPoint(2, sf::Vector2f(x+SIZE, y+SIZE));
	square.setPoint(3, sf::Vector2f(x, y+SIZE));

	if (!strcmp(color, "border"))
		square.setFillColor(sf::Color(49, 29, 63));
	else if (!strcmp(color, "empty"))
		square.setFillColor(sf::Color(136, 48, 78));
	else if (!strcmp(color, "head"))
		square.setFillColor(sf::Color(226, 62, 87));
	else if (!strcmp(color, "tail"))
		square.setFillColor(sf::Color(82, 37, 70));
    else if (!strcmp(color, "food"))
        square.setFillColor(sf::Color(44, 123, 74));
    window.renderWindow.draw(square);
}
