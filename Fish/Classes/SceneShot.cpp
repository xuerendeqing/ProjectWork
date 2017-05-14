#include "SceneShot.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android-studio/app/jni/hellocpp/GameInvoking.h"
#endif

SceneShot::SceneShot()
{

}

SceneShot::~SceneShot()
{

}
SceneShot* SceneShot::create(const std::string& strPath)
{
	auto m_shot = new (std::nothrow)SceneShot();
	if (m_shot&&m_shot->init(strPath))
	{
		m_shot->autorelease();
		return m_shot;
	}
	else
	{
		CC_SAFE_DELETE(m_shot);
		return NULL;
	}
}

bool SceneShot::init(const std::string& strPath)
{
	if (!Layer::init())
	{
		return false;
	}
	m_Path = strPath.c_str();

	auto m_screen = Sprite::create(strPath);
	m_screen->setPosition(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
	this->addChild(m_screen,Z_1);
	m_screen->setScale(0.7f); //放缩
	m_screen->setRotation(CCRANDOM_0_1()*15);
	
	//这里暂时读取资源
	auto m_callback = MenuItemSprite::create(Sprite::create("ui/yBack_up.png"), Sprite::create("ui/yBack_down.png"), CC_CALLBACK_1(SceneShot::CloseShotCallBack, this));
	m_callback->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_callback->setPosition(Vec2(m_callback->getContentSize().width / 2,m_screen->getContentSize().height-m_callback->getContentSize().height/2));

	//这里暂时读取资源
	auto m_share = MenuItemSprite::create(Sprite::create("ui/yCamera_up.png"), Sprite::create("ui/yCamera_down.png"), CC_CALLBACK_1(SceneShot::OpenShare, this));
	m_share->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_share->setPosition(Vec2(m_screen->getContentSize().width-m_share->getContentSize().width/2,m_share->getContentSize().height/2));

	auto menu = Menu::create(m_callback,m_share, NULL);
	menu->setPosition(Vec2::ZERO);
	m_screen->addChild(menu, Z_2);

	//注册触摸事件
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			
			return true;
		}
		return false;
	};

	listener1->onTouchMoved = [](Touch* touch, Event* event)
	{

	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}
void SceneShot::CloseShotCallBack(Ref* pSender)
{
	//这里调用返回
	this->removeFromParentAndCleanup(true);
}
void SceneShot::OpenShare(Ref* pSender)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	createImagePath("xiaodong","exit");
#endif
}