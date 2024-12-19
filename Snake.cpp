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
	currentDirection = Direction::RIGHT;//��ʼ�ķ�������Ϊ����
	body.clear();//�㿪ʼ��ʱ��������vector����
	body.push_back(CPoint(11, row));
	body.push_back(CPoint(10, row));
	body.push_back(CPoint(9, row));
}

//���߶�����
void Snake::Move(CPoint food)
{
	//ȷ����ͷ��λ��
	int headX = body.front().x;
	int headY = body.front().y;

	//�������ƶ��ķ���ȷ����ͷ��λ��
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

	//�����ײ


	//����ͷǰ��һ���µĵ���Ϊ�µ���ͷ
	body.insert(body.begin(), CPoint(headX, headY));

	IsateFood(food,body.front());//�ж��Ƿ�Ե���ʳ��

	//���û�гԵ�ʵ��Ƴ�β���ĵ��Ա����ߵĳ���
	if (!ateFood) {
		body.pop_back();
	}
}

bool Snake::CheekCollision() const
{
	int x = body.front().x;
	int y = body.front().y;

	//����Ƿ�ײǽ(������ͼ�ؼ��ķ�Χ)
	if (x < 0 || x >=20 || y < 0 || y >= 20) {
		return true;
	}

	//����Ƿ�ײ���Լ�������
	for (size_t i = 1; i < body.size(); i++) {
		if (body[i].x == x && body[i].y == y) {
			return true;
		}
	}
	return false;
}

//�����ͷ�������ʳ��������غϵĻ��ͳԵ���ʳ��
void Snake::IsateFood(CPoint food,CPoint head)
{
	if (food == head)
		ateFood = true;
	else
		ateFood = false;
}

//���÷�����
void Snake::SetDirection(Direction dir)
{
	//���ݵ�ǰ�ߵķ������ֱ�ӷ����ƶ�
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
	CBrush brush(color);//�ô�������ɫ������
	
	for (CPoint& point : body) {
		int left = point.x * BodySize;//ÿ������Ĵ�СΪ40*40���������λ��
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

