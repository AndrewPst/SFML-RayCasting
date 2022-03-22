#include "Player.h"

void Player_::setPosition(const sf::Vector3f& pos) {
	_position = pos;
}

sf::Vector3f& Player_::getPosition() {
	return _position;
}

void Player_::setAngle(double angle) {
	_rayAngle = angle;
}

double Player_::getAngle() {
	return _rayAngle;
}

void Player_::makeAction(PlayerAction_t action) {
	_currentAction = action;
}

PlayerAction_t Player_::getCurrentAction() {
	return _currentAction;
}
