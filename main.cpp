#include <iostream>
#include "Cuber UnrealGUI.h"
using namespace std;
//TODO: FrameButton�еĲ�ɫ��ʾ����ѡ������ʾģʽ�л�  û���У�Ū���棡
int main()
{
	cuberx::AText aText("*#|test|#*", 10, 1, 5, 5);
	aText.draw();
	cuberx::FrameButton fb("���԰�ť",11,3,10,4);
	fb.setTextColor(15,0);
	fb.draw();
	
	cuberx::ARectFrame art(8, 4, 7, 7);
	art.draw();
	cuberx::winS.PointJump(12, 1);

	return 0;
}