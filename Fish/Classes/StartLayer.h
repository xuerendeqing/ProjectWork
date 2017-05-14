#ifndef _START_LAYER_H_
#define _START_LAYER_H_

#include "GameDefine.h"
#include "RipplePge.h"

class StartLayer :public Layer
{
public:
	StartLayer();

	virtual ~StartLayer();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StartLayer);

	//增加在Android平台下的返回键监听
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);


	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	
	void updateWater(float dt);
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float runtime,m_touchTime;
	bool m_isService;
	RipplePge *m_ripple;
	Sprite *m_Service,*m_Eye;

	void ServiceCallback();

	void startGameCallBack(Ref* pSender);
	void GameCoinCallBack(Ref* pSender);//金币回调函数
	void GameDiamonCallBack(Ref* pSender);//钻石回调函数
	void GameSetCallback(Ref* pSender);//设置回调函数
	void GameAboutCallback(Ref* pSender);//游戏的分享和关于回调函数
	void EyeScaleYCallback();//创建眼睛缩放
	void EyeScaleCallback();
};
#endif