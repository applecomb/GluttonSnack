#include <graphics.h>
#include "GluttonSnake.h"
int gameSvelocity(int v)
{
	char ch[10];
	int speed;
	inputbox_getline("蛇的起始速度设置","请输入1—500的整数，来设置蛇的起始速度：\n（单位/ms）\n注意：你所输入的数字越大，蛇的移动速度将越快",ch,10);
	v = atoi(ch);
	speed = 501-v;
	if (!(1<=speed&&speed<=500))
	{
		return gameSvelocity(v);
	}
	return speed;
}
void drawWall()
{
	int i;
	setbkcolor(BLACK);
	setcolor(BLACK);
	setfillcolor(GREEN);
	for (i = 0;i < getheight()/A;i++)
	{
		bar3d(0,A*i,A,A+A*i,0,0);
	}
	for (i = 0;i < getwidth()/A;i++)
	{
		bar3d(A*i,getheight()-A,A+A*i,getheight(),0,0);
	}
	for (i = getheight()/A;i >= 0;i--)
	{
		bar3d(getwidth()-A,0+A*i,getwidth(),A+A*i,0,0);
	}
	for (i = getwidth()/A;i >= 0;i--)
	{
		bar3d(A*i,0,A+A*i,A,0,0);
	}
	for (i = getwidth()/A;i >= 0;i--)
	{
		bar3d(A*i,3*A,A+A*i,4*A,0,0);
	}
}
snake initSnake()
{
	snake s;
	s.x[0] = 5*A;
	s.y[0] = 5*A;
	s.x[1] = 6*A;
	s.y[1] = 5*A;
	s.node = 2;
	s.life = 0;
	s.direction = 1;
	return s;
} 
food initFood()
{
	food f;
	randomize();
	f.x = random(getwidth()-10*A)+A;
	f.y = random(getheight()-10*A)+4*A;
	while(f.x % A != 0)
	{
		f.x++;
	}
	while(f.y % A != 0)
	{
		f.y++;
	}
	return f;
}
void drawSnake(snake s)
{
	int i;
	setcolor(BLACK);
	setfillcolor(LIGHTBLUE);
	for (i = 0; i < s.node;i++)
	{
		bar3d(s.x[i],s.y[i],s.x[i]+A,s.y[i]+A,0,0);
	}
	imagefilter_blurring(NULL, 0x7e, 0xff);
	delay_fps(60);
}
void drawFood(food f)
{
	setcolor(BLACK);
	setfillcolor(LIGHTRED);
	bar3d(f.x,f.y,f.x+A,f.y+A,0,0);
	imagefilter_blurring(NULL, 0x7e, 0xff);
}
snake updateSnake(snake s)
{
	int i;
	for(i = s.node-1;i > 0;i--)
	{
		s.x[i] = s.x[i-1];
		s.y[i] = s.y[i-1];
	}
	switch(s.direction)
	{
	case 1:  s.x[0] += A; break;
	case 2:  s.x[0] -= A; break;
	case 3:  s.y[0] -= A; break;
	case 4:  s.y[0] += A; break;
	}
	return s;
}
food updateFood(food f)
{
	randomize();
	if(f.yes == 1)
	{
		f.x = random(getwidth()-10*A)+A;
		f.y = random(getheight()-10*A)+4*A;
		while(f.x%A != 0)
		{
			f.x++;
		}
		while(f.y%A != 0)
		{
			f.y++;
		}
		f.yes = 0;
	}
	return f;
}
snake updateSdirection(snake s)
{
	key_msg k = getkey();
	if (k.key == key_up  &&  s.direction != 4)
	{
		s.direction = 3;
	}
	else if (k.key == key_right  &&  s.direction != 2)
	{
		s.direction = 1;
	}
	else if (k.key == key_left  &&  s.direction != 1)
	{
		s.direction = 2;
	}
	else if (k.key == key_down  &&  s.direction != 3)
	{
		s.direction = 4;
	}
	return s;
}
int toWall(snake s)
{
	if (s.x[0] < A  ||  s.x[0] > getwidth()-2*A  ||  s.y[0] < 4*A  ||  s.y[0] > getheight()-2*A)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int toItself(snake s)
{
	int i;
	for (i = 3;i < s.node;i++)
	{
		if (s.x[i] == s.x[0]  &&  s.y[i] == s.y[0])
		{
			return 1;
		}
	}
	return 0;
}
int eatFood(snake s,food f)
{
	if (s.x[0] == f.x  &&  s.y[0] == f.y)
	{
		return 1;
	}
	return 0;
}
void printScore(int socre)
{
	setcolor(RED);
	setbkmode(TRANSPARENT);
	setfont(2*A,0,"黑体");
	xyprintf(A+1,A,"得分:%d",socre);
}
void gamePlay()
{
	int i,v = 0,score = 0;
	gameBegain();
	v = gameSvelocity(v);
	snake s;
	food f;
	s = initSnake();
	f = initFood();
	while(1)
	{
		for (;!kbhit();delay_ms(v))
		{
			s = updateSnake(s);
			f = updateFood(f);

			if (eatFood(s,f) == 1)
			{
				s.node++;
				f.yes = 1;
				score++;
				v -= 5;
			}
			if (toWall(s)  ||  toItself(s))
			{
				s.life = 1;
				cleardevice();
				gameOver();
				getch();
			}
			if (kbhit())
			{
				s = updateSdirection(s);
			}
			drawWall();
			drawSnake(s);
			drawFood(f);
			printScore(score);
		}
		s = updateSdirection(s);
	}
}
void gameBegain()
{
	int z,t = 2,i;
	imagefilter_blurring(NULL, 0x7e, 0xff);
	setcolor(LIGHTBLUE);
	setfont(100,0,"宋体");
	xyprintf(getwidth()/40*9,getheight()/4,"GLETTON");
	xyprintf(getwidth()/40*9,getheight()/32*17," SNAKE");
	setcolor(BLACK);
	setfillcolor(GREEN);
	for (z = 7-A/5;z > 0;z--)
	{
		for (i = 0;i < getwidth()/A-4*(z-1)-1;i++)
		{
			bar3d(A*i+2*(z-1)*A,2*(z-1)*A,A+A*i+2*(z-1)*A,A+2*(z-1)*A,0,0);
			delay_ms(t);
		}
		for (i = 0;i < getheight()/A-4*(z-1)-1;i++)
		{
			bar3d(getwidth()-A-2*(z-1)*A,A*i+2*(z-1)*A,getwidth()-2*(z-1)*A,A+A*i+2*(z-1)*A,0,0);
			delay_ms(t);
		}
		for (i = getwidth()/A-1-4*(z-1);i > 0;i--)	
		{
			bar3d(A*i+2*(z-1)*A,getheight()-A-2*(z-1)*A,A+A*i+2*(z-1)*A,getheight()-2*(z-1)*A,0,0);
			delay_ms(t);
		}
		for (i = getheight()/A-4*(z-1);i > 0;i--)
		{
			bar3d(2*(z-1)*A,A*i+(2*(z-1)-1)*A,A+2*(z-1)*A,A+A*i+(2*(z-1)-1)*A,0,0);
			delay_ms(t);
		}
	}
	delay_ms(20);
	cleardevice();
}




