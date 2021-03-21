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

	if (!strcmp(color, "black"))
		square.setFillColor(sf::Color(0, 0, 0));
	else if (!strcmp(color, "white"))
		square.setFillColor(sf::Color(255, 255, 255));
	else if (!strcmp(color, "red"))
		square.setFillColor(sf::Color(200, 0, 0));
	else if (!strcmp(color, "green"))
		square.setFillColor(sf::Color(0, 220, 0));
    window.renderWindow.draw(square);
}
