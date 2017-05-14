#ifndef _ABOUT_LAYER_H_
#define _ABOUT_LAYER_H_

#include "GameDefine.h"

class AboutLayer :public Layer
{
public:
	AboutLayer();

	virtual ~AboutLayer();

	CREATE_FUNC(AboutLayer);

	virtual bool init();
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void CloseCallback(Ref* pSender);//�رջص�
	void AboutCallback(Ref* pSender);//���ڲ˵��Ļص�
	void SinaCallback(Ref* pSender);//����
	void ExitCallBack(Ref* pSender);//������Ϸ
};
#endif