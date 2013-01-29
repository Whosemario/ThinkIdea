#[Octree](http://en.wikipedia.org/wiki/Octree)#
![](http://upload.wikimedia.org/wikipedia/commons/thumb/2/20/Octree2.svg/640px-Octree2.svg.png)   
Octree是一个树形数据结构，它的每一个内部子节点有8个孩子节点。Octree常常用于3D图形或者3D游戏中，它将一个三维空间递归地分割为8个小的三维空间，如此递归下去，直到到达合适的节点为止。    
本代码中的Octree应用于快速查找三维空间中有多少小球碰撞的情况。将空间递归地分小，然后计算每一个小空间中小球的碰撞情况。

Octree类提供了4个主要的API：    
####void Octree::add(Ball* ball)####
此API主要将一个新的Ball加入到Octree中。
####void Octree::remove(Ball* ball)####
此API主要将一个久的Ball加入到Octree中。
####void Octree::getPossibleBallBallCollisions(vector<BallPair>& container,Octree* root)####
从以root为根的Octree中得到所有可能的相互碰撞的小球，结果存入container中，BallPair是两个Ball的指针。
####void Octree::getPossibleBallWallCollisions(vector<BallWallPair>& container,Octree* root)####
从以root为根的Octree中得到所有可能的与墙壁碰撞的小球，结构存入container中，BallWallPair一个是Ball的指针，一个是Wall的枚举值。

Octree类还提供了3个常量值：   
####MAX_BALL_EACH_NODE####
每个叶子节点可容纳的最大的小球数量
####MIN_BALL_EACH_NODE####
每个叶子节点可容纳的最小的小球数量
####MAX_DEPTH_OF_TREE####
Octree的最大深度