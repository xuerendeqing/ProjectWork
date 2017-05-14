#ifndef _SCENE_SHOT_H_
#define _SCENE_SHOT_H_

#include "GameDefine.h"

class SceneShot:public Layer
{
public:
	SceneShot();

	virtual ~SceneShot();

	static SceneShot* create(const std::string& strPath);

	bool init(const std::string& strPath);
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const char* m_Path;
	void CloseShotCallBack(Ref* pSender);//关闭截图界面
	void OpenShare(Ref* pSender);//打开分享菜单
};
#endif
