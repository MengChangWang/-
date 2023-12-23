#include<graphics.h>//包含已被淘汰的函数
// #include<easyx.h> 只包含最新的函数

void Draw()//画棋盘
{
	initgraph(400, 400);
	setbkcolor(LIGHTBLUE);//先设置好窗口大小，再设置背景颜色
	cleardevice(); 
	setlinecolor(BLACK);//设置线的颜色
	for (int i = 0; i < 400; i += 20)
	{
		line(0, i, 400, i);
		line(i, 0, i, 400);
	}
	while (1);
	closegraph();
	closegraph();
	closegraph();
}


int main()
{
	initgraph(800, 600, 1);//initgraph(int x,int y,int style) x，y坐标，显示方式（1表示显示控制台），不写style的参数表示不显示控制台
	setbkcolor(RED);//设置背景颜色函数 1.颜色宏 2.RGB设置
	cleardevice();//刷新设备屏幕 (设置背景颜色后，要加上该函数)

	//line(int x,int y,int x,int y) 画线函数，参数：起点加终点
	//circle(int x,int y,int r) 
	//rectangle(int x,int y,int x,int y)画矩形 参数：左上角坐标和右下角坐标
	
	//设置填充颜色 setfillcolor() 
	// 带线的圆 fillcircle(int x,int y,int r) 不带线的圆 solidcircle(int x,int y,int r)


	//while (1);//防止闪屏
	//closegraph();//关闭窗口
	Draw();

	return 0;
}
