#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "GameDefine.h"
#include "UILayer.h"


class GameLayer : public Layer
{
public:
	GameLayer();

	virtual ~GameLayer();

	static Scene *createScene();

	CREATE_FUNC(GameLayer);

	virtual bool init();

	GameState m_State;//状态机
	UILayer *m_UiLayer;

	//增加在Android平台下的返回键监听
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	void addFish();

	void updateScene(float dt);

	virtual void update(float dt);

	void updateFish(float dt);

	void createFishLine(float dt);

};
#endif
