#pragma once
#include"CU Standard.h"
#include<iostream>
using namespace std;

//���Ⱥ��
namespace cuberx {
	//���Ⱥ��(�����ڶ��ڷ�����������ڴ�(����new�ؼ���),�����������Զ������ڴ�)
	template<int objectCount>
	class Group : public cuberx::Container
	{
	protected:
		cuberx::Base* objects[objectCount];
	public:
		Group()
		{
			for (int i = 0; i < objectCount; i++)
			{
				objects[i] = nullptr;
			}
		}
		~Group()
		{
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					delete objects[i];
					objects[i] = nullptr;
				}
			}
		}
		//�����������-1��ʾ��������
		virtual void draw(int offsetX = 0, int offsetY = 0, int index = -1)
		{
			if (index == -1)
			{
				for (int i = 0; i < objectCount; i++)
				{
					objects[i]->draw(location.x + offsetX, location.y + offsetY);
				}
			}
			else if (index >= 0)
			{
				objects[index]->draw(location.x + offsetX, location.y + offsetY);
			}
		}
		virtual void draw(int offsetX = 0, int offsetY = 0)
		{
			for (int i = 0; i < objectCount; i++)
			{
				objects[i]->draw(location.x + offsetX, location.y + offsetY);
			}
		}
		virtual void setNowChosingObject(int newChoingObject)
		{
			if (objects[nowChosingObject] != nullptr)
			{
				objects[nowChosingObject]->whenStopChosed();
			}
			if (objects[newChoingObject] != nullptr)
			{
				objects[newChoingObject]->whenBeChosed();
			}
			nowChosingObject = newChoingObject;
		}
		//��λ��Ӧ
		int keyAction(int newKey)
		{
			//
			int result = 0;
			for (int i = 0; i < objectCount; i++)
			{
				result = objects[i]->keyAction(newKey);
				if (result == 1)
				{
					return result;
				}
			}
			return result;
		}
		//����������������Ϣ(ͬ���������)
		virtual void setFatherMainWindow(cuberx::MainWindow* newFatherMainWindow)
		{
			fatherMainWindow = newFatherMainWindow;
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					objects[i]->setFatherMainWindow(newFatherMainWindow);
				}
			}
		}
		//����������������Ϣ(ͬ���������)
		virtual void resetFatherMainWindow()
		{
			fatherMainWindow = nullptr;
			for (int i = 0; i < objectCount; i++)
			{
				if (objects[i] != nullptr)
				{
					objects[i]->resetFatherMainWindow();
				}
			}
		}
	};

}

//�������:�߿�+��ɫ"��ʾ:"+��ɫ"����̫��"
namespace cuberx {

	class TestGroup : public cuberx::Group<3>
	{
	protected:
		cuberx::ARectFrame* arf;
		cuberx::AText* at;
		cuberx::CLText* clt;
	public:
		TestGroup()
		{
			arf = new cuberx::ARectFrame(17, 3, 0, 0);
			at = new cuberx::AText("��ʾ:", 5, 1, 2, 1);
			clt = new cuberx::CLText("����̫��", "00000000", "44444444", 8, 1, 8, 1);
			objects[0] = arf;
			objects[1] = at;
			objects[2] = clt;
		}
	};

}