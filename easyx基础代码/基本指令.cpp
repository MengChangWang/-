#include<graphics.h>//�����ѱ���̭�ĺ���
// #include<easyx.h> ֻ�������µĺ���

void Draw()//������
{
	initgraph(400, 400);
	setbkcolor(LIGHTBLUE);//�����úô��ڴ�С�������ñ�����ɫ
	cleardevice(); 
	setlinecolor(BLACK);//�����ߵ���ɫ
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
	initgraph(800, 600, 1);//initgraph(int x,int y,int style) x��y���꣬��ʾ��ʽ��1��ʾ��ʾ����̨������дstyle�Ĳ�����ʾ����ʾ����̨
	setbkcolor(RED);//���ñ�����ɫ���� 1.��ɫ�� 2.RGB����
	cleardevice();//ˢ���豸��Ļ (���ñ�����ɫ��Ҫ���ϸú���)

	//line(int x,int y,int x,int y) ���ߺ����������������յ�
	//circle(int x,int y,int r) 
	//rectangle(int x,int y,int x,int y)������ ���������Ͻ���������½�����
	
	//���������ɫ setfillcolor() 
	// ���ߵ�Բ fillcircle(int x,int y,int r) �����ߵ�Բ solidcircle(int x,int y,int r)


	//while (1);//��ֹ����
	//closegraph();//�رմ���
	Draw();

	return 0;
}
