#pragma once
#include"CU Basic.h"
#include <iostream>
#include <thread>
#include <conio.h>
#define $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT 256
using namespace std;


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
	public:
		
		MainWindow()
		{
			title = "CuberX UnrealGUI ( " + $CU_VERSION + " )";
			enable = 0;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		MainWindow(string title, int new_size_width = 0, int new_size_height = 0, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			this->title = title;
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		MainWindow(int new_size_width = 0, int new_size_height = 0, bool enable = 0) : Container(new_size_width, new_size_height)
		{
			this->title = "CuberX UnrealGUI ( " + $CU_VERSION + " )";
			this->enable = enable;
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				objects[i] = 0;
			}
			timePerTick = 0;
			tickListenerMode = 2;
			nowChosingObject = 0;
		}
		
		//��Ӷ���
		int add(cuberx::Base* newObject)
		{
			for (int i = 0; i < $CU_MAINWINDOW_TOTAL_OBJECTS_COUNT; i++)
			{
				if (objects[i] == 0)
				{
					objects[i] = newObject;
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
					return *this;
				}
				
			}
			throw "[CuberX UnrealGUI]No Enough Place For The New Object. Please Change #define CU_MAINWINDOW_TOTAL_OBJECTS_COUNT.";
			return *this;
		}
		virtual thread* setEnable(bool ifEnable)
		{
			if (ifEnable)
			{
				enable = ifEnable;
				draw();
				if (useTickListener)
				{
					thread *tickListenerThread = new thread(tickListener, this);
					return tickListenerThread;	
				}
			}
			else
			{
				enable = ifEnable;
				setLastTestTickTime(0);
				return 0;
			}
			
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


		//֡�ʹ��������ᱻ��Ϊ���߳����ɣ�
		static void tickListener(MainWindow* this_MainWindow)
		{
			while(1)
			{
				//����Ƿ��йر�
				if (this_MainWindow->getUseTickListener() == 0 || this_MainWindow->getEnable() == 0)
				{
					return;
				}

				//У��֡��ʱ��(ǰ�߲�Ϊ��˵��������,���߲�Ϊ��˵�����ǵ�һ��ִ��)
				if (this_MainWindow->getTimePerTick() != 0 && this_MainWindow->getLastTestTickTime() != 0)
				{
					ULONGLONG pastTime = GetTickCount64() - this_MainWindow->getLastTestTickTime();
					//���ģʽ(1Ϊ��������,2Ϊ�������� �� ��ʱ����ִ��(����))
					switch (this_MainWindow->getTickListenerMode())
					{
					case 1:
					{
						if (pastTime < this_MainWindow->getTimePerTick())
						{
							Sleep(this_MainWindow->getTimePerTick() - pastTime);
						}
						this_MainWindow->setLastTestTickTime(GetTickCount64());
					}
					break;
					case 2:
					{
						if (pastTime <= this_MainWindow->getTimePerTick())
						{
							//����(����)|ǡ��(��0)  (��ִ��)
							Sleep(this_MainWindow->getTimePerTick() - pastTime);
							this_MainWindow->setLastTestTickTime(GetTickCount64());
						}
						else
						{
							//��ʱ(ִ�в�����[�ϴ�ʱ��])
							this_MainWindow->setLastTestTickTime(this_MainWindow->getLastTestTickTime() + this_MainWindow->getTimePerTick());
						}
					}
					break;
					default:
						cout << "\n[CuberX]Error:Unknown TickListenerMode";
						break;
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
				//TODO: ������

				
			}
			return;
		}
		virtual void keyListener(int newKey)
		{
			
			//ȫ�ּ�λ(������Ӧ)
			switch (newKey)
			{
			default:
				break;
			}

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