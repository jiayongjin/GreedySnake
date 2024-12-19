#include "pch.h"
#include "Snake.h"

Snake::Snake()
{
}

Snake::~Snake()
{
}

void Snake::Init(int row)
{
	ateFood = false;
	currentDirection = Direction::RIGHT;//开始的方向设置为向右
	body.clear();//点开始的时候清空这个vector容器
	body.push_back(CPoint(11, row));
	body.push_back(CPoint(10, row));
	body.push_back(CPoint(9, row));
}

//让蛇动起来
void Snake::Move(CPoint food)
{
	//确定蛇头的位置
	int headX = body.front().x;
	int headY = body.front().y;

	//根据蛇移动的方向确定蛇头的位置
	switch (currentDirection) {
	case Direction::UP:
		headY--;
		break;
	case Direction::DOWN:
		headY++;
		break;
	case Direction::LEFT:
		headX--;
		break;
	case Direction::RIGHT:
		headX++;
		break;
	}

	//检查碰撞


	//在蛇头前加一个新的点作为新的蛇头
	body.insert(body.begin(), CPoint(headX, headY));

	IsateFood(food,body.front());//判断是否吃到了食物

	//如果没有吃到实物，移除尾部的点以保持蛇的长度
	if (!ateFood) {
		body.pop_back();
	}
}

bool Snake::CheekCollision() const
{
	int x = body.front().x;
	int y = body.front().y;

	//检查是否撞墙(超出绘图控件的范围)
	if (x < 0 || x >=20 || y < 0 || y >= 20) {
		return true;
	}

	//检查是否撞到自己的身体
	for (size_t i = 1; i < body.size(); i++) {
		if (body[i].x == x && body[i].y == y) {
			return true;
		}
	}
	return false;
}

//如果蛇头的坐标和食物的坐标重合的话就吃到了食物
void Snake::IsateFood(CPoint food,CPoint head)
{
	if (food == head)
		ateFood = true;
	else
		ateFood = false;
}

//设置方向函数
void Snake::SetDirection(Direction dir)
{
	//根据当前蛇的方向避免直接方向移动
	if ((dir == Direction::UP && currentDirection != Direction::DOWN) ||
		(dir == Direction::DOWN && currentDirection != Direction::UP) ||
		(dir == Direction::LEFT && currentDirection!=Direction::RIGHT) ||
		(dir == Direction::RIGHT && currentDirection!=Direction::LEFT)) {
		currentDirection = dir;
	}
}

void Snake::AutoMoveToFood(CPoint food)
{
	int headX = body.front().x;
	int headY = body.front().y;

	int foodX = food.x;
	int foodY = food.y;

	if (headX < foodX&&currentDirection!=Direction::LEFT) {
		currentDirection = Direction::RIGHT;
	}
	else if (headX > foodX&&currentDirection!=Direction::RIGHT) {
		currentDirection = Direction::LEFT;
	}
	else if (headY < foodY&&currentDirection!=Direction::UP) {
		currentDirection = Direction::DOWN;
	}
	else if(currentDirection!=Direction::DOWN){
		currentDirection = Direction::UP;
	}
	else {
		currentDirection = Direction::UP;
	}
}

void Snake::Draw(CDC* pDC,COLORREF color)
{
	CBrush brush(color);//用传进来颜色来画蛇
	
	for (CPoint& point : body) {
		int left = point.x * BodySize;//每节身体的大小为40*40，计算绘制位置
		int top = point.y * BodySize;
		int right = left + BodySize;
		int bottom = top + BodySize;
		pDC->SelectObject(&brush);
		pDC->Rectangle(left, top, right, bottom);
	}
}

vector<CPoint> Snake::GetBody() const
{
	return body;
}

