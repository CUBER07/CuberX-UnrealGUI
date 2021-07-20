#pragma once
#include<iostream>
#include<Windows.h>
#include <thread>
#include <conio.h>
using namespace std;

//�汾
string $CU_VERSION = "Main";

//Ԥ����
namespace cuberx
{
	class MainWindow;
}

//Basic
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
			SMALL_RECT rc = { 0,0, w - 1, h - 1};
			SetConsoleWindowInfo(hOut, 1, &rc);
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

		//��ʾ/���ع��
		void setCursorVisition(bool visible)
		{
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_CURSOR_INFO CursorInfo;
			GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
			CursorInfo.bVisible = visible; //���ؿ���̨���
			SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
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
	//������Ϣ
	class CUTask
	{
	private:
		unsigned short index;//���
		unsigned int tag;//��ǩ
		bool enable;//�Ƿ�����
		void(*runFunc)(cuberx::Base*);//���нӿں���
		cuberx::Base* RunClass;//���нӿڶ���
		DWORD CountDownTick;//ʣ��ʱ��
	public:
		CUTask()
		{
			index = 0;
			tag = 0;
			runFunc = NULL;
			CountDownTick = 0;
			RunClass = 0;
			enable = 0;
		}


		void setCountDownTick(DWORD newCountDownTick)
		{
			CountDownTick = newCountDownTick;
		}
		DWORD getCountDownTick()
		{
			return CountDownTick;
		}
		void setIndex(unsigned short newIndex)
		{
			this->index = newIndex;
		}
		unsigned short getIndex()
		{
			return index;
		}
		void setTag(unsigned int newTag)
		{
			tag = newTag;
		}
		unsigned int getTag()
		{
			return tag;
		}
		void setRunFunc(void(*newRunFunc)(cuberx::Base*))
		{
			runFunc = newRunFunc;
		}
		bool getEnable()
		{
			return enable;
		}
		void setEnable(bool ifEnable)
		{
			enable = ifEnable;
		}
		//��ȡ���к���ǰ��Ϊ��������(cuberx::Base*)Ϊ���صĺ����Ĳ���
		void (*getRunFunc())(cuberx::Base*)
		{
			return runFunc;
		}
		void setRunClass(cuberx::Base* newRunClass)
		{
			RunClass = newRunClass;
		}
		//��ȡĿ������ָ��
		cuberx::Base* getRunClass()
		{
			return RunClass;
		}
		//��ʣ��ʱ�̼���1
		void countDown()
		{
			CountDownTick -= 1;
			return;
		}

		//���и�����
		void run()
		{
			//���а󶨵ĺ���
			runFunc(RunClass);
			return;
		}
		//�������
		int reset()
		{
			index = 0;
			tag = 0;
			runFunc = NULL;
			RunClass = 0;
			CountDownTick = 0;
			setEnable(0);
			return 0;
		}
		//��������
		int set(cuberx::Base* NewRunClass, int NewTag, void(*NewRun)(cuberx::Base*) = 0, DWORD NewCountDownTick = 0, bool ifEnable = 1)
		{
			tag = NewTag;
			runFunc = NewRun;
			RunClass = NewRunClass;
			CountDownTick = NewCountDownTick;
			enable = ifEnable;
			return 0;
		}

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
		cuberx::MainWindow* fatherMainWindow;
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
			fatherMainWindow = 0;
		}
		Base(string newText)
		{
			text = newText;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
			fatherMainWindow = 0;
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
			fatherMainWindow = 0;
		}
		Base(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
			fatherMainWindow = 0;
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
			fatherMainWindow = 0;
		}
		Base(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 0;
			beChosed = 0;
			visible = 1;
			fatherMainWindow = 0;
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
			return 0;
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
		virtual void setSize(int width, int height)
		{
			size.width = width;
			size.height = height;
		}
		virtual Coordinate getSize()
		{
			return size;
		}
		virtual void setLocation(int width, int height)
		{
			location.width = width;
			location.height = height;
		}
		virtual Coordinate getLocation()
		{
			return location;
		}
		virtual void setCanBeChosed(bool ifCanBeChosed)
		{
			canBeChosed = ifCanBeChosed;
		}
		virtual bool getCanBeChosed()
		{
			return canBeChosed;
		}
		//����������������Ϣ
		virtual void setFatherMainWindow(cuberx::MainWindow* newFatherMainWindow)
		{
			fatherMainWindow = newFatherMainWindow;
		}
		//����������������Ϣ
		virtual void resetFatherMainWindow()
		{
			fatherMainWindow = 0;
		}
		//��ȡ����������
		virtual cuberx::MainWindow* getFatherMainWindow()
		{
			return fatherMainWindow;
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

//MainWindow
#define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT 256
#define $CU_MAINWINDOW_TOTAL_TASKS_COUNT 256
namespace cuberx {

	class MainWindow : public cuberx::Container
	{
	protected:
		string title;//���ڱ���(��ӳ�ڿ���̨��)
		bool enable;//�Ƿ�����
		bool useTickListener;//�Ƿ�ʹ��֡�ʹ�����
		bool checkKey;//�Ƿ����λ
		ULONGLONG lastTestTickTime;//��һ�μ��(����)֡ʱ��
		ULONGLONG timePerTick;//֡��ʱ��(0Ϊ������ ��λΪ����)
		int tickListenerMode;//���ģʽ(1Ϊ��������,2Ϊ�������� �� ��ʱ����ִ��)
		int nowChosingObject;//Ŀǰѡ���CU���(-1��ʾ��)
		cuberx::Base* objects[$CU_MAINWINDOW_TOTAL_OBJECTS_COUNT];
		cuberx::CUTask tasks[$CU_MAINWINDOW_TOTAL_TASKS_COUNT];
	public:

		MainWindow()
		{
			setSize(0, 0);
			title = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
			enable = 0;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
			{
				tasks[i].setIndex(i);
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
			checkKey = 1;
		}
		MainWindow(string title, int new_size_width = 0, int new_size_height = 0, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			setSize(new_size_width, new_size_height);
			this->title = title;
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
			{
				tasks[i].setIndex(i);
			}
			checkKey = 1;
		}
		MainWindow(int new_size_width, int new_size_height, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			setSize(new_size_width, new_size_height);
			this->title = "CuberX UnrealGUI  (" + $CU_VERSION + ")";
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
			{
				tasks[i].setIndex(i);
			}
			checkKey = 1;
		}

		//��Ӷ���
		int add(cuberx::Base* newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = newObject;
					newObject->setFatherMainWindow(this);
					return i;
				}
			}
			return -1;
		}
		int add(cuberx::Base& newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = &newObject;
					newObject.setFatherMainWindow(this);
					return i;
				}
			}
			return -1;
		}
		MainWindow& operator<<(cuberx::Base* newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = newObject;
					newObject->setFatherMainWindow(this);
					return *this;
				}

			}
			throw "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
			return *this;
		}
		MainWindow& operator<<(cuberx::Base& newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = &newObject;
					newObject.setFatherMainWindow(this);
					return *this;
				}

			}
			throw "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
			return *this;
		}

		//�Ƴ�����
		void remove(cuberx::Base* removeObject)
		{
			if (removeObject != 0)
			{
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] == removeObject)
					{
						objects[i]->resetFatherMainWindow();
						objects[i] = 0;
						draw();
					}
				}
			}
		}
		void remove(cuberx::Base& removeObject)
		{
			cuberx::Base* pRemoveObject = &removeObject;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == pRemoveObject)
				{
					objects[i]->resetFatherMainWindow();
					objects[i] = 0;
					draw();
				}
			}
		}
		MainWindow& operator-=(cuberx::Base* removeObject)
		{
			if (removeObject != 0)
			{
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] == removeObject)
					{
						objects[i]->resetFatherMainWindow();
						objects[i] = 0;
						draw();
					}
				}
			}
			return *this;
		}
		MainWindow& operator-=(cuberx::Base& removeObject)
		{
			cuberx::Base* pRemoveObject = &removeObject;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == pRemoveObject)
				{
					objects[i]->resetFatherMainWindow();
					objects[i] = 0;
					draw();
				}
			}

			return *this;
		}

		virtual thread* setEnable(bool ifEnable)
		{
			enable = ifEnable;
			if (ifEnable)
			{
				//���ô��ڴ�С
				if (getSize().height == 0 || getSize().width == 0)//ĳһ�ߴ�Ϊ��
				{

				}
				else//�����ߴ�(δ���Ǹ���)  ���ô��ڴ�С �� ����
				{
					cuberx::winS.WindowArea(getSize().width, getSize().height, 1);
					//�ӳ٣���ֹ����
					Sleep(10);
				}
				
				//������ʾ
				char setTitleString[256] = "title ";
				strcat_s(setTitleString, title.c_str());
				system(setTitleString);

				//���ع��
				cuberx::winS.setCursorVisition(0);

				//�����ȫ������
				draw();

				//����useTickListener ����֡�ʹ������߳�
				if (useTickListener)
				{
					thread* tickListenerThread = new thread(tickListener, this);
					return tickListenerThread;
				}

			}
			else
			{
				setLastTestTickTime(0);
				//��ʾ���
				cuberx::winS.setCursorVisition(1);
			}
			return 0;

		}
		virtual bool getEnable()
		{
			return enable;
		}
		virtual void draw(int drawObjectIndex = -1)
		{
			if (drawObjectIndex <= -1)
			{
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] != 0)
					{
						if (objects[i]->getVisible())
						{
							objects[i]->draw();
						}
					}
				}
			}
			else
			{
				objects[drawObjectIndex]->draw();
			}
		}
		virtual void setTimePerTick(ULONGLONG newTimePerTick)
		{
			timePerTick = newTimePerTick;
		}
		virtual ULONGLONG getTimePerTick()
		{
			return timePerTick;
		}
		virtual void setUseTickListener(bool ifUseTickListener)
		{
			useTickListener = ifUseTickListener;
			if (enable)
			{
				//ˢ��״̬������������
				setEnable(1);
			}
		}
		virtual bool getUseTickListener()
		{
			return useTickListener;
		}
		virtual void setCheckKey(bool ifCheckKey)
		{
			checkKey = ifCheckKey;
		}
		virtual bool getCheckKey()
		{
			return checkKey;
		}
		virtual ULONGLONG getLastTestTickTime()
		{
			return lastTestTickTime;
		}
		virtual void setLastTestTickTime(ULONGLONG newLastTestTickTime)
		{
			lastTestTickTime = newLastTestTickTime;
		}
		virtual void setTickListenerMode(int newMode)
		{
			tickListenerMode = newMode;
		}
		virtual int getTickListenerMode()
		{
			return tickListenerMode;
		}
		virtual int getNowChosingObject()
		{
			return nowChosingObject;
		}
		virtual void setNowChosingObject(int newChosingObject)
		{
			if (objects[newChosingObject] == 0)
			{
				cout << "[CuberX]Error:The newChosingObject Has Not Be Found!";
			}
			else
			{
				if (objects[nowChosingObject] != 0)
				{
					objects[nowChosingObject]->whenStopChosed();
				}
				objects[newChosingObject]->whenBeChosed();
				nowChosingObject = newChosingObject;
			}
		}

		//����������ȡ������Ϣ
		virtual cuberx::CUTask& getTaskInfo(int tagIndex)
		{
			return tasks[tagIndex];
		}
		//���������
		virtual int getNewTask()
		{

			//����Ѱ��
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
			{
				//Ѱ�ҵ���λ��δ���õ�����
				if (tasks[i].getEnable() == 0)
				{
					//���ø�����
					tasks[i].reset();
					//���ظ����������
					return i;
				}
			}

			//��������
			return -1;
		}
		//��������
		virtual void setTask(int taskIndex, cuberx::Base* NewRunClass, int NewTag, void(*NewRun)(cuberx::Base*), DWORD NewCountDownTick, bool ifEnable = 1)
		{
			tasks[taskIndex].set(NewRunClass, NewTag, NewRun, NewCountDownTick, ifEnable);
			return;
		}

		//֡�ʹ��������ᱻ��Ϊ���߳����ɣ�
		static void tickListener(MainWindow* this_MainWindow)
		{
			while (1)
			{
				//����Ƿ��йر�
				if (this_MainWindow->getUseTickListener() == 0 || this_MainWindow->getEnable() == 0)
				{
					return;
				}

				//У��֡��ʱ��(ǰ�߲�Ϊ��˵��������,���߲�Ϊ��˵�����ǵ�һ��ִ��)
				if (this_MainWindow->getTimePerTick() != 0)
				{
					if (this_MainWindow->getLastTestTickTime() != 0)
					{
						ULONGLONG pastTime = GetTickCount64() - this_MainWindow->getLastTestTickTime();
						//���ģʽ(1Ϊ��������,2Ϊ�������� �� ��ʱ����ִ��(����))
						switch (this_MainWindow->getTickListenerMode())
						{
						case 1:
						{
							if (pastTime < this_MainWindow->getTimePerTick())
							{
								Sleep((DWORD)this_MainWindow->getTimePerTick() - 1 - (DWORD)pastTime);
							}
							this_MainWindow->setLastTestTickTime(GetTickCount64());
						}
						break;
						case 2:
						{
							if (pastTime <= this_MainWindow->getTimePerTick())
							{
								//����(����)|ǡ��(��0)  (��ִ��)
								Sleep((DWORD)this_MainWindow->getTimePerTick() - (DWORD)pastTime);
								this_MainWindow->setLastTestTickTime(GetTickCount64());
							}
							else
							{
								//��ʱ(ִ�в�����[�ϴ�ʱ��])
								this_MainWindow->setLastTestTickTime(this_MainWindow->getLastTestTickTime() + this_MainWindow->getTimePerTick() - 1);
							}
						}
						break;
						default:
							cout << "\n[CuberX]Error:Unknown TickListenerMode";
							break;
						}
					}
					else
					{
						this_MainWindow->setLastTestTickTime(GetTickCount64());
					}
				}
				
				
				//����λ
				if (this_MainWindow->getCheckKey())
				{
					if (_kbhit())
					{
						int nowInputKey = _getch();
						this_MainWindow->keyListener(nowInputKey);
					}
				}

				//������
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_TASKS_COUNT; i++)
				{
					cuberx::CUTask& nowTask = this_MainWindow->getTaskInfo(i);
					//����������
					if (nowTask.getEnable())
					{
						//�ѵ���ʱ��
						if (nowTask.getCountDownTick() == 1)
						{
							//��������
							nowTask.run();
							//��������
							nowTask.reset();
						}
						//δ����ʱ��(0��ʾ������ʱ�䣡2��������Ϊδ����)
						else if (nowTask.getCountDownTick() > 1)
						{
							//��ʣ��ʱ�̼���1
							nowTask.countDown();
						}
					}
				}

			}
			return;
		}
		//���̼�����һ֡�ڣ�
		virtual void keyListener(int newKey)
		{

			//ȫ�ּ�λ(������Ӧ)



			int result = 0;

			//Ŀǰѡ�г�Ա
			if (getNowChosingObject() >= 0)
			{
				if (objects[getNowChosingObject()] != 0)
				{
					result = objects[getNowChosingObject()]->keyAction(newKey);
					if (result == 1)
					{
						return;
					}
				}
			}
			//����������Ա
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] != 0 && i != getNowChosingObject())
				{
					result = objects[i]->keyAction(newKey);
					if (result == 1)
					{
						return;
					}
				}
			}
			//ȫ�ּ�λ(�ͺ���Ӧ)
			switch (newKey)
			{
				//��(��)��
			case KEY.$UP:
			case KEY.$LEFT:
			{
				//����ʣ�ಿ�֣�����
				if (getNowChosingObject() != $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1)
				{
					for (int i = 1 + getNowChosingObject(); i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
					{
						if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
						{
							setNowChosingObject(i);
							return;
						}
					}
				}
				//����ȫ��������������δ�ɹ�����£�������
				for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
				{
					if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
					{
						setNowChosingObject(i);
						return;
					}
				}
			}
			break;

			//��(��)��
			case KEY.$DOWN:
			case KEY.$RIGHT:
			{
				//����ǰ�沿�֣�����
				if (getNowChosingObject() != 0)
				{
					for (int i = getNowChosingObject() - 1; i >= 0; i--)
					{
						if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
						{
							setNowChosingObject(i);
							return;
						}
					}
				}
				//����ȫ��������������δ�ɹ�����£�������
				for (int i = $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT - 1; i >= 0; i--)
				{
					if (objects[i] != 0 && objects[i]->getCanBeChosed() == 1)
					{
						setNowChosingObject(i);
						return;
					}
				}
			}
			break;
			default:
				break;
			}
		}
	};

}

//ARectFrame
namespace cuberx {
	//0.     1.���� 2. ���� 3. ���� 4. ��  5. ���� 6. ��  7. �ש� 8. �ߩ� 9. �ǩ� 10. ��  11. ��
	string frameChar[] = { "  ","����","�� ","����","�� " ,"����","�� ","�ש�","�ߩ�","�ǩ�","�� ", "��" };
	//���α߿�
	class ARectFrame : public cuberx::Module
	{
	protected:

	public:

		ARectFrame()
		{

		}
		ARectFrame(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
		}
		ARectFrame(int width, int height)
		{
			size.width = width;
			size.height = height;
		}


		void draw()
		{
			cuberx::winS.PointJump(location.y, location.x);
			cout << frameChar[1];
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y, location.x + 1 + i);
				cout << frameChar[5];
			}
			cuberx::winS.PointJump(location.y, location.x + size.width - 1);
			cout << frameChar[2];

			cuberx::winS.PointJump(location.y + size.height - 1, location.x);
			cout << frameChar[3];
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y + size.height - 1, location.x + 1 + i);
				cout << frameChar[5];
			}
			cuberx::winS.PointJump(location.y + size.height - 1, location.x + size.width - 1);
			cout << frameChar[4];

			for (int i = 0; i < size.y - 2; i++)
			{
				cuberx::winS.PointJump(location.y + 1 + i, location.x);
				cout << frameChar[6];
				cuberx::winS.PointJump(location.y + 1 + i, location.x + size.width - 1);
				cout << frameChar[6];
			}
		}

	};

}

//AText
namespace cuberx {

	class AText : public cuberx::Module
	{
	public:
		AText()
		{
			text = " ";
		}
		AText(string newText)
		{
			text = newText;
		}
		AText(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
		}
		AText(int width, int height)
		{
			size.width = width;
			size.height = height;
		}
		AText(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
		}
		AText(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
		}
		void draw()
		{
			cuberx::winS.PointJump(location.y, location.x);
			cout << text;
			cuberx::winS.PointJump(getFatherMainWindow()->getSize().y - 1, getFatherMainWindow()->getSize().x - 1);
		}
	};

}

//FrameButton
namespace cuberx {

	//0.     1.���� 2. ���� 3. ���� 4. ��  5. ���� 6. ��  7. �ש� 8. �ߩ� 9. �ǩ� 10. ��  11. ��


	class FrameButton : public cuberx::Module
	{
	private:
		cuberx::ColorInfo textColorInfo;
		cuberx::ColorInfo frameColorInfo;
		cuberx::ColorInfo chosedTextColorInfo;
		cuberx::ColorInfo chosedFrameColorInfo;
		cuberx::ColorInfo normalTextColorInfo;
		cuberx::ColorInfo normalFrameColorInfo;
		cuberx::CUFunction* clickAction;
		static void $action(cuberx::Base* bs)
		{
			cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
			pButton->setTextColor(8, 7);

			pButton->draw();
		}
		static void $action2(cuberx::Base* bs)
		{
			cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
			pButton->setTextColor(0, 7);
			pButton->setFrameColor(0, 7);
			pButton->draw();
		}
		static void $action3(cuberx::Base* bs)
		{
			cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
			pButton->setTextColor(15, 0);
			pButton->setFrameColor(0, 15);
			pButton->draw();
		}
		static void $action4(cuberx::Base* bs)
		{
			cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
			pButton->setTextColor(7, 0);
			pButton->setFrameColor(0, 7);
			pButton->draw();
		}
		static void $action5(cuberx::Base* bs)
		{
			cuberx::FrameButton* pButton = dynamic_cast<cuberx::FrameButton*>(bs);
			pButton->setTextColor(15, 0);
			pButton->setFrameColor(0, 15);
			pButton->draw();
		}
	public:
		FrameButton()
		{
			text = " ";
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText)
		{
			text = newText;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(int width, int height, int x, int y)
		{
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(int width, int height)
		{
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText, int width, int height, int x, int y)
		{
			text = newText;
			location.x = x;
			location.y = y;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		FrameButton(string newText, int width, int height)
		{
			text = newText;
			size.width = width;
			size.height = height;
			canBeChosed = 1;
			chosedTextColorInfo = { 7,0 };
			chosedFrameColorInfo = { 0,7 };
			normalTextColorInfo = { 0,7 };
			normalFrameColorInfo = { 0,7 };
			textColorInfo = normalTextColorInfo;
			frameColorInfo = normalFrameColorInfo;
			clickAction = 0;
		}
		void draw()
		{
			cuberx::winS.PointJump(location.y, location.x);
			winS.colorOut(frameChar[1], frameColorInfo.font, frameColorInfo.backGround);
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y, location.x + 1 + i);
				winS.colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y, location.x + size.width - 1);
			winS.colorOut(frameChar[2], frameColorInfo.font, frameColorInfo.backGround);

			cuberx::winS.PointJump(location.y + size.height - 1, location.x);
			winS.colorOut(frameChar[3], frameColorInfo.font, frameColorInfo.backGround);
			for (int i = 0; i < size.width - 2; i++)
			{
				cuberx::winS.PointJump(location.y + size.height - 1, location.x + 1 + i);
				winS.colorOut(frameChar[5], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y + size.height - 1, location.x + size.width - 1);
			winS.colorOut(frameChar[4], frameColorInfo.font, frameColorInfo.backGround);

			for (int i = 0; i < size.y - 2; i++)
			{
				cuberx::winS.PointJump(location.y + 1 + i, location.x);
				winS.colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
				cuberx::winS.PointJump(location.y + 1 + i, location.x + size.width - 1);
				winS.colorOut(frameChar[6], frameColorInfo.font, frameColorInfo.backGround);
			}
			cuberx::winS.PointJump(location.y + 1, location.x + 2);
			winS.colorOut(text, textColorInfo.font, textColorInfo.backGround);

			cuberx::winS.PointJump(getFatherMainWindow()->getSize().height - 1, getFatherMainWindow()->getSize().width - 1);
		}
		void whenBeChosed()
		{
			//setTextColor(chosedTextColorInfo.backGround, chosedTextColorInfo.font);
			//draw();
			cuberx::MainWindow& fmw = *getFatherMainWindow();


			//���нӿں���
			fmw.setTask(fmw.getNewTask(), this, 1, $action2, 2);
			fmw.setTask(fmw.getNewTask(), this, 1, $action3, 5);
		}
		void whenStopChosed()
		{
			//setTextColor(normalTextColorInfo.backGround, normalTextColorInfo.font);
			//draw();
			cuberx::MainWindow& fmw = *getFatherMainWindow();


			//���нӿں���
			fmw.setTask(fmw.getNewTask(), this, 1, $action, 4);
			fmw.setTask(fmw.getNewTask(), this, 1, $action2, 8);

		}


		void setTextColor(int backGround, int font)
		{
			textColorInfo.backGround = backGround;
			textColorInfo.font = font;
		}
		void setFrameColor(int backGround, int font)
		{
			frameColorInfo.backGround = backGround;
			frameColorInfo.font = font;
		}
		void setBeChosed(bool newCase)
		{
			beChosed = newCase;
			if (newCase)
			{
				whenBeChosed();
			}
		}
		void setClickAction(cuberx::CUFunction* newFunc)
		{
			clickAction = newFunc;
		}
		void setClickAction(cuberx::CUFunction& newFunc)
		{
			clickAction = &newFunc;
		}
		CUFunction& getClickAction()
		{
			return *clickAction;
		}
		int keyAction(int newKey)
		{
			switch (newKey)
			{
			case KEY.$ENTER:
			{
				cuberx::MainWindow& fmw = *getFatherMainWindow();


				//���нӿں���
				fmw.setTask(fmw.getNewTask(), this, 1, $action4, 2);

				if (&getClickAction() != 0)
				{
					getClickAction().func(this);
				}
				fmw.setTask(fmw.getNewTask(), this, 1, $action5, 35);
				return 1;
			}

			}
			return 0;
		}
	};

}