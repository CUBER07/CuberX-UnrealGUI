#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

//��λ��


//�汾
string $CU_VERSION = "dev";
using namespace std;
namespace cuberx {
	class Base;

	//������Ϣ
	class WindowInfo {
	public:
		//��ȡ��ʾ���
		HANDLE GetDisplayHandle()
		{
			return GetStdHandle(STD_OUTPUT_HANDLE);
		}
		char NowFontsColor;
		char NowWindowColor;
	} WI;
	//��������
	class WindowSetting {
	private:
		short w;
		short h;
	public:
		WindowSetting() {
			w = 0;
			h = 0;
		}
		//���ڴ�С
		int WindowArea(short w, short h, bool ifcls = 0) {
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD size = { w, h };
			SetConsoleScreenBufferSize(hOut, size);
			SMALL_RECT rc = { 1,1, w, h };
			SetConsoleWindowInfo(hOut, true, &rc);
			if (ifcls == 1) system("cls");
			return 0;
		}
		//�������ڴ�С
		int LockWindow() {
			HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
			RECT rc;
			GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����
			//�ı�cmd���ڷ��
			SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
			//��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
			SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
			return 0;
		}
		//����ȫ����ʾ��ɫ
		int ColorSetting(char FontsColor = '7', char WindowColor = '0') {
			char SendStr[] = "color xx";
			char* p_ch = SendStr + 6;
			*p_ch = WindowColor;
			*(++p_ch) = FontsColor;
			system(SendStr);
			return 0;
		}
		//�����ת
		void PointJump(int pawnH, int pawnW, HANDLE handle = WI.GetDisplayHandle())
		{
			COORD PointPawn;
			PointPawn.X = pawnW;             //������
			PointPawn.Y = pawnH;             //������
			SetConsoleCursorPosition(handle, PointPawn);
		}

		/*��ɫ���
		0 = ��ɫ 8 = ��ɫ
		1 = ��ɫ 9 = ����ɫ
		2 = ��ɫ 10 = ����ɫ
		3 = ǳ��ɫ 11 = ��ǳ��ɫ
		4 = ��ɫ 12 = ����ɫ
		5 = ��ɫ 13 = ����ɫ
		6 = ��ɫ 14 = ����ɫ
		7 = ��ɫ 15 = ����ɫ
		https://blog.csdn.net/qq_42885747/article/details/103835671?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.control
		*/
		void colorOut(string str, int FontsColorInt, int WindowColorInt) {
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | (FontsColorInt + WindowColorInt * 16));
			cout << str;
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
		}

		
	} winS;
	template<class T>
	class SuperArray
	{
	private:
		T** mem;
		int HEIGHT;
		int WIDTH;
		bool ifON;
	public:
		SuperArray() 
		{
			HEIGHT = 0;
			WIDTH = 0;
			ifON = 0;
		}
		SuperArray(int height, int width) 
		{
			HEIGHT = height;
			WIDTH = width;
			ifON = 1;
			mem = new T * [HEIGHT];
			//����mem[HEIDHT][WIDTH];
			for (int i = 0; i < HEIGHT; i++)
			{
				mem[i] = new T[WIDTH];
			}
		}
		void reset(int newHeight, int newWidth)
		{
			if (ifON == 1)
			{
				for (int i = 0; i < HEIGHT; i++)
				{
					delete[] mem[i];
					mem[i] = 0;
				}
				delete[] mem;
				mem = 0;
			}
			HEIGHT = newHeight;
			WIDTH = newWidth;
			ifON = 1;
			mem = new T * [HEIGHT];
			//����mem[HEIDHT][WIDTH];
			for (int i = 0; i < HEIGHT; i++)
			{
				mem[i] = new T[WIDTH];
			}
		}
		~SuperArray()
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				delete[] mem[i];
				mem[i] = 0;
			}
			delete[] mem;
			mem = 0;
		}

		T* operator[](int a)
		{
			if (a < HEIGHT)
			{
				return mem[a];
			}
			else
			{
				return 0;
			}
		}
	};
	//λ����Ϣ
	struct Coordinate
	{
		int width = 0;
		int height = 0;
		int& x = width;
		int& y = height;
	};
	//ɫ����Ϣ
	struct ColorInfo
	{
		int backGround = 0;
		int font = 7;
	};
	//һ�����麯���İ�װ
	class CUFunction
	{
	public:
		//ע��:��ʾBase�����ָ����this_base������this
		virtual void func(Base* this_base) = 0;
	};
	//��λ��Ϣ
	class Key
	{
	public:
		static const int $UP = 72;
		static const int $DOWN = 80;
		static const int $LEFT = 75;
		static const int $RIGHT = 77;
		static const int $SPACE = 32;
		static const int $BACK_SPACE = 8;
		static const int $ESC = 27;
		static const int $ENTER = 13;
		static const int $DELETE = 83;
		static const int $INSERT = 82;
	} KEY;

	//������
	class Base
	{
	protected:
		cuberx::Coordinate location;
		cuberx::Coordinate size;
		string text;
		bool beChosed;
		bool canBeChosed;
		bool visible;
	public:
		Base()
		{
			text = " ";
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText)
		{
			text = newText;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		Base(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
		}
		virtual void RUN_WHEN_BE_CREATED()
		{
			return;
		}
		virtual void draw()
		{
			return;
		}
		virtual void whenBeChosed()
		{
			return;
		}
		virtual void whenStopChosed()
		{
			return;
		}
		//һ��涨��1��ʾ��ȡ�ɹ���0��ʾʧ��
		virtual int keyAction(int newKey)
		{
			return 1;
		}
		virtual void setText(string newText)
		{
			text = newText;
		}
		virtual bool getVisible()
		{
			return visible;
		}
		virtual void setVisible(bool ifVisible)
		{
			visible = ifVisible;
		}
		virtual void setCanBeChosed(bool ifCanBeChosed)
		{
			canBeChosed = ifCanBeChosed;
		}
		virtual bool getCanBeChosed()
		{
			return canBeChosed;
		}
	};

	//������
	class Container : public cuberx::Base
	{


	public:
		Container()
		{
			text = " ";
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText)
		{
			text = newText;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		Container(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
		}
		virtual int add(cuberx::Base* newObject)
		{
			return 0;
		}
		virtual int add(cuberx::Base& newObject)
		{
			return 0;
		}
		virtual void remove(cuberx::Base* newObject)
		{

		}
		virtual void remove(cuberx::Base& newObject)
		{

		}
	};

	//�����
	class Module : public cuberx::Base
	{
	public:
		Module()
		{

		}
		
	};

}