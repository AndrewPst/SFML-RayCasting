#include <SFML/Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include "Settings.h"
#include "GameEngine.h"

using namespace sf;

int main()
{
#pragma region Initialization

	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(VideoMode(D_WIDTH, D_HEIGHT), "", Style::Default, settings);

	GameEngine game(window);

	game.initializate();


#pragma endregion
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}

		window.clear(Color::Black);
		game.tick();		// Отрисовка окна	
		window.display();
	}
	return 0;
}