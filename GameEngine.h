#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Settings.h"
#include "FPS.h"
#include "Player.h"
#include "Map.h"

class GameEngine
{
private:
	sf::RenderWindow& _window;
	FPS _fps;

	Player_ player;
	Map _map;

	typedef struct RayCastParameters_t
	{
		double startCoord = 0, rayDepth = 0, otherCoord = 0;
		int koef = 0;
		MapToken_t mapToken;
	};

private:

	void checkKeys();
	void draw();
	void drawSkyAndFloor();
public:
	explicit GameEngine(sf::RenderWindow& window);
	void initializate();
	void tick();
};

