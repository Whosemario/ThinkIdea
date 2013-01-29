
#ifndef BALL_H
#define BALL_H

#include "vec3f.h"

struct Ball{
	float radius;
	Vec3f pos;
};

enum Wall {WALL_LEFT, WALL_RIGHT, WALL_FAR, WALL_NEAR, WALL_TOP, WALL_BOTTOM};

struct BallPair{
	struct Ball* ball1;
	struct Ball* ball2;
};

struct BallWallPair {
	Ball* ball;
	Wall wall;
};

#endif