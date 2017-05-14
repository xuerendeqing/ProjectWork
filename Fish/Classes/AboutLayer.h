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

	void CloseCallback(Ref* pSender);//关闭回调
	void AboutCallback(Ref* pSender);//关于菜单的回调
	void SinaCallback(Ref* pSender);//新浪
	void ExitCallBack(Ref* pSender);//结束游戏
};
#endif