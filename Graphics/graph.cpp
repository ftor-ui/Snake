#include "graph.h"
#include <cstring>
#include <iostream>

Window::Window(int const WIDTH, int const HEIGHT, char const *title)
{
	renderWindow.create(sf::VideoMode(WIDTH, HEIGHT), title, sf::Style::Close);
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

bool Window::setFont(char const *path)
{
    return font.loadFromFile(path);
}

void printSquare(Window &window, int x, int y, int const SIZE, char const *color)
{
	sf::ConvexShape square;
	square.setPointCount(4);
	square.setPoint(0, sf::Vector2f(x, y));
	square.setPoint(1, sf::Vector2f(x+SIZE, y));
	square.setPoint(2, sf::Vector2f(x+SIZE, y+SIZE));
	square.setPoint(3, sf::Vector2f(x, y+SIZE));

	if (!strcmp(color, "head"))
		square.setFillColor(sf::Color(226, 62, 87));
	else if (!strcmp(color, "tail"))
		square.setFillColor(sf::Color(82, 37, 70));
    else if (!strcmp(color, "food"))
        square.setFillColor(sf::Color(44, 123, 74));
    window.renderWindow.draw(square);
}

void printBorder(Window &window, int WIDTH, int HEIGHT, int SIZE)
{
    // Top border
    sf::ConvexShape top;
	top.setPointCount(4);
	top.setPoint(0, sf::Vector2f(0, 0));
	top.setPoint(1, sf::Vector2f(WIDTH, 0));
	top.setPoint(2, sf::Vector2f(WIDTH, SIZE));
	top.setPoint(3, sf::Vector2f(0, SIZE));

	// Left border
	sf::ConvexShape left;
	left.setPointCount(4);
	left.setPoint(0, sf::Vector2f(0, SIZE));
	left.setPoint(1, sf::Vector2f(0, HEIGHT));
	left.setPoint(2, sf::Vector2f(SIZE, HEIGHT));
	left.setPoint(3, sf::Vector2f(SIZE, 0));

	// Right border
	sf::ConvexShape right;
	right.setPointCount(4);
	right.setPoint(0, sf::Vector2f((WIDTH - SIZE) / SIZE * SIZE, SIZE));
	right.setPoint(1, sf::Vector2f((WIDTH - SIZE) / SIZE * SIZE, HEIGHT));
	right.setPoint(2, sf::Vector2f(WIDTH, HEIGHT));
	right.setPoint(3, sf::Vector2f(WIDTH, SIZE));

	// Bottom border
	sf::ConvexShape bottom;
	bottom.setPointCount(4);
	bottom.setPoint(0, sf::Vector2f(SIZE, (HEIGHT - SIZE) / SIZE * SIZE));
	bottom.setPoint(1, sf::Vector2f((WIDTH - SIZE) / SIZE * SIZE, (HEIGHT - SIZE) / SIZE * SIZE));
	bottom.setPoint(2, sf::Vector2f((WIDTH - SIZE) / SIZE * SIZE, HEIGHT));
	bottom.setPoint(3, sf::Vector2f(SIZE, HEIGHT));

	// Setting color
	top.setFillColor(sf::Color(49, 29, 63));
	left.setFillColor(sf::Color(49, 29, 63));
	right.setFillColor(sf::Color(49, 29, 63));
	bottom.setFillColor(sf::Color(49, 29, 63));

	// Draw
	window.renderWindow.draw(top);
	window.renderWindow.draw(left);
	window.renderWindow.draw(right);
	window.renderWindow.draw(bottom);
}

void printString(Window &window, int x, int y, int SIZE, char const *str)
{
    sf::Text text;
    text.setFont(window.font);
    text.setString(str);
    text.setCharacterSize(SIZE);
    text.setStyle(sf::Text::Italic);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(sf::Color(230, 230, 230));
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color(70, 70, 70));

    window.renderWindow.draw(text);
}

sf::ConvexShape printButton(Window &window, int x, int y, int width, int height, char const *str)
{
    // Create button
    sf::ConvexShape button;
    button.setPointCount(4);
    button.setPoint(0, sf::Vector2f(x, y));
    button.setPoint(1, sf::Vector2f(x+width, y));
    button.setPoint(2, sf::Vector2f(x+width, y+height));
    button.setPoint(3, sf::Vector2f(x, y+height));
    button.setFillColor(sf::Color(255, 255, 255));
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color(0, 0, 0));

    // Print text
    sf::Text text;
    text.setFont(window.font);
    text.setString(str);
    text.setCharacterSize(height/2);
    text.setStyle(sf::Text::Italic);
    text.setPosition(sf::Vector2f(x+width/8, y+height/4));
    text.setFillColor(sf::Color(230, 230, 230));
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color(70, 70, 70));

    // Draw
    window.renderWindow.draw(button);
    window.renderWindow.draw(text);

    return button;
}
