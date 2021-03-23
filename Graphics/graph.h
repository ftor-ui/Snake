#ifndef _GRAPH_H
#define _GRAPH_H

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window(int const, int const, char const *);
	~Window();
	bool isOpen();
	void render();
	bool setFont(char const *);

	sf::RenderWindow renderWindow;
	sf::Font font;
private:
	Window(Window const &);
	Window & operator=(Window const &);
};

void printSquare(Window &, int, int, int const, char const *);

void printBorder(Window &, int, int, int const);

void printString(Window &, int, int, int, char const *);

sf::ConvexShape printButton(Window &, int, int, int, int, char const *);

#endif
