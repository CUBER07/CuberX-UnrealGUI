
#include "CU Standard.h"

using namespace std;
//TODO: 1.��Ӷ��text���� 2.FrameButton���ӳ���Ӧ(�����⣬�̶Ȳ���) 3.FrameButton�Ľ�����bug�������л�ʱ��

int main()
{

    cuberx::FrameButton fb1("��ʼ��Ϸ", 11, 3, 56, 12);
    cuberx::FrameButton fb2("��Ϸ�̳�", 11, 3, 56, 16);
    cuberx::TextButton ttb("   ���Ǹ�DEMO   ", 54, 22, 22, 1);
    cuberx::AText at1("���Խ���(��װ�Ǹ���Ϸ)", 22, 1, 51, 7);
    cuberx::ARectFrame arf(127, 32, 0, 0);
    cuberx::MainWindow mw("���Խ���", 128, 32);
    cuberx::CLText clt(" MUSIC ", "CCCCCCC", "7777777", 7, 1, 119, 1);
    cuberx::TipBar tb("��ʾ: ", "�����¼���ҳ!", "000000000000", "88AAAA888888", 0, 0, false, 0, 23, 3);
    cuberx::PGBar pgb(50, 12, 28, 100, 0, 0, 1, 8, 15);
    class gb_AC : public cuberx::CUFunction
    {
    public:
        void func(cuberx::Base* this_button)
        {
            /*
                this_button->getFatherMainWindow()->setEnable(0);
                system("cls");
                cout << "�½���";
                */
        }
    }gb_ac1, gb_ac2;
    fb1.setClickAction(gb_ac1);
    fb2.setClickAction(gb_ac2);

    mw << fb1 << fb2 << at1 << arf << clt << tb << pgb << ttb;
    mw.setUseTickListener(1);
    mw.setTimePerTick(10);
    thread* thr = mw.setEnable(1);
    Sleep(5000);
    tb.setCLText("������������ɺ�ɼ�������", "NNNNNNNNNNNNNNNNNNNNNNN", "6666666666666666666666666666666666666666666666666666");
    cuberx::WAVSoundPlayer sp("7q412-dqfzq.wav", 1);
    mw.setCheckKey(0);
    Sleep(100);
    sp.playSound();
    clt.setTextColorInfo("AAAAAAA", "FFFFFFF");
    for (int i = 0; i < 100; i++)
    {
        pgb.setNowValue(pgb.getNowValue() + 1);
        Sleep(10);
    }
    mw.setCheckKey(1);




    thr->join();


    cuberx::winS.PointJump(12, 1);

    return 0;
}

template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y)
{
    return x + y;
}

