#ifndef _CUSTOMER_SERVICE_H_
#define _CUSTOMER_SERVICE_H_

#include "GameDefine.h"

class CustomerService:public Layer
{
public:
	CustomerService();

	virtual ~CustomerService();

	CREATE_FUNC(CustomerService);

	virtual bool init();
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite *m_Confirm;
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
};
#endif
