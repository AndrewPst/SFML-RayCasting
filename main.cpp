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
	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}

		window.clear(Color::Black);
		game.tick();		// ��������� ����	
		window.display();
	}
	return 0;
}