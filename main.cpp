#include "Graphics/graph.h"
#include <cstdlib>
#include <ctime>

// Resolution of window
int const WIDTH = 800;
int const HEIGHT = 600;

// Size of square
int const SIZE = 20;

// Game params
sf::Time speed = sf::milliseconds(90);
bool GameOver;

// Param of snake
int x;
int y;
int countTail;
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
int foodX;
int foodY;

void init();
void render(Window &);
void controller();
void logic();

int main()
{
    init();
	Window window(WIDTH, HEIGHT, "Snake");
	while (window.isOpen())
	{
	    render(window);
	    controller();
		if (!GameOver)
            logic();
		window.render();
		sf::sleep(speed);
	}
	return 0;
}

void init()
{
    srand(time(NULL));
    GameOver = false;

    // Param of snake
    x = ((WIDTH / 2) / SIZE) * SIZE;
    y = ((HEIGHT / 2) / SIZE) * SIZE;
    countTail = 0;
    state = STOP;

    // Param of food
    foodX = SIZE + rand()%((WIDTH-2*SIZE)/SIZE) * SIZE;
    foodY = SIZE + rand()%((HEIGHT-2*SIZE)/SIZE) * SIZE;
}

void render(Window &window)
{
    window.renderWindow.clear();
	for (int idy = 0; idy < HEIGHT; idy+=SIZE)
		{
			for (int idx = 0; idx < WIDTH; idx+=SIZE)
			{
				if ((idx == 0 || idx >= (WIDTH - SIZE) / SIZE * SIZE) ||
				    (idy == 0 || idy >= (HEIGHT - SIZE) / SIZE * SIZE))
					printSquare(window, idx, idy, SIZE, "border");
				else if (idx == x && idy == y)
					printSquare(window, idx, idy, SIZE, "head");
				else if (idx == foodX && idy == foodY)
					printSquare(window, idx, idy, SIZE, "food");
				else
				{
					bool isTail = false;
					for (int idt = 0; idt < countTail; idt++)
						if (prevX[idt] == idx && prevY[idt] == idy)
						{
							printSquare(window, idx, idy, SIZE, "tail");
							isTail = true;
						}
					if (isTail == false)
						printSquare(window, idx, idy, SIZE, "empty");
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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        init();
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

	// Control position of snake
	if (x == 0)
        x = (WIDTH - 2*SIZE) / SIZE * SIZE;
    else if (x >= (WIDTH - SIZE) / SIZE * SIZE)
        x = SIZE;
    if (y == 0)
        y = (HEIGHT - 2*SIZE) / SIZE * SIZE;
    else if (y >= (HEIGHT - SIZE) / SIZE * SIZE)
        y = SIZE;

	// Check the GameOver
	for (int idt = 0; idt < countTail; idt++)
		if (prevX[idt] == x && prevY[idt] == y)
		{
			GameOver = true;
			break;
		}
	if (GameOver)
		state = STOP;
}
