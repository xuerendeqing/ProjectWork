#ifndef _GAME_JNI_H_
#define _GAME_JNI_H_

#include "GameDefine.h"

void exitApp()//���ļ������д�ṩandroid���õ�C++�ӿڡ���android�е���C++�ĺ���
{
	Director::getInstance()->end();
}
#endif