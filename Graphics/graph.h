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

	sf::RenderWindow renderWindow;
private:
	Window(Window const &);
	Window & operator=(Window const &);
};

void printSquare(Window &, int, int, int const, char const *);

#endif
