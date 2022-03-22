#include "Map.h"

MapToken_t Map::getMapToken(int x, int y) 
{
	if (x > FIELD_WIDTH || x < 0 || y > FIELD_HEIGHT || y < 0)
		return MapToken_t::MAPTOKEN_EMPTY;
	return (MapToken_t)(field[y][x] - '0');
}
