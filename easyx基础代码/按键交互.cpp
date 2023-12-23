//����ʽ  ������ʽ
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

struct Ball
{
	int x;
	int y;
	int r;
	int dx;
	int dy;
};
Ball ball = {400, 400, 15, 2, -3};
Ball myball = { 500, 500,15,5,5 };
void Drawball(Ball ball)
{
	setfillcolor(RED);
	solidcircle(ball.x, ball.y, ball.r);
}


void Moveball()
{
	if (ball.x - ball.r <= 0 || ball.x + ball.r >= 800)
	{
		ball.dx = -ball.dx;
	}
	if (ball.y - ball.r <= 0 || ball.y + ball.r >= 800)
	{
		ball.dy = -ball.dy;
	}
	ball.x += ball.dx;
	ball.y += ball.dy;
}
// ��ʱ�� �����Զ��ƶ��Ķ���
int Timer(int duration, int id)
{
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration)
	{
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

void keyDown()
{
	int userkey = _getch();
	switch (userkey)
	{
	case 'w':
	case 'W':
	case 72:
		myball.y -= 15;
		break;
	case 'S':
	case 's':
	case 80:
		myball.y += 15;
		break;
	case 'a':
	case'A':
	case 75:
		myball.x -= 15;
		break;
	case'D':
	case'd':
	case 77:
		myball.x += 15;
		break;

	}

}

void KeyDown2()//�첽����
{
	if (GetAsyncKeyState(VK_UP))
	{
		myball.y -= 15;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		myball.y += 15;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		myball.x -= 15;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		myball.x += 15;
	}
}

int main(void)
{
	initgraph(800, 800);
	setbkcolor(LIGHTBLUE);
	BeginBatchDraw(); //˫����
	while (1)
	{
		cleardevice();
		Drawball(ball);
		Drawball(myball);
		if(Timer(20,0))
		Moveball();
		//if (_kbhit())
		//{
		//	keyDown();
		//}
		if (Timer(20, 1))
		KeyDown2();
		//Sleep(20);��������������
		FlushBatchDraw();//��ʾһ֡ ��ˢ���������ơ����ύ�������ͼ��
	}
	EndBatchDraw();
	closegraph();
	return 0;
}