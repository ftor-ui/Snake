#include "Graphics/graph.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

// Resolution of Window
int const WWIDTH = 800;
int const WHEIGHT = 600;

// Resolution of game-field
int const WIDTH = WWIDTH - WWIDTH / 3 + WWIDTH / 10;
int const HEIGHT = WHEIGHT;

// Size of square
int const SIZE = HEIGHT / 30;

// Game params
sf::Time speed = sf::milliseconds(90);
bool GameOver;
int score;
char bScore[128];
int bestScore;
char bBestScore[128];

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
void menu(Window &);
void bestScoreUpdate();
void render(Window &);
void controller(Window &);
void logic();

int main()
{
    init();
	Window window(WWIDTH, WHEIGHT, "Snake");
	window.setFont("C:\\Windows\\Fonts\\Arial.ttf");
	menu(window);
	while (window.isOpen())
	{
	    render(window);
	    controller(window);
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
    score = 0;
    sprintf(bScore, "Score: %d", 0);
    FILE *data = fopen("data.dat", "a");
    fclose(data);
    data = fopen("data.dat", "r");
    fscanf(data, "%d", &bestScore);
    fclose(data);
    snprintf(bBestScore, sizeof(bBestScore), "Best: %d", bestScore);

    // Param of snake
    x = ((WIDTH / 2) / SIZE) * SIZE;
    y = ((HEIGHT / 2) / SIZE) * SIZE;
    countTail = 0;
    state = STOP;

    // Param of food
    foodX = SIZE + rand()%((WIDTH-2*SIZE)/SIZE) * SIZE;
    foodY = SIZE + rand()%((HEIGHT-2*SIZE)/SIZE) * SIZE;
}

void menu(Window &window)
{
    while (window.isOpen())
    {
        window.renderWindow.clear(sf::Color(136, 48, 78));
        sf::ConvexShape handleButton1 = printButton(window, WWIDTH/2 - 50, WHEIGHT/2-45, 100, 30, "New Game");
        sf::ConvexShape handleButton2 = printButton(window, WWIDTH/2 - 50, WHEIGHT/2+5, 100, 30, "Quit");
        printBorder(window, WWIDTH, WHEIGHT, SIZE);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (handleButton1.getGlobalBounds().contains(sf::Mouse::getPosition(window.renderWindow).x, sf::Mouse::getPosition(window.renderWindow).y))
                break;
            else if (handleButton2.getGlobalBounds().contains(sf::Mouse::getPosition(window.renderWindow).x, sf::Mouse::getPosition(window.renderWindow).y))
            {
                window.renderWindow.close();
                break;
            }

        }
        window.render();
    }
}

void bestScoreUpdate()
{
    bestScore = score > bestScore ? score : bestScore;
    FILE *data = fopen("data.dat", "w");
    fprintf(data, "%d", bestScore);
    fclose(data);
}

void render(Window &window)
{
    window.renderWindow.clear(sf::Color(136, 48, 78));
	for (int idt = 0; idt < countTail; idt++)
        printSquare(window, prevX[idt], prevY[idt], SIZE, "tail");
    printSquare(window, foodX, foodY, SIZE, "food");
    printSquare(window, x, y, SIZE, "head");
    printBorder(window, WIDTH, HEIGHT, SIZE);
    printString(window, WIDTH + SIZE / 2, SIZE / 2, 2*SIZE - SIZE / 2, bScore); // Score
    printString(window, WIDTH + SIZE / 2, 2*SIZE, 2*SIZE - SIZE / 2, bBestScore);
    printString(window, WIDTH + SIZE / 2, 4*SIZE, 2*SIZE - SIZE / 2, "R - restart");
    printString(window, WIDTH + SIZE / 2, 5*SIZE + SIZE, SIZE, "B.space - reset");
}

void controller(Window &window)
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
    {
        bestScoreUpdate();
        init();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
    {
        FILE *data = fopen("data.dat", "w");
		fprintf(data, "%d", 0);
		fclose(data);
		bestScore = 0;
		sprintf(bBestScore, "Best: %d", bestScore);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        menu(window);
        bestScoreUpdate();
        init();
    }
}

void logic()
{
	// Collision with food
	if (x == foodX && y == foodY)
	{
		countTail++;
		score+=10;
		snprintf(bScore, sizeof(bScore), "Score: %d", score);
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
    {
		state = STOP;
		bestScoreUpdate();
    }
}
