#pragma once

#include <SFML/Graphics.hpp>

struct Player
{
	double X;
	double Y;
	double Z;
	bool inJump = false;
	double jumpSpeed = 0;
	double angle;
};

enum class PlayerAction_t {
	ACTION_NONE = 0,
	ACTION_JUMP,
	ACTION_SIT_DOWN,
	ACTION_UNKNOWN
};

class Player_
{
private:
	sf::Vector3f _position;
	bool _isJump;
	double _jumpSpeed;
	double _rayAngle;

	PlayerAction_t _currentAction = PlayerAction_t::ACTION_NONE;

public:
	Player_() = default;

	void setPosition(const sf::Vector3f&);
	sf::Vector3f& getPosition();

	void setAngle(double);
	double getAngle();

	//TODO: сделать прыжок
	void makeAction(PlayerAction_t);
	PlayerAction_t getCurrentAction();

};

