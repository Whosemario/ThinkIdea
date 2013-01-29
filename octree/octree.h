#ifndef OCTREE_H
#define OCTREE_H

#include "ball.h"
#include <set>
#include <vector>

class Octree{
private:
	Vec3f connerDown;
	Vec3f connerUp;
	Vec3f center;
	bool hasChildren;
	int numBalls;
	Octree* children[2][2][2];
	std::set<Ball*> balls;
	int depth;

	void destroyChildren();
	void collectBallsFromChildren(std::set<Ball*>&);
	void processBallInChildren(Ball*,bool);
	void spawnChildren();
	void getPossibleBallWallCollisions(std::vector<BallWallPair>&,Wall,char,int);
public:
	const static int MAX_BALL_EACH_NODE = 10;
	const static int MIN_BALL_EACH_NODE = 3;
	const static int MAX_DEPTH_OF_TREE = 10;

	Octree();
	Octree(Vec3f&, Vec3f&, int);
	~Octree();

	void add(Ball*);
	void remove(Ball*);

	static void getPossibleBallBallCollisions(std::vector<BallPair>&,Octree*);
	static void getPossibleBallWallCollisions(std::vector<BallWallPair>&,Octree*);
};

#endif