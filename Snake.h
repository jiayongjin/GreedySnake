#pragma once
#define BodySize 40 //蛇的身体为40*40

struct Point {
	int x;
	int y;
	Point(int _x,int _y):x(_x),y(_y){}
};

//枚举四个方向
enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
class Snake
{
public:
	Snake();
	~Snake();

	void Init(int row);
	void Move(CPoint food);
	//当蛇咬到自己碰到墙壁的时候返回
	bool CheekCollision() const;//判断是否发生了碰撞
	//void Grown();
	void IsateFood(CPoint food,CPoint head);//判断是否吃到食物
	//设置方向函数
	void SetDirection(Direction dir);
	//自动的移动到实物
	void AutoMoveToFood(CPoint food);//传食物的坐标
	void Draw(CDC *pDC,COLORREF color);
	vector<CPoint> GetBody() const;
	bool ateFood;
private:
	vector<CPoint> body;
	Direction currentDirection;
};
