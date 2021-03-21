#include "Graphics/graph.h"
#include <cstdlib>
#include <ctime>

// Resolution of window
int const WIDTH = 800;
int const HEIGHT = 600;

// Size of square
int const SIZE = 20;

// Game params
sf::Time speed = sf::milliseconds(60);
bool GameOver = false;

// Param of snake
int x = ((WIDTH / 2) / SIZE) * SIZE;
int y = ((HEIGHT / 2) / SIZE) * SIZE;
int countTail = 0;
int prevX[(WIDTH-2*SIZE)*(HEIGHT-2*SIZE) - SIZE];
int prevY[(WIDTH-2*SIZE)*(HEIGHT-2*SIZE) - SIZE];
enum states {
	STOP = 0,
	RIGHT,
	LEFT,
	UP,
	DOWN
} state;

// Param of food
int foodX = SIZE + rand()%((WIDTH-2*SIZE)/SIZE) * SIZE;
int foodY = SIZE + rand()%((HEIGHT-2*SIZE)/SIZE) * SIZE;


void render(Window &);
void controller();
void logic();

int main()
{
    srand(time(NULL));
	Window window(WIDTH, HEIGHT, "Snake");
	while (window.isOpen())
	{
	    render(window);
		if (!GameOver)
        {
            controller();
            logic();
        }
        sf::sleep(speed);
		window.render();
	}
	return 0;
}

void render(Window &window)
{
    window.renderWindow.clear();
	for (int idy = 0; idy < HEIGHT; idy+=SIZE)
		{
			for (int idx = 0; idx < WIDTH; idx+=SIZE)
			{
				if ((idx == 0 || idx == WIDTH - SIZE) ||
				    (idy == 0 || idy == HEIGHT - SIZE))
					printSquare(window, idx, idy, SIZE, "black");
				else if (idx == x && idy == y)
					printSquare(window, idx, idy, SIZE, "red");
				else if (idx == foodX && idy == foodY)
					printSquare(window, idx, idy, SIZE, "red");
				else
				{
					bool isTail = false;
					for (int idt = 0; idt < countTail; idt++)
						if (prevX[idt] == idx && prevY[idt] == idy)
						{
							printSquare(window, idx, idy, SIZE, "green");
							isTail = true;
						}
					if (isTail == false)
						printSquare(window, idx, idy, SIZE, "white");
				}
			}
		}
}

void controller()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (state != DOWN)
            state = UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (state != RIGHT)
            state = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (state != UP)
            state = DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (state != LEFT)
            state = RIGHT;
    }
}

void logic()
{
	// Collision with food
	if (x == foodX && y == foodY)
	{
		countTail++;
		foodX = SIZE + rand()%((WIDTH-2*SIZE)/SIZE) * SIZE;
		foodY = SIZE + rand()%((HEIGHT-2*SIZE)/SIZE) * SIZE;
	}

	// Control tail
	if (countTail != 0)
	{
		if (countTail > 1)
			for (int idt = countTail-1; idt > 0; idt--)
			{
				prevX[idt] = prevX[idt-1];
				prevY[idt] = prevY[idt-1];
			}
		prevX[0] = x;
		prevY[0] = y;
	}

	// Control vector player
	switch(state)
	{
	case STOP:
		break;
	case RIGHT:
		x+=SIZE;
		break;
	case LEFT:
		x-=SIZE;
		break;
	case UP:
		y-=SIZE;
		break;
	case DOWN:
		y+=SIZE;
		break;
	}

	// Check the GameOver
	if (x == 0 || x == WIDTH - SIZE || \
		y == 0 || y == HEIGHT - SIZE)
		GameOver = true;
	for (int idt = 0; idt < countTail; idt++)
		if (prevX[idt] == x && prevY[idt] == y)
		{
			GameOver = true;
			break;
		}
	if (GameOver)
		state = STOP;
}
