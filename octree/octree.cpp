
#include<iostream>
#include"octree.h"

using namespace std;

Octree::Octree():hasChildren(false),numBalls(0),depth(0){
	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
			for(int z=0;z<2;z++)
				children[x][y][z]=NULL;
}

Octree::Octree(Vec3f& c1, Vec3f& c2, int d):connerDown(c1),connerUp(c2),
	center((c1+c2)/2),hasChildren(false),numBalls(0),depth(d){
	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
			for(int z=0;z<2;z++)
				children[x][y][z]=NULL;
}

Octree::~Octree(){
	if(hasChildren){
		for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
			for(int z=0;z<2;z++)
				delete children[x][y][z];
	}
}

void Octree::destroyChildren(){

	collectBallsFromChildren(balls);

	for(int x=0;x<2;x++)
		for(int y=0;y<2;y++)
			for(int z=0;z<2;z++)
				delete children[x][y][z];

	hasChildren = false;
}

void Octree::collectBallsFromChildren(set<Ball*>& tb){
	if(hasChildren){
		for(int x=0;x<2;x++)
			for(int y=0;y<2;y++)
				for(int z=0;z<2;z++)
					children[x][y][z]->collectBallsFromChildren(tb);
	}
	else{
		for(set<Ball*>::iterator it = balls.begin();it != balls.end(); it++){
			tb.insert(*it);
		}
	}
}

void Octree::processBallInChildren(Ball* ball, bool addBall){
	Vec3f pos = ball->pos;
	float r = ball->radius;
	for(int x=0;x<2;x++){
		if(x==0){
			if(pos[0]-r > center[0])
				continue;
		}
		else{
			if(pos[0]+r < center[0])
				continue;
		}

		for(int y=0;y<2;y++){
			if(y==0){
				if(pos[1]-r > center[1])
					continue;
			}
			else{
				if(pos[1]+r < center[1])
					continue;
			}

			for(int z=0; z<2; z++){
				if(z==0){
					if(pos[2]-r > center[2])
						continue;
				}
				else{
					if(pos[2]+r < center[2])
						continue;
				}

				if(addBall)
					this->add(ball);
				else
					this->remove(ball);
			}
		}
	}
}

void Octree::add(Ball* ball){
	++numBalls;
	if(!hasChildren && numBalls > MAX_BALL_EACH_NODE
		&& depth < MAX_DEPTH_OF_TREE)
		spawnChildren();

	if(hasChildren)
		processBallInChildren(ball,true);
	else
		balls.insert(ball);
}

void Octree::spawnChildren(){
	for(int x=0;x<2;x++){
		float maxX,minX;
		if(x==0){
			minX = connerDown[0];
			maxX = center[0];
		}
		else{
			minX = center[0];
			maxX = connerUp[0];
		}
		for(int y=0;y<2;y++){
			float maxY,minY;
			if(y==0){
				minY = connerDown[1];
				maxY = center[1];
			}
			else{
				minY = center[1];
				maxY = connerUp[1];
			}
			for(int z=0; z<2; z++){
				float maxZ,minZ;
				if(z==0){
					minZ = connerDown[2];
					maxZ = center[2];
				}
				else{
					minZ = center[2];
					maxZ = connerUp[2];
				}

				children[x][y][z] = new Octree(Vec3f(minX,minY,minZ),Vec3f(maxX,maxY,maxZ),depth+1);
			}
		}
	}

	for(set<Ball*>::iterator it = balls.begin(); it != balls.end(); it++)
		processBallInChildren(*it,true);
	balls.clear();
	
	hasChildren = true;
}

void Octree::remove(Ball* ball){
	--numBalls;
	if(hasChildren && numBalls < MIN_BALL_EACH_NODE)
		destroyChildren();
	if(hasChildren)
		processBallInChildren(ball,false);
	else
		balls.erase(ball);
}

void Octree::getPossibleBallBallCollisions(vector<BallPair>& container,Octree* root){
	if(root->hasChildren){
		for(int x=0;x<2;x++)
			for(int y=0;y<2;y++)
				for(int z=0;z<2;z++)
					Octree::getPossibleBallBallCollisions(container,root->children[x][y][z]);
	}
	else{
		for(set<Ball*>::iterator it1 = root->balls.begin(); it1 != root->balls.end();it1++){
			Ball* ball1 = *it1;
			for(set<Ball*>::iterator it2 = root->balls.begin();it2 != root->balls.end();it2++){
				Ball* ball2 = *it2;
				if(ball1 < ball2){
					BallPair pair ;
					pair.ball1 = ball1;
					pair.ball2 = ball2;
					container.push_back(pair);
				}
			}
		}
	}
}

void Octree::getPossibleBallWallCollisions(vector<BallWallPair>& container,Octree* root){
	root->getPossibleBallWallCollisions(container,WALL_LEFT,'x',0);
	root->getPossibleBallWallCollisions(container,WALL_RIGHT,'x',1);
	root->getPossibleBallWallCollisions(container,WALL_FAR,'z',0);
	root->getPossibleBallWallCollisions(container,WALL_NEAR,'z',1);
	root->getPossibleBallWallCollisions(container,WALL_TOP,'y',1);
	root->getPossibleBallWallCollisions(container,WALL_BOTTOM,'y',0);
}

void Octree::getPossibleBallWallCollisions(vector<BallWallPair>& container,Wall wall,char dirt,int index){
	if(hasChildren){
		Octree* child = NULL;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				if(dirt=='x'){
					children[index][i][j]->getPossibleBallWallCollisions(container,wall,dirt,index);
				}
				else if(dirt=='y'){
					children[i][index][j]->getPossibleBallWallCollisions(container,wall,dirt,index);
				}
				else{
					children[i][j][index]->getPossibleBallWallCollisions(container,wall,dirt,index);
				}
	}
	else{
		for(set<Ball*>::iterator it = balls.begin(); it != balls.end();it++){
			BallWallPair pair ;
			pair.ball = *it;
			pair.wall = wall;
			container.push_back(pair);
		}
	}
}