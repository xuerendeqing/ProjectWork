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

	//������Androidƽ̨�µķ��ؼ�����
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
	void GameCoinCallBack(Ref* pSender);//��һص�����
	void GameDiamonCallBack(Ref* pSender);//��ʯ�ص�����
	void GameSetCallback(Ref* pSender);//���ûص�����
	void GameAboutCallback(Ref* pSender);//��Ϸ�ķ���͹��ڻص�����
	void EyeScaleYCallback();//�����۾�����
	void EyeScaleCallback();
};
#endif