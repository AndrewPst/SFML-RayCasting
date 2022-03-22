#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.h"

#include <map>

enum class MapToken_t
{
	MAPTOKEN_FIELD = 0,
	MAPTOKEN_WALL,
	MAPTOKEN_WALL_BLUE,
	MAPTOKEN_EMPTY,
};

class Map
{
private:

	const char field[(int)FIELD_HEIGHT][1 + (int)FIELD_WIDTH] = {
		"1111111111",
		"1000000001",
		"1022200001",
		"1000000001",
		"1000011101",
		"1000000001",
		"1000000001",
		"1112222211",
	};

public:

	std::map<MapToken_t, sf::Texture> _textureMap;
	MapToken_t getMapToken(int x, int y);

};

