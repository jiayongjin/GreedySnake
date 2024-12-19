#pragma once
#define BodySize 40 //�ߵ�����Ϊ40*40

struct Point {
	int x;
	int y;
	Point(int _x,int _y):x(_x),y(_y){}
};

//ö���ĸ�����
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
	//����ҧ���Լ�����ǽ�ڵ�ʱ�򷵻�
	bool CheekCollision() const;//�ж��Ƿ�������ײ
	//void Grown();
	void IsateFood(CPoint food,CPoint head);//�ж��Ƿ�Ե�ʳ��
	//���÷�����
	void SetDirection(Direction dir);
	//�Զ����ƶ���ʵ��
	void AutoMoveToFood(CPoint food);//��ʳ�������
	void Draw(CDC *pDC,COLORREF color);
	vector<CPoint> GetBody() const;
	bool ateFood;
private:
	vector<CPoint> body;
	Direction currentDirection;
};
