#include<graphics.h>
#define N 200
#define A 20
typedef struct snake{
	int x[N];
	int y[N];//����ߵ�ÿһ��ĳ�������
	int node;//�ߵĽ���
	int life;//�ߵ�����ֵ
	int direction;//�ߵ��ƶ�����
}snake;//����ṹ���ͬʱ����ṹ�������
typedef struct food{
	int x,y;//ʳ����ֵ�����
	int yes;//ʳ��������Ƿ���Ҫ�ı�
}food;
snake initSnake();//��ʼ����
food initFood();//��ʼ��ʳ��
void drawWall();//����ǽ��
void drawSnake(snake s);//������
void drawFood(food f);//����ʳ��
snake updateSnake(snake s);//�ı��ߵ�ֵ
snake updateSdireciton(snake s);//�ı��ߵ��ƶ�����
food updateFood(food f);//�ı�ʳ���λ��
int toWall(snake s);//�ж����Ƿ�ײǽ
int toItself(snake s);//�ж����Ƿ�ײ���Լ�
int eatFood(snake s,food f);//�ж����Ƿ�Ե�ʳ��
void printScore(int score);//��ӡ�ɼ�
void gameOver();//��Ϸ�������
void gamePlay();//��Ϸ�������
void gameBegain();//��Ϸ��ʼ���
void gameSvelocity(); 
