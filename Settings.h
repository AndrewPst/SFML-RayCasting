#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

constexpr double MOVE_SPEED = 0.01;
constexpr double ROTATION_SPEED = 0.005;
constexpr int JUMP_ACCELERATION = -2;
constexpr int JUMP_HEIGHT = 60;
constexpr int SHIFT_MODE_Z = -400;

constexpr double FIELD_HEIGHT = 8;
constexpr double FIELD_WIDTH = 10;

constexpr double D_HEIGHT = 800;
constexpr double D_WIDTH = 1024;

constexpr double BLOCK_SIZE = D_WIDTH / FIELD_WIDTH;

constexpr double FOV = (M_PI/3.0);
constexpr double NUM_RAYS = 1024;
constexpr double DELTA_ANGLE = (FOV / (NUM_RAYS ));

constexpr double WIDTH_FACTOR = D_WIDTH / (NUM_RAYS);