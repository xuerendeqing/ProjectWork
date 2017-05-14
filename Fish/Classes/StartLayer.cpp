#include "StartLayer.h"
#include "GameLayer.h"
#include "Config.h"
#include "CustomerService.h"
#include "AboutLayer.h"
#include "SetLayer.h"

StartLayer::StartLayer() :runtime(0), m_touchTime(0), m_isService(true)
{

}
StartLayer::~StartLayer()
{
	this->unschedule(CC_SCHEDULE_SELECTOR(StartLayer::updateWater));
}
Scene* StartLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = StartLayer::create();

	scene->addChild(layer);

	return scene;
}

bool StartLayer::init()//注意第一次进入程序时的，在开始界面停止游戏，会出现金币数量无法保存。是因为程序结束的时候数据没有写入xml文件
{
	if (!Layer::init())
	{
		return false;
	}

	//测试数据包的
	SetIntegerToXML("MyGold",1000000);
	SetIntegerToXML("MyDiamond", 1000000);
	//在这里释放加载场景中的图片资源
	SpriteFrameCache::getInstance()->removeSpriteFrameByName(s_load_plist);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_load_fish);
	Director::getInstance()->getTextureCache()->removeTextureForKey(s_load);
	
	//加载plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("water/water.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery/cannon.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet/Bullet.plist");//加载子弹
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet/net.plist");//加载子弹
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery/CannonEffectFrame.plist");//加载炮火特效
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery/WeaponSwitch.plist");//加载炮的转换特效
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/touch.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gold/Gold.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/ui.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/head.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/lianji0.plist");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("start/start.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("start/achievement.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("start/achievement_word.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("start/seting.plist");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pao_1.plist");//测试用

	for (unsigned short i = 0; i < 18; i++)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_fish_plist[i]);
	}

	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(StartLayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(StartLayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(StartLayer::onTouchEnded, this);
	m_listener->onTouchCancelled = CC_CALLBACK_2(StartLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(StartLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	m_ripple = RipplePge::create(s_start_back);
	m_ripple->setAnchorPoint(Vec2(0, 0));
	m_ripple->setPosition(Vec2(origin.x, origin.y));
	this->addChild(m_ripple, Z_0);
	//创建logo
	auto m_logo = Sprite::createWithSpriteFrameName("telecom_logo.png");
	m_logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_logo->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - m_logo->getContentSize().height / 2-30));
	this->addChild(m_logo, Z_1);
	//创建登入菜单
	auto m_start = MenuItemSprite::create(Sprite::createWithSpriteFrameName("start_up.png"), Sprite::createWithSpriteFrameName("start_down.png"), CC_CALLBACK_1(StartLayer::startGameCallBack, this));
	m_start->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_start->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	//金币的菜单
	auto m_coinButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("diamondBg.png"), Sprite::createWithSpriteFrameName("coinBg.png"), CC_CALLBACK_1(StartLayer::GameCoinCallBack, this));
	m_coinButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_coinButton->setPosition(Vec2(origin.x + visibleSize.width-m_coinButton->getContentSize().width/2-10, origin.y + visibleSize.height-m_coinButton->getContentSize().height));
	auto p_coin = Sprite::createWithSpriteFrameName("coin.png");
	p_coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_coin->setPosition(Vec2(m_coinButton->getContentSize().width/2-p_coin->getContentSize().width-8,m_coinButton->getContentSize().height/2+3));
	m_coinButton->addChild(p_coin, Z_1);

	auto m_showScore = Label::createWithCharMap(s_notice, 10,14, '0');//这里显示金币数量
	m_showScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	m_showScore->setScale(1.5f);
	m_showScore->setAlignment(TextHAlignment::CENTER);
	char showscore[100];
	sprintf(showscore, "%d", GetIntegerFromXML("MyGold"));
	m_showScore->setString(showscore);
	m_showScore->setPosition(Vec2(m_coinButton->getContentSize().width-20, m_coinButton->getContentSize().height / 2+3));
	m_coinButton->addChild(m_showScore,Z_1);
	
	//钻石菜单
	auto m_diamondButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("diamondBg.png"), Sprite::createWithSpriteFrameName("coinBg.png"), CC_CALLBACK_1(StartLayer::GameDiamonCallBack, this));
	m_diamondButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_diamondButton->setPosition(Vec2(origin.x + visibleSize.width - m_diamondButton->getContentSize().width / 2 - 10, origin.y + visibleSize.height - m_diamondButton->getContentSize().height / 2 - 70));
	auto p_diam= Sprite::createWithSpriteFrameName("diamond.png");
	p_diam->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_diam->setPosition(Vec2(m_diamondButton->getContentSize().width / 2 - p_diam->getContentSize().width -8, m_diamondButton->getContentSize().height / 2 + 3));
	m_diamondButton->addChild(p_diam, Z_1);
	auto m_showDiamon= Label::createWithCharMap(s_notice,10,14, '0');//显示钻石数量
	m_showDiamon->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	m_showDiamon->setScale(1.5f);
	m_showDiamon->setAlignment(TextHAlignment::CENTER);
	char showdiamon[100];
	sprintf(showdiamon, "%d", GetIntegerFromXML("MyDiamond"));
	m_showDiamon->setString(showdiamon);
	m_showDiamon->setPosition(Vec2(m_diamondButton->getContentSize().width-20, m_diamondButton->getContentSize().height / 2+3));
	m_diamondButton->addChild(m_showDiamon, Z_1);
	
	//创建设置菜单
	auto m_Set = MenuItemSprite::create(Sprite::createWithSpriteFrameName("set_up.png"), Sprite::createWithSpriteFrameName("set_down.png"), CC_CALLBACK_1(StartLayer::GameSetCallback, this));
	m_Set->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Set->setPosition(Vec2(origin.x + m_Set->getContentSize().width / 2+5, origin.y + m_Set->getContentSize().height/2));
	//创建关于菜单
	auto m_About = MenuItemSprite::create(Sprite::createWithSpriteFrameName("weibo_up.png"), Sprite::createWithSpriteFrameName("weibo_down.png"), CC_CALLBACK_1(StartLayer::GameAboutCallback, this));
	m_About->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_About->setPosition(Vec2(origin.x + visibleSize.width - m_About->getContentSize().width / 2 - 5, origin.y + m_About->getContentSize().height/2));
	//创建客服菜单
	m_Service = Sprite::createWithSpriteFrameName("btn_Service.png");
	m_Service->setAnchorPoint(Vec2(0.5f,0.3f));
	m_Service->setPosition(Vec2(origin.x+visibleSize.width-m_Service->getContentSize().width/2,origin.y+m_Service->getContentSize().height+15));
	this->addChild(m_Service, Z_1);
	m_Service->runAction(RepeatForever::create(Sequence::create(EaseSineOut::create(RotateBy::create(1.0f,15.0f)), EaseSineIn::create(RotateBy::create(1.0f, -15.0f)), EaseSineOut::create(RotateBy::create(1.0f, -15.0f)), EaseSineIn::create(RotateBy::create(1.0f, 15.0f)), NULL)));
	//注册触摸事件
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			if (m_isService==true)
			{
				m_isService = false;
				m_Service->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), CallFunc::create(CC_CALLBACK_0(StartLayer::ServiceCallback, this)), NULL));
			}
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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_Service);

	//创建猫咪的眼睛
	m_Eye = Sprite::createWithSpriteFrameName("eyes.png");
	m_Eye->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Eye->setPosition(Vec2(m_Service->getContentSize().width/2,m_Service->getContentSize().height/2+m_Eye->getContentSize().height/2));
	m_Service->addChild(m_Eye, Z_2);
	m_Eye->runAction(RepeatForever::create(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(StartLayer::EyeScaleYCallback, this)), DelayTime::create(0.2f), CallFunc::create(CC_CALLBACK_0(StartLayer::EyeScaleCallback, this)), NULL)));
	//显示客服字体
	auto m_serFont = Sprite::createWithSpriteFrameName("text_service.png");
	m_serFont->setPosition(Vec2(origin.x + visibleSize.width - m_serFont->getContentSize().width / 2 -35, origin.y + m_serFont->getContentSize().height + 80));
	this->addChild(m_serFont, Z_1);

	auto menu = Menu::create(m_start, m_coinButton, m_diamondButton, m_Set, m_About, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, Z_2);
	//创建水泡泡
	auto m_bubble_1 = ParticleSystemQuad::create("particles/bubble.plist");
	m_bubble_1->setTexture(Director::getInstance()->getTextureCache()->addImage("particles/bubble.png"));
	m_bubble_1->setPosition(Vec2(origin.x +m_bubble_1->getContentSize().width+150, origin.y + m_bubble_1->getContentSize().height+100));
	this->addChild(m_bubble_1, Z_1);

	//创建水泡泡
	auto m_bubble_2 = ParticleSystemQuad::create("particles/bubble.plist");
	m_bubble_2->setTexture(Director::getInstance()->getTextureCache()->addImage("particles/bubble.png"));
	m_bubble_2->setPosition(Vec2(origin.x + visibleSize.width- m_bubble_2->getContentSize().width-150, origin.y + m_bubble_2->getContentSize().height));
	this->addChild(m_bubble_2, Z_1);

	this->schedule(CC_SCHEDULE_SELECTOR(StartLayer::updateWater));
	//开始背景音乐
	if (!GetBooleanFromXML("MyMusic"))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(s_start_music, true);
	}


	return true;
}
bool StartLayer::onTouchBegan(Touch* touch, Event* event)
{
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		runtime = 0.1f;
		m_ripple->addRipple(locationInNode,4.0f);
		return true;
	}
	return false;
}

void StartLayer::onTouchMoved(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	if (runtime >= 0.1f)
	{
		runtime -= 0.1f;
		m_ripple->addRipple(locationInNode,4.0f);//这里添加一个波纹，即波纹显示的位置
	}
	
}
void StartLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	m_ripple->addRipple(locationInNode, 4.0f);
}
void StartLayer::onTouchCancelled(Touch* touch, Event* event)
{

}
void StartLayer::updateWater(float dt)
{
	m_touchTime += dt;
	if (m_touchTime>=3.0f)
	{
		m_ripple->addRipple(Vec2((origin.x + visibleSize.width)*CCRANDOM_0_1(), (origin.y + visibleSize.height)*CCRANDOM_0_1()), 4.0f);
		m_touchTime = 0;
	}
	runtime += dt;
	m_ripple->update(dt);
}
void StartLayer::startGameCallBack(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GameLayer::createScene()));
	this->removeFromParentAndCleanup(true);
}
void StartLayer::GameCoinCallBack(Ref* pSender)
{
	log("666666666666666");
}
void StartLayer::GameDiamonCallBack(Ref* pSender)
{
	log("555555555555555");
}
void StartLayer::GameSetCallback(Ref* pSender)
{
	if (!GetBooleanFromXML("MySound"))
	{
		AudioEngine::play2d(s_button, false, 1.0f);
	}
	auto m_Setting = SetLayer::create();
	this->addChild(m_Setting, Z_2);
}

void StartLayer::GameAboutCallback(Ref* pSender)
{
	//游戏分享和关于菜单
	
	if (!GetBooleanFromXML("MySound"))
	{
		AudioEngine::play2d(s_button, false, 1.0f);
	}
	auto m_About = AboutLayer::create();
	this->addChild(m_About, Z_2);
}
void StartLayer::EyeScaleYCallback()
{
	m_Eye->setScaleY(0.0f);
}
void StartLayer::EyeScaleCallback()
{
	m_Eye->setScaleY(1.0f);
}
void StartLayer::ServiceCallback()
{
	
	if (!GetBooleanFromXML("MySound"))
	{
		AudioEngine::play2d(s_button, false, 1.0f);
	}
	auto m_CustomerService = CustomerService::create();
	this->addChild(m_CustomerService,Z_2);
	m_isService = true;
}
void StartLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
