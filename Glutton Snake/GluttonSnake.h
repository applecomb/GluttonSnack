#include<graphics.h>
#define N 200
#define A 20
typedef struct snake{
	int x[N];
	int y[N];//存放蛇的每一节某点的坐标
	int node;//蛇的节数
	int life;//蛇的生命值
	int direction;//蛇的移动方向
}snake;//定义结构体的同时定义结构体的名称
typedef struct food{
	int x,y;//食物出现的坐标
	int yes;//食物的坐标是否需要改变
}food;
snake initSnake();//初始化蛇
food initFood();//初始化食物
void drawWall();//绘制墙壁
void drawSnake(snake s);//绘制蛇
void drawFood(food f);//绘制食物
snake updateSnake(snake s);//改变蛇的值
snake updateSdireciton(snake s);//改变蛇的移动方向
food updateFood(food f);//改变食物的位置
int toWall(snake s);//判断蛇是否撞墙
int toItself(snake s);//判断蛇是否撞到自己
int eatFood(snake s,food f);//判断蛇是否吃掉食物
void printScore(int score);//打印成绩
void gameOver();//游戏结束设计
void gamePlay();//游戏过程设计
void gameBegain();//游戏开始设计
void gameSvelocity(); 
