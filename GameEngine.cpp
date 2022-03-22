#include "GameEngine.h"

using sf::Keyboard;

GameEngine::GameEngine(sf::RenderWindow& window) : _window(window)
{
}

void GameEngine::initializate()
{
	player.setPosition(sf::Vector3f(4, 4, 0));
	player.setAngle(0);
	sf::Texture texture1, texture2;
	texture1.loadFromFile("stone.jpg");
	texture1.setSmooth(false);
	_map._textureMap.insert({ MapToken_t::MAPTOKEN_WALL, texture1 });

	texture2.loadFromFile("stone1.jpg");
	texture2.setSmooth(false);
	_map._textureMap.insert({ MapToken_t::MAPTOKEN_WALL_BLUE, texture2 });
}

void GameEngine::tick()
{
#pragma region FPS counter
	_fps.update();
	std::stringstream  ss;
	ss << _fps.getFPS();
	_window.setTitle(ss.str());
#pragma endregion


#pragma region Logic

	checkKeys();
	drawSkyAndFloor();
	draw();

#pragma endregion
}

void GameEngine::drawSkyAndFloor()
{
	sf::RectangleShape rect(sf::Vector2f(D_WIDTH, D_HEIGHT / 2));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Cyan);
	_window.draw(rect);
	rect.setPosition(0, D_HEIGHT / 2);
	rect.setFillColor(sf::Color::Green);
	_window.draw(rect);

}


/*
Отличие алгоритма от стандартного :
Мы не идем с маленьким шагом. Поле состоит из квадатов, которые строятся пересекающимеся
горизонтальными и ветикальными линиями. Мы идем сначала по всем вертикальным линиям, потом по гоизонтальным, соханяя
параметры с структуру. Выбираем ту, у которой препятствие ближе
*/

void GameEngine::draw()
{
	double angle = player.getAngle() - FOV / 2;
	for (double a = 0; a < NUM_RAYS; a += 1)
	{
		angle += DELTA_ANGLE;
		double cos_r = cos(angle);
		double sin_r = sin(angle);

#pragma region  X ray trasting

		RayCastParameters_t pX;
		//выбираем направление движения луча
		if (cos_r >= 0) {
			pX.startCoord = ceil(player.getPosition().x);
			pX.koef = 1;
		}
		else
		{
			pX.startCoord = floor(player.getPosition().x);
			pX.koef = -1;
		}

		for (int i = 0; i <= FIELD_WIDTH; i++) {
			pX.rayDepth = (pX.startCoord - player.getPosition().x) / cos_r;
			pX.otherCoord = player.getPosition().y + pX.rayDepth * sin_r;

			int _y = floor(pX.otherCoord);
			int _x = floor(pX.startCoord);

			pX.mapToken = _map.getMapToken(_x - (pX.koef < 0 ? 1 : 0), _y);
			if (pX.mapToken != MapToken_t::MAPTOKEN_FIELD && pX.mapToken != MapToken_t::MAPTOKEN_EMPTY) {
				break;
			}
			pX.startCoord += pX.koef;
		}
#pragma endregion

#pragma region Y ray trasting

		//Тоже самое для ветикалей
		RayCastParameters_t pY;

		if (sin_r >= 0) {
			pY.startCoord = ceil(player.getPosition().y);
			pY.koef = 1;
		}
		else
		{
			pY.startCoord = floor(player.getPosition().y);
			pY.koef = -1;
		}

		for (int i = 0; i <= FIELD_HEIGHT; i++) {
			pY.rayDepth = (pY.startCoord - player.getPosition().y) / sin_r;
			pY.otherCoord = player.getPosition().x + pY.rayDepth * cos_r;

			int _y = floor(pY.startCoord);
			int _x = floor(pY.otherCoord);
			pY.mapToken = _map.getMapToken(_x, _y - (pY.koef < 0 ? 1 : 0));
			if (pY.mapToken != MapToken_t::MAPTOKEN_FIELD && pY.mapToken != MapToken_t::MAPTOKEN_EMPTY) {
				break;
			}
			pY.startCoord += pY.koef;
		}
#pragma endregion

#pragma region Choosing the nearest obstacle
		RayCastParameters_t rayCastParam;
		if (pX.rayDepth < pY.rayDepth) {
			rayCastParam = pX;
		}
		else {
			rayCastParam = pY;
		}
		double cValue = pow(rayCastParam.rayDepth, 0.5);
		if (cValue < 1)
			cValue = 1;
		double tempCoord = fmod(rayCastParam.otherCoord, 1.0);
#pragma endregion

		rayCastParam.rayDepth *= cos(player.getAngle() - angle);
		double proj_height = ((NUM_RAYS / tan(FOV / 1))) / rayCastParam.rayDepth;

		sf::Sprite sprite;
		sprite.setTexture(_map._textureMap[rayCastParam.mapToken]);
		double rectSize = sprite.getLocalBounds().width / NUM_RAYS;
		double pos = tempCoord * sprite.getLocalBounds().width;
		sprite.setTextureRect(sf::IntRect((int)(pos), 0, rectSize, sprite.getLocalBounds().height));
		double koefY = proj_height / (double)sprite.getLocalBounds().height;

		double sizeX = pow(WIDTH_FACTOR, 2);
		double koefX = sizeX / (sprite.getLocalBounds().width);
		sprite.setScale(koefX, koefY);
		sf::Color cl = sf::Color(sprite.getColor());
		cl.r = 255 / pow(cValue, 1.5);
		cl.g = 255 / pow(cValue, 1.5);
		cl.b = 255 / pow(cValue, 1.5);
		sprite.setColor(cl);
		sprite.setPosition(a * pow(WIDTH_FACTOR, 1), D_HEIGHT / 2.0 - proj_height / 2.0 + player.getPosition().z / rayCastParam.rayDepth);
		_window.draw(sprite);
	}
}

void GameEngine::checkKeys()
{
	double mSpeed = MOVE_SPEED;
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		player.getPosition().x += mSpeed * cos(player.getAngle());
		player.getPosition().y += mSpeed * sin(player.getAngle());
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		player.getPosition().x -= mSpeed * cos(player.getAngle());
		player.getPosition().y -= mSpeed * sin(player.getAngle());
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
		player.getPosition().x += mSpeed * cos(player.getAngle() + M_PI_2);
		player.getPosition().y += mSpeed * sin(player.getAngle() + M_PI_2);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
		player.getPosition().x -= mSpeed * cos(player.getAngle() + M_PI_2);
		player.getPosition().y -= mSpeed * sin(player.getAngle() + M_PI_2);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		player.setAngle(player.getAngle() + ROTATION_SPEED);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		player.setAngle(player.getAngle() - ROTATION_SPEED);
	}
}