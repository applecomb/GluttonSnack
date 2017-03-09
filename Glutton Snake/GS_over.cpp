#include <graphics.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

#define BALL_AMOUNT		300

#ifdef	PI
#undef	PI
#endif

#define PI				3.14159f
#define PI2				(2*PI)
#define FLOATCOMP0(x)	(x < 0.01f && x > -0.01f)

using std::vector;

float getAngleByNormal(float x, float y)
{
	float d = sqrtf(x*x+y*y);
	if(FLOATCOMP0(d)) return .0f;
	float angle = asinf(y / d);
	if(x > .0f)
	{
		if(y > .0f)	return angle;
		else return PI2 + angle;
	}
	else
	{
		return PI - angle;
	}
}

class Ball
{
public:
	Ball() : m_x((float)getwidth() / 2), m_y((float)getheight() / 2)
	{
		s_speed += .01f;
		m_dx = s_speed * cosf(s_direction);
		m_dy = s_speed * sinf(s_direction);
		m_speed = s_speed;
		m_radius = (float)randomf() * 5.0f + 2.0f;
		m_color = random(0xff0000) + 0xffff;
		s_direction += .1f;
	}

	void update()
	{
		m_x += m_dx;
		m_y += m_dy;

		if(m_x < .0f || m_x > getwidth())
		{
			m_dx = -m_dx;
			m_x += m_dx;
		}
		if(m_y < .0f || m_y > getheight())
		{
			m_dy = -m_dy;
			m_y += m_dy;
		}

#ifdef _DEBUG

		if(m_x < .0f || m_x > getwidth()|| m_y < .0f || m_y > getheight())
		{
			setcaption("检测到某些点出界了!!");
		}

#endif
	}

	void render()
	{
		setfillcolor(m_color);
		setcolor(m_color);
		fillellipse(m_x, m_y, m_radius, m_radius);
	}

	void turn(float x, float y)
	{
		float aglBall = getAngleByNormal(-m_dx, -m_dy);
		float aglLine = getAngleByNormal(x, y);
		float angle = 2 * aglLine - aglBall;
		m_dx = cosf(angle) * m_speed;
		m_dy = sinf(angle) * m_speed;
		m_x += m_dx;
		m_y += m_dy;
	}

	void getPos(float& x, float& y)
	{
		x = m_x;
		y = m_y;
	}

	float getRadius() { return m_radius; }

	~Ball() {}

private:
	float m_x, m_y;
	float m_dx, m_dy;
	float m_radius;
	float m_speed;
	COLORREF m_color;
	static float s_direction;
	static float s_speed;
};

float Ball::s_direction;
float Ball::s_speed = 0.5f;

class Line
{
public:
	Line() {}
	Line(int x1, int y1, int x2, int y2)
		: m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_maxx(x1), m_minx(x2), m_maxy(y1), m_miny(y2)
	{
		if(m_maxx < m_minx) std::swap(m_maxx, m_minx);
		if(m_maxy < m_miny) std::swap(m_maxy, m_miny);
		getLineEquation();
	}
	~Line() {}

	void getLineEquation()  //ax + by + c = 0
	{
		float a = m_y1 - m_y2, b = m_x1 - m_x2, c = m_x1 * m_y2 - m_x2 * m_y1;
		if(FLOATCOMP0(b))
		{
			m_a = 1;
			m_b = 0.0f;
			m_c = -m_x1;
		}
		else
		{
			m_a = a / b;
			m_b = -1.0f;
			m_c = c / b;
		}
		m_d2 = m_a * m_a + m_b * m_b;
		m_d = sqrtf(m_d2);
	}

	void render() { line(m_x1, m_y1, m_x2, m_y2); }



private:
	int m_x1, m_y1;
	int m_x2, m_y2;
	int m_maxx, m_maxy, m_minx, m_miny;
	float m_a, m_b, m_c, m_d, m_d2;
};

class Scene
{
public:
	Scene() : m_activeBallNum(0), m_bUpdate(true), m_bBlurring(true) {}
	~Scene(){}

	void update()
	{
		static bool bFirstTime = true;
		if(bFirstTime)
		{

			setbkmode(TRANSPARENT);  // 真正双缓冲啊!也只有这个才会出现这种奇葩现象。
			setfont(50,0, "黑体"); // 你没保存系统状态,如果去掉这两句，你看看就知道了。
			if(m_activeBallNum < BALL_AMOUNT) ++m_activeBallNum;
			outtextxy(getwidth()/9,getheight()/3," Your score is good!");
			outtextxy(getwidth()/3, getheight()/12*7,"CAME OVER");
		}	
		if(m_bBlurring)
		{
			imagefilter_blurring(NULL, 0x7e, 0xff);
			swappage();
			delay_fps(60);
		}
		else
		{

			swappage();
			delay_fps(60);
			cleardevice();			
		}
	}

	void show()
	{
		for(int i = 0; i != m_activeBallNum; ++i)
		{
			if(m_bUpdate) m_ball[i].update();
			m_ball[i].render();
		}
		setcolor(WHITE);
	}

private:
	Ball m_ball[BALL_AMOUNT];
	vector<Line> m_vec;
	int m_activeBallNum;
	bool m_bBlurring, m_bUpdate;
};

void gameOver()
{
	setinitmode(0);
	setbkcolor(BLACK);
	randomize();
	Scene scene;
	for( ; ; )
	{
		scene.update();
		scene.show();
	}
}

