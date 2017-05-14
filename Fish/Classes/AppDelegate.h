#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "GameDefine.h"

class  AppDelegate : private Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	virtual void initGLContextAttrs();

	virtual bool applicationDidFinishLaunching();

	virtual void applicationDidEnterBackground();

	virtual void applicationWillEnterForeground();
private:
	void initBackMusic();

	void initEffect();

	void initUserData();
};
#endif 

