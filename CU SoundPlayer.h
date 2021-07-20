#pragma once
#include"CU Standard.h"
#include<iostream>
#include<thread>
#include <mmsystem.h> //��������ͷ�ļ��� 
#pragma comment(lib,"winmm.lib")//�������������ӿ�
using namespace std;
/**/
namespace cuberx {

	class SoundPlayer : public cuberx::Module
	{
	private:
		const wchar_t* soundFile;
		bool useNewThread;//�Ƿ�ʹ�ö��̲߳���(����ʵ�ֶ���������в���)
		static void $playSound(wchar_t* file1, wchar_t* file2)
		{
			mciSendString(file1, NULL, 0, 0);
			mciSendString(file2, NULL, 0, 0);
		}
	public:
		SoundPlayer() : soundFile(L"")
		{
			useNewThread = 1;
		}
		SoundPlayer(wchar_t* newSoundFile, bool ifUseNewThread = 1) : soundFile(newSoundFile)
		{
			useNewThread = ifUseNewThread;
		}
		
		static thread* playSoundTool(wchar_t* newSoundFile1, wchar_t* newSoundFile2, bool ifUseNewThread = 1)
		{
			thread* thr = new thread($playSound, newSoundFile1, newSoundFile2);
			return thr;
		}
	};

}