#include <iostream>
#include "Cuber UnrealGUI.h"
using namespace std;
//TODO: ���MainWindow��������
int main()
{
	cuberx::FrameButton fb1("���԰�ť1",12,3,0,0);
	cuberx::FrameButton fb2("���԰�ť2",12,3,0,5);
	cuberx::MainWindow mw("Test Window",50,50);
	class gb_AC : public cuberx::CUFunction
	{
	public:
		void func(cuberx::Base* this_button)
		{
			this_button->setText("�ұ����!");
			this_button->draw();
		}
	}gb_ac1,gb_ac2;
	fb1.setClickAction(gb_ac1);
	fb2.setClickAction(gb_ac2);

	mw << fb1 << fb2;
	mw.setUseTickListener(1);
	mw.setTimePerTick(0);
	mw.setEnable(1)->join();


	

	

	cuberx::winS.PointJump(12, 1);

	return 0;
}