#ifndef _LOADING_H_
#define _LOADING_H_

#include "GameDefine.h"

class Loading : public Layer
{
public:
	Loading();

	virtual ~Loading();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Loading);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	short int current_number, total_number;
	void LoadingResource(Texture2D* texture);
};
#endif 