#include <iostream>
#include "CuberX UnrealGUI.h"
using namespace std;
//TODO: 1.FrameButton���ӳ���Ӧ(�����⣬�̶Ȳ���) 2.���ڴ�С���û������
int main()
{
	cuberx::FrameButton fb1("��ʼ��Ϸ",11,3,56,17);
	cuberx::FrameButton fb2("��Ϸ�̳�",11,3,56,21);
	cuberx::AText at1("���Խ���(��װ�Ǹ���Ϸ)", 22, 1, 51, 7);
	cuberx::ARectFrame arf(127, 32, 0, 0);
	cuberx::MainWindow mw(128,32);

	class gb_AC : public cuberx::CUFunction
	{
	public:
		void func(cuberx::Base* this_button)
		{
			/*
			this_button->setText("�ұ����!");
			this_button->draw();
			this_button->getFatherMainWindow()->setEnable(0);
			system("cls");
			cout << "�½���";
			*/
		}
	}gb_ac1,gb_ac2;
	fb1.setClickAction(gb_ac1);
	fb2.setClickAction(gb_ac2);


	mw << fb1 << fb2 << at1 << arf;
	mw.setUseTickListener(1);
	mw.setTimePerTick(5);
	mw.setEnable(1)->join();


	

	

	cuberx::winS.PointJump(12, 1);

	return 0;
}