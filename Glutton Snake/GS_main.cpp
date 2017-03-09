#include <graphics.h>
#include "GluttonSnake.h"
void main()
{
	initgraph(640,480);
	gamePlay();
	getch();
	closegraph();
}