#ifndef _GAME_JNI_H_
#define _GAME_JNI_H_

#include "GameDefine.h"

void exitApp()//此文件定义编写提供android调用的C++接口。即android中调用C++的函数
{
	Director::getInstance()->end();
}
#endif