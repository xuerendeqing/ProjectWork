#include "UILayer.h"
#include "Config.h"
#include "CannonEffect.h"
#include "SceneShot.h"

UILayer::UILayer() :m_CannonType(GetIntegerFromXML("MyCannonType")), m_isTouch(false), m_isMove(false),
m_isLongPress(false), m_PressTime(0), m_TouchCounts(0), m_isAdd(true), m_isSub(true), m_isButton(true),
m_isChange(true), Cannon_Value(0), m_click_1(NULL), m_click_2(NULL), m_click_3(NULL), m_click_4(NULL), m_progress_1(NULL),
m_progress_2(NULL), m_progress_3(NULL), m_progress_4(NULL), m_isSkill_1(false), m_isSkill_2(false), m_isSkill_3(false), m_isSkill_4(false),
m_ProgressTimer_1(NULL), m_ProgressTimer_2(NULL), m_ProgressTimer_3(NULL), m_ProgressTimer_4(NULL), m_Model(COMMON_MODEL), m_startPoint(640,360),
p_islock(false), m_TouchModel(TOUCH_MODEL), m_TouchPoint(0, 0), total_points(0), kill_count(0), m_isKillAction(false)
{

}
UILayer::~UILayer()
{

}
bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//触摸事件
	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(UILayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(UILayer::onTouchEnded, this);
	m_listener->onTouchCancelled = CC_CALLBACK_2(UILayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	//创建炮台背景
	auto m_battery = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_battery_back));
	m_battery->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_battery->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y +m_battery->getContentSize().height/2));
	this->addChild(m_battery, Z_0);

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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_battery);
	

	//创建炮台加减菜单按钮
	auto m_add = MenuItemSprite::create(Sprite::createWithSpriteFrameName("addButton_01.png"), Sprite::createWithSpriteFrameName("addButton_02.png"), CC_CALLBACK_1(UILayer::addButton, this));
	m_add->setPosition(Vec2(m_battery->getPositionX()+m_add->getContentSize().width/2+25,m_battery->getPositionY()-10));
	//炮台减
	auto m_sub = MenuItemSprite::create(Sprite::createWithSpriteFrameName("subButton_01.png"), Sprite::createWithSpriteFrameName("subButton_02.png"), CC_CALLBACK_1(UILayer::subButton, this));
	m_sub->setPosition(Vec2(m_battery->getPositionX() - m_sub->getContentSize().width-10, m_battery->getPositionY() - 10));
	//创建炮台,传入炮台的类型
	m_Cannon = Cannon::create(this);
	m_Cannon->RotationToFire(m_startPoint);
	this->addChild(m_Cannon, Z_2);

	Cannon_Coin = Label::createWithCharMap(s_coin, 12, 20, '0');
	Cannon_Coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	Cannon_Coin->setAlignment(TextHAlignment::CENTER);
	Cannon_Value =Config::getInstance()->getCannonValue();//炮台初始化炮台开始的值
	char cannon_score[100];
	sprintf(cannon_score, "%d", Cannon_Value);
	Cannon_Coin->setString(cannon_score);
	Cannon_Coin->setPosition(Vec2(m_Cannon->getContentSize().width / 2, m_Cannon->getContentSize().height / 2 - Cannon_Coin->getContentSize().height + 2));
	m_Cannon->addChild(Cannon_Coin, Z_3);
	
	//创建点击特效
	m_TouchEffect = TouchEffect::create();
	this->addChild(m_TouchEffect,Z_0);

	//创建金币显示菜单
	auto m_coin = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buyCoinButton_01.png"), Sprite::createWithSpriteFrameName("buyCoinButton_02.png"), CC_CALLBACK_1(UILayer::CoinCallback, this));//回调函数,金币数量小于1000
	m_coin->setPosition(Vec2(origin.x+visibleSize.width/3-m_coin->getContentSize().width/2+20,origin.y+m_coin->getContentSize().height/2));
	Config::getInstance()->setGoldPoint(m_coin->getPosition());
	//创建金币的显示
	L_Coin = Label::createWithCharMap(s_coin, 12,20,'0');
	L_Coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	L_Coin->setAlignment(TextHAlignment::CENTER);
	L_Coin->setPosition(Vec2(m_coin->getContentSize().width-L_Coin->getContentSize().width-20,m_coin->getContentSize().height/2-5));
	m_coin->addChild(L_Coin, Z_1);
	//创建钻石显示菜单
	auto m_diamond = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buyDiamondButton_01.png"), Sprite::createWithSpriteFrameName("buyDiamondButton_02.png"), CC_CALLBACK_1(UILayer::DiamondCallback, this));//回调函数
	m_diamond->setPosition(Vec2(origin.x + visibleSize.width/2+m_diamond->getContentSize().width+65, origin.y + m_diamond->getContentSize().height / 2));
	Config::getInstance()->setDiamondPoint(m_diamond->getPosition());
	//创建钻石的显示
	L_Diamond = Label::createWithCharMap(s_coin, 12, 20, '0');
	L_Diamond->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	L_Diamond->setAlignment(TextHAlignment::CENTER);
	L_Diamond->setPosition(Vec2(m_diamond->getContentSize().width - L_Diamond->getContentSize().width - 20, m_diamond->getContentSize().height / 2-5));
	m_diamond->addChild(L_Diamond, Z_1);
	//创建相机菜单
	auto m_camera = MenuItemSprite::create(Sprite::createWithSpriteFrameName("camera_01.png"), Sprite::createWithSpriteFrameName("camera_02.png"), CC_CALLBACK_1(UILayer::CameraCallback, this));//回调函数,金币数量小于1000
	m_camera->setPosition(Vec2(origin.x+visibleSize.width-m_camera->getContentSize().width/2-10,origin.y+visibleSize.height/2-m_camera->getContentSize().height));

	auto menu = Menu::create(m_add, m_sub, m_coin, m_diamond, m_camera,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, Z_1);


	//创建头像显示背景的位置
	auto m_head_back = Sprite::createWithSpriteFrameName("headFrame.png");
	m_head_back->setPosition(Vec2(origin.x + m_head_back->getContentSize().width / 2 + 10, origin.y + visibleSize.height - m_head_back->getContentSize().height));
	this->addChild(m_head_back, Z_1);
	//创建头像精灵
	auto m_headSprite = Sprite::createWithSpriteFrameName("head008.png");
	m_headSprite->setPosition(Vec2(m_headSprite->getContentSize().width / 2, m_head_back->getContentSize().height / 2 + 25));
	m_head_back->addChild(m_headSprite, Z_1);//个体精灵一个触摸事件
	//创建显示联网的背景
	auto m_net_back = Sprite::createWithSpriteFrameName("onlineAward_bg.png");
	m_net_back->setPosition(Vec2(m_head_back->getContentSize().width / 2 + m_net_back->getContentSize().width / 2, m_head_back->getContentSize().height / 2+m_net_back->getContentSize().height+20));
	m_head_back->addChild(m_net_back, Z_1);//给精灵一个触摸事件，创建一个弹出层
	//检测是否有网络连接，网络有三个状态，连接中，未连接，连接超时
	
	//创建击杀的显示
	auto m_kill_back = Sprite::createWithSpriteFrameName("beijing_1.png");
	m_kill_back->setPosition(Vec2(origin.x+visibleSize.width-m_kill_back->getContentSize().width/2,origin.y+visibleSize.height/2+m_kill_back->getContentSize().height*2));
	this->addChild(m_kill_back, Z_1);
	//创建显示kill
	auto m_kill = Sprite::createWithSpriteFrameName("kill_1.png");
	m_kill->setPosition(Vec2(m_kill_back->getContentSize().width/2+m_kill->getContentSize().width/2,m_kill_back->getContentSize().height/2));
	m_kill_back->addChild(m_kill, Z_0);
	//创建击杀数字的显示
	L_Kill = Label::createWithCharMap(s_lianji_font, 30, 36, '0');
	L_Kill->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	L_Kill->setAlignment(TextHAlignment::CENTER);
	L_Kill->setPosition(Vec2(m_kill_back->getContentSize().width / 2 - L_Kill->getContentSize().width / 2, m_kill_back->getContentSize().height / 2));
	m_kill_back->addChild(L_Kill, Z_0);


	//创建极速技能按钮
	m_Skill_1 = cocos2d::ui::Button::create(s_speed_up, s_speed_down);
	m_Skill_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Skill_1->setSwallowTouches(true);
	m_Skill_1->setPosition(Vec2(origin.x + visibleSize.width - 130, origin.y + 45));
	m_Skill_1->addTouchEventListener(CC_CALLBACK_2(UILayer::SkillButtonCallback_1, this));
	this->addChild(m_Skill_1, Z_1);

	//创建锁定技能按钮
	m_Skill_2 = cocos2d::ui::Button::create(s_lock_up, s_lock_down);
	m_Skill_2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Skill_2->setPosition(Vec2(origin.x + visibleSize.width - 120, origin.y + 135));
	m_Skill_2->addTouchEventListener(CC_CALLBACK_2(UILayer::SkillButtonCallback_2, this));
	this->addChild(m_Skill_2, Z_1);

	//创建定屏技能按钮
	m_Skill_3 = cocos2d::ui::Button::create(s_suspend_up, s_suspend_up);
	m_Skill_3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Skill_3->setPosition(Vec2(origin.x + visibleSize.width - 47, origin.y + 79));
	m_Skill_3->addTouchEventListener(CC_CALLBACK_2(UILayer::SkillButtonCallback_3, this));
	this->addChild(m_Skill_3, Z_1);
	
	//狂暴技能
	m_Skill_4 = cocos2d::ui::Button::create(s_rage_up, s_rage_down);
	m_Skill_4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_Skill_4->setPosition(Vec2(origin.x + visibleSize.width -40, origin.y + 173));
	m_Skill_4->addTouchEventListener(CC_CALLBACK_2(UILayer::SkillButtonCallback_4, this));
	this->addChild(m_Skill_4, Z_1);
	
	this->schedule(CC_SCHEDULE_SELECTOR(UILayer::updateUI));

	return true;
}
bool UILayer::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		if (locationInNode.y < Director::getInstance()->getWinSize().height / 20)
		{
			return false;
		}
		m_TouchPoint = locationInNode;//锁定需要与鱼碰撞的位置点值
		m_startPoint = locationInNode;//大炮初始化朝向的点值
		m_TouchEffect->playEffect(locationInNode);
		m_Cannon->RotationToFire(m_startPoint);
		//触摸的时间长按
		m_isTouch = true;
		if (m_Model==COMMON_MODEL)//触摸屏幕，如果炮台的模式是普通模式，则执行长按事件或者是点击事件
		{
			this->schedule(CC_SCHEDULE_SELECTOR(UILayer::updateLongDelay), 0.17f);
			m_Cannon->CannonAction();//炮台在没有点击事件的开始点值时，调用极速模式会出现因为没有开始点值。而出现子弹移动错误
		}
		return true;
	}

	return false;
}

void UILayer::onTouchMoved(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	m_isMove = true;
	m_Cannon->RotationToFire(locationInNode);
}

void UILayer::onTouchEnded(Touch* touch, Event* event)
{
	//这个值用来判断锁定的触摸情况
	if (m_TouchModel==LOCK_MODEL)
	{
		p_islock = true;
	}
	if (m_Model== COMMON_MODEL)
	{
		m_isTouch = false;
		m_PressTime = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(UILayer::updateLongDelay));
		if (m_isLongPress)
		{
			m_TouchCounts = 0;
			m_isLongPress = false;
			return;
		}
	}
}
void UILayer::onTouchCancelled(Touch* touch, Event* event)
{

}
void UILayer::updateLongDelay(float dt)
{
	if (m_isTouch)
	{
		m_PressTime++;
		if (m_PressTime >=1)
		{
			m_isLongPress = true;
			this->onLongClick();
		}  
	}
	else
	{
		m_PressTime = 0;
	}
}
void UILayer::onLongClick()
{
	m_Cannon->CannonAction();
}
void UILayer::addButton(Ref* pSender)
{
	//增加炮台的类型
	if (m_isChange == true)
	{
		if (m_CannonType == 5)
		{
			m_isAdd = false;
		}
		else
		{
			++m_CannonType;
			m_isAdd = true;
			this->CannonEffect();
			if (m_CannonType < 6)
			{
				m_isSub = true;
				switch (m_CannonType)
				{
				case 1:
					m_isChange = false;
					m_Cannon->initWithSpriteFrameName("cannon002.png");
					m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
					m_Cannon->setScale(0.0f);
					Config::getInstance()->setCannonValue(100);
					m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
					break;
				case 2:
					m_isChange = false;
					m_Cannon->initWithSpriteFrameName("cannon003.png");
					m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
					m_Cannon->setScale(0.0f);
					Config::getInstance()->setCannonValue(150);
					m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
					break;
				case 3:
					m_isChange = false;
					m_Cannon->initWithSpriteFrameName("cannon004.png");
					m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
					m_Cannon->setScale(0.0f);
					Config::getInstance()->setCannonValue(200);
					m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
					break;
				case 4:
					m_isChange = false;
					m_Cannon->initWithSpriteFrameName("cannon005.png");
					m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
					m_Cannon->setScale(0.0f);
					Config::getInstance()->setCannonValue(250);
					m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
					break;
				case 5:
					m_isChange = false;
					m_Cannon->initWithSpriteFrameName("cannon006.png");
					m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
					m_Cannon->setScale(0.0f);
					Config::getInstance()->setCannonValue(300);
					m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
					m_isAdd = false;
					break;
				default:
					break;
				}
			}

			Cannon_Value = Config::getInstance()->getCannonValue();
			char cannon_score[100];
			sprintf(cannon_score, "%d", Cannon_Value);
			Cannon_Coin->setString(cannon_score);
			if (m_isButton == true)
			{
				m_isButton = false;
				if (!GetBooleanFromXML("MySound"))
				{
					auto m_audioID = AudioEngine::play2d(s_button, false, 1.0f);
					AudioEngine::setFinishCallback(m_audioID, CC_CALLBACK_0(UILayer::AudioButtonFinish, this));
				}

			}
		}
	}

}
void UILayer::subButton(Ref* pSender)
{
	//减小炮台的类型
	if (m_isChange == true)
	{
		if (m_CannonType == 0)
		{
			m_isSub = false;
		}
		else
		{
			m_CannonType--;
			m_isAdd = true;
			this->CannonEffect();
			switch (m_CannonType)
			{
			case 0:
				m_isChange = false;
				m_Cannon->initWithSpriteFrameName("cannon001.png");
				m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
				Config::getInstance()->setCannonValue(50);
				m_Cannon->setScale(0.0f);
				m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
				m_isSub = false;
				break;
			case 1:
				m_isChange = false;
				m_Cannon->initWithSpriteFrameName("cannon002.png");
				m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
				m_Cannon->setScale(0.0f);
				Config::getInstance()->setCannonValue(100);
				m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
				break;
			case 2:
				m_isChange = false;
				m_Cannon->initWithSpriteFrameName("cannon003.png");
				m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
				m_Cannon->setScale(0.0f);
				Config::getInstance()->setCannonValue(150);
				m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
				break;
			case 3:
				m_isChange = false;
				m_Cannon->initWithSpriteFrameName("cannon004.png");
				m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
				m_Cannon->setScale(0.0f);
				Config::getInstance()->setCannonValue(200);
				m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
				break;
			case 4:
				m_isChange = false;
				m_Cannon->initWithSpriteFrameName("cannon005.png");
				m_Cannon->setAnchorPoint(Vec2(0.5f, 0.4f));
				m_Cannon->setScale(0.0f);
				Config::getInstance()->setCannonValue(250);
				m_Cannon->runAction(Sequence::create(ScaleTo::create(0.3f, 1.0f), CallFunc::create(CC_CALLBACK_0(UILayer::CannonChangeCallBack, this)), NULL));
				break;
			default:
				break;
			}
			Cannon_Value = Config::getInstance()->getCannonValue();
			char cannon_score[100];
			sprintf(cannon_score, "%d", Cannon_Value);
			Cannon_Coin->setString(cannon_score);
			if (m_isButton == true)
			{
				m_isButton = false;
				if (!GetBooleanFromXML("MySound"))
				{
					auto m_audioID = AudioEngine::play2d(s_button, false, 1.0f);
					AudioEngine::setFinishCallback(m_audioID, CC_CALLBACK_0(UILayer::AudioButtonFinish, this));
				}
			}
		}
	}
}

void UILayer::AudioButtonFinish()
{
	m_isButton = true;
}
void UILayer::CannonEffect()
{
	auto m_CannonEffect = CannonEffect::create();
	m_CannonEffect->setPosition(m_Cannon->getPosition());
	this->addChild(m_CannonEffect, Z_3);
}
void UILayer::CannonChangeCallBack()
{
	m_isChange = true;
}
void UILayer::CoinCallback(Ref* pSender)
{

}
void UILayer::DiamondCallback(Ref* pSender)
{

}
void UILayer::CameraCallback(Ref* pSender)
{
	m_filename = "CaptureScreen.png";
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_filename = "CaptureScreen.png";
#endif
	utils::captureScreen(CC_CALLBACK_2(UILayer::afterCapture, this), m_filename);
	//开始拍照功能
	if (!GetBooleanFromXML("MySound"))
	{
		auto m_audioID = AudioEngine::play2d(s_camera, false, 1.0f);
		AudioEngine::setFinishCallback(m_audioID, CC_CALLBACK_0(UILayer::AudioButtonFinish, this));
	}

}
void UILayer::afterCapture(bool succeed, const std::string& outputFile)
{
	if (succeed)
	{
		//创建一个弹出层。实现在层中显示截图
		auto m_SceneShort = SceneShot::create(outputFile);
		this->addChild(m_SceneShort, Z_6);
		m_filename = outputFile;
	}
}
void UILayer::SkillButtonCallback_1(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_isSkill_1 = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_isSkill_1 = false;
		//按下的时候检测钻石的值，如果钻石满足，则开始执行
		if (Config::getInstance()->getDiamondValue()>=100)
		{
			this->SkillClickCallBack(SKILLE_BUTTON_1);
		}
		else
		{
			//否则出现提示钻石不足
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void UILayer::SkillButtonCallback_2(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_isSkill_2 = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_isSkill_2 = false;
		//按下的时候检测钻石的值，如果钻石满足，则开始执行
		if (Config::getInstance()->getDiamondValue() >= 200)
		{
			this->SkillClickCallBack(SKILLE_BUTTON_2);
		}
		else
		{
			//否则出现提示钻石不足
		}
		
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void UILayer::SkillButtonCallback_3(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_isSkill_3 = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_isSkill_3 = false;
		this->SkillClickCallBack(SKILLE_BUTTON_3);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void UILayer::SkillButtonCallback_4(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_isSkill_4 = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_isSkill_4 = false;
		this->SkillClickCallBack(SKILLE_BUTTON_4);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void UILayer::SkillClickCallBack(ButtonType m_buttonType)
{

	switch (m_buttonType)
	{
	case SKILLE_BUTTON_1:
		m_Skill_1->setTouchEnabled(false);
		//当技能按钮按下的时候，设置炮台进入极速模式
		m_Model = QUICK_MODEL;
		if (m_Model == QUICK_MODEL)
		{
			this->schedule(CC_SCHEDULE_SELECTOR(UILayer::CannonQuickModel), 0.12f);
		}
		//每按一次，扣减钻石
		Config::getInstance()->setSkillValue(100);
		m_click_1 = Sprite::create(s_speed_default);
		m_click_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_click_1->setPosition(m_Skill_1->getPosition());
		this->addChild(m_click_1, Z_1);
		m_ProgressTimer_1 = ProgressTimer::create(Sprite::create(s_speed_up));
		m_ProgressTimer_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_ProgressTimer_1->setPosition(m_Skill_1->getPosition());
		this->addChild(m_ProgressTimer_1, Z_1);
		m_ProgressTimer_1->setType(ProgressTimer::Type::RADIAL);
		m_ProgressTimer_1->runAction(Sequence::create(ProgressTo::create(10.0f, 100), CallFunc::create(CC_CALLBACK_0(UILayer::SkillFinishRemove_1, this)), NULL));
		break;
	case SKILLE_BUTTON_2:
		m_Skill_2->setTouchEnabled(false);
		//锁定的工能，即在按下锁定按钮后。开启锁定触摸模式
		//每按一次，扣减钻石
		Config::getInstance()->setSkillValue(200);
		m_TouchModel = LOCK_MODEL;
		Config::getInstance()->setFishLock(true);
		m_click_2 = Sprite::create(s_lock_default);
		m_click_2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_click_2->setPosition(m_Skill_2->getPosition());
		this->addChild(m_click_2, Z_1);
		m_ProgressTimer_2 = ProgressTimer::create(Sprite::create(s_lock_up));
		m_ProgressTimer_2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_ProgressTimer_2->setPosition(m_Skill_2->getPosition());
		this->addChild(m_ProgressTimer_2, Z_1);
		m_ProgressTimer_2->setType(ProgressTimer::Type::RADIAL);
		m_ProgressTimer_2->runAction(Sequence::create(ProgressTo::create(30.0f, 100), CallFunc::create(CC_CALLBACK_0(UILayer::SkillFinishRemove_2, this)), NULL));
		break;
	case SKILLE_BUTTON_3:
		m_Skill_3->setTouchEnabled(false);
		Config::getInstance()->setPauseFish(PAUSE_TRUE);//定屏的真假判断
		//创建一个显示冰冻的精灵
		m_Frozen = Sprite::create("ui/frozen.png");//这里的资源测试
		m_Frozen->setScale(3.3f);
		m_Frozen->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
		this->addChild(m_Frozen, Z_0);

		m_click_3 = Sprite::create(s_suspend_default);
		m_click_3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_click_3->setPosition(m_Skill_3->getPosition());
		this->addChild(m_click_3, Z_1);
	
		m_ProgressTimer_3 = ProgressTimer::create(Sprite::create(s_suspend_up));
		m_ProgressTimer_3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_ProgressTimer_3->setPosition(m_Skill_3->getPosition());
		this->addChild(m_ProgressTimer_3, Z_1);
		m_ProgressTimer_3->setType(ProgressTimer::Type::RADIAL);
		m_ProgressTimer_3->runAction(Sequence::create(ProgressTo::create(10.0f, 100), CallFunc::create(CC_CALLBACK_0(UILayer::SkillFinishRemove_3, this)), NULL));
		break;
	case SKILLE_BUTTON_4:
		m_Skill_4->setTouchEnabled(false);
		m_click_4 = Sprite::create(s_rage_default);
		m_click_4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_click_4->setPosition(m_Skill_4->getPosition());
		this->addChild(m_click_4, Z_1);
		m_ProgressTimer_4 = ProgressTimer::create(Sprite::create(s_rage_up));
		m_ProgressTimer_4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		m_ProgressTimer_4->setPosition(m_Skill_4->getPosition());
		this->addChild(m_ProgressTimer_4, Z_1);
		m_ProgressTimer_4->setType(ProgressTimer::Type::RADIAL);
		m_ProgressTimer_4->runAction(Sequence::create(ProgressTo::create(3.0f, 100), CallFunc::create(CC_CALLBACK_0(UILayer::SkillFinishRemove_4, this)), NULL));
	default:
		break;
	}
}
void UILayer::SkillFinishRemove_1()
{
	m_Model = COMMON_MODEL;//当极速模式执行完后，将炮台状态设置为普通模式
	this->unschedule(CC_SCHEDULE_SELECTOR(UILayer::CannonQuickModel));//停止极速模式的调用
	m_Skill_1->setTouchEnabled(true);
	this->removeChild(m_click_1);
	this->removeChild(m_ProgressTimer_1);
}
void UILayer::SkillFinishRemove_2()
{
	//锁定结束后，改变触摸的模式为普通模式
	m_TouchModel =TOUCH_MODEL;
	Config::getInstance()->setFishLock(false);
	m_Skill_2->setTouchEnabled(true);
	this->removeChild(m_click_2);
	this->removeChild(m_ProgressTimer_2);
}
void UILayer::SkillFinishRemove_3()//冰冻技能
{
	//显示时间到了后删除冰冻精灵
	m_Frozen->removeFromParentAndCleanup(true);
	Config::getInstance()->setPauseFish(PAUSE_FALSE);
	m_Skill_3->setTouchEnabled(true);
	this->removeChild(m_click_3);
	this->removeChild(m_ProgressTimer_3);
}
void UILayer::SkillFinishRemove_4()
{
	m_Skill_4->setTouchEnabled(true);
	this->removeChild(m_click_4);
	this->removeChild(m_ProgressTimer_4);
}
void UILayer::CannonQuickModel(float dt)//大炮的极速发射
{
	m_Cannon->CannonAction();
}
void UILayer::updateUI(float dt)
{
	//分数的更新
	total_points = Config::getInstance()->getCoinValue();
	char score[100];
	sprintf(score, "%d", total_points);//这里存在长整型与整型的问题
	L_Coin->setString(score);
	//钻石的更新
	diamond_points = Config::getInstance()->getDiamondValue();
	char diamon_score[100];
	sprintf(diamon_score, "%d", diamond_points);
	L_Diamond->setString(diamon_score);
	//连续击杀次数的显示
	kill_count = Config::getInstance()->getKillValue();
	char kill_score[100];
	sprintf(kill_score, "%d", kill_count);
	L_Kill->setString(kill_score);
	if (Config::getInstance()->getKillShow()==true)//这里暂时使用这种方式。后续的扩展使用类似的“大杀特杀”，“大杀四方”等类似的用勋章图标的方式标记显示。以获取kill_count击杀鱼的个数来判断是哪一种
	{
		Config::getInstance()->setKillShow(false);
		L_Kill->setScale(2.0f);
		L_Kill->runAction(ScaleTo::create(0.1f, 1.0f, 1.0f));
	}
	//游戏开始10秒后创建任务显示，在这里扩展





}
