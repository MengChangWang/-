//IMAGE������ʾͼƬ
/*����ͼ��
   loadimage��IMAGE* img,URL);ԭ������
   loadimage(IMAGE* img,URL ,int width,int height) ���ż���*/
   //��ʾͼƬ  putimage(int x,int y,IMAGE* img);��ʾλ�ã���ʾʲôͼƬ
#include <graphics.h>
#include <conio.h>

void yuan_yang_tietu()
{
	IMAGE img;
	loadimage(&img, "./image/image1.jpg", 800, 600);
	putimage(0, 0, &img);
}
void tou_ming_tietu()
{
	IMAGE img[2];
	loadimage(img , "./image/qie1.jpg");
	loadimage(img + 1, "./image/qie2.jpg");
	putimage(100, 100, img , SRCAND);
	putimage(100, 100, img + 1, SRCPAINT);
}

int main()  
{
	initgraph(800, 600);
	int a = 1;
	
	yuan_yang_tietu();
	tou_ming_tietu();
	 
	while (1);
	closegraph();
	return 0;
}