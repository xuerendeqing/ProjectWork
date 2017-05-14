#include "AppDelegate.h"
#include "Loading.h"
#include "Config.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

void AppDelegate::initGLContextAttrs()
{
   
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
	{
        glview = GLViewImpl::create("Cocos");
        director->setOpenGLView(glview);
    }
	
	//glview->setFrameSize(800,480);

	Size frameSize = glview->getFrameSize();

	if (frameSize.width <= 480 && frameSize.height <= 320)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 800 && frameSize.height <= 480)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 854 && frameSize.height <= 480)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_WIDTH);
	}
	else if (frameSize.width <= 960 && frameSize.height <= 540)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_WIDTH);
	}
	else if (frameSize.width <= 960 && frameSize.height <= 640)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 1024 && frameSize.height <= 768)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 1136 && frameSize.height <= 640)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
	}
	else if (frameSize.width <= 1280 && frameSize.height <= 720)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
	}
	else if (frameSize.width <= 1280 && frameSize.height <= 800)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 1920 && frameSize.height <= 1080)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 2048 && frameSize.height <= 1536)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}
	else if (frameSize.width <= 2560 && frameSize.height <= 1600)
	{
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	}

	director->setDisplayStats(true);     

	director->setAnimationInterval(1.0f / 60.0f);
	UserDefault::getInstance()->getXMLFilePath();
	if (UserDefault::getInstance()->isXMLFileExist())
	{
		//初始化xml文件中的数据和音效开关状态
		GetIntegerFromXML("MyGold");
		GetIntegerFromXML("MyDiamond");
		GetBooleanFromXML("MyMusic");
		GetBooleanFromXML("MySound");
		GetIntegerFromXML("MyCannonType");
		GetIntegerFromXML("MyTask");//初始化任务
	}
	//加载音效
	this->initBackMusic();

	this->initEffect();

	auto scene = Loading::createScene();

	director->runWithScene(scene);

	return true;
}


void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
	Director::getInstance()->pause();
	AudioEngine::pauseAll();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
	Director::getInstance()->resume();
	AudioEngine::resumeAll();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void AppDelegate::initBackMusic()
{
	for (unsigned short i = 0; i < 4; i++)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(s_back_music[i]);
	}
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(s_start_music);
}
void AppDelegate::initEffect()
{
	for (unsigned short i = 0; i < 14; i++)
	{
		AudioEngine::preload(s_fish_effect[i]);
	}
	AudioEngine::preload(s_fire);//预加载
	AudioEngine::preload(s_gold_effect);
	AudioEngine::preload(s_button);
	AudioEngine::preload(s_firefail);
	AudioEngine::preload(s_camera);
}
