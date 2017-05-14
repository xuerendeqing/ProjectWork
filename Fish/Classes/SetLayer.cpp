#include "SetLayer.h"
#include "Config.h"

SetLayer::SetLayer()
{

}

SetLayer::~SetLayer()
{

}
bool SetLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto m_left = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_set_back));
	m_left->setPosition(Vec2(origin.x+visibleSize.width/2-m_left->getContentSize().width/2,origin.y+visibleSize.height/2));
	this->addChild(m_left,Z_0);
	auto m_right= Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_set_back));
	m_right->setFlippedX(true);
	m_right->setPosition(Vec2(origin.x + visibleSize.width / 2+m_right->getContentSize().width/2, origin.y + visibleSize.height / 2));
	this->addChild(m_right, Z_0);
	//创建显示钻石
	auto m_Gem = Sprite::createWithSpriteFrameName("settingGem.png");
	m_Gem->setPosition(Vec2(origin.x+visibleSize.width/2,m_left->getContentSize().height+m_Gem->getContentSize().height/2));
	this->addChild(m_Gem, Z_1);
	//创建设置
	auto m_text= Sprite::createWithSpriteFrameName("text_setting.png");
	m_text->setPosition(Vec2(origin.x + visibleSize.width / 2, m_left->getContentSize().height - m_text->getContentSize().height / 2));
	this->addChild(m_text, Z_1);
	//创建图标
	auto m_mseicon = Sprite::createWithSpriteFrameName("mseicon.png");
	m_mseicon->setPosition(Vec2(m_left->getContentSize().width/2,m_left->getContentSize().height/2));
	m_left->addChild(m_mseicon,Z_1);
	//创建字体
	auto m_musice= Sprite::createWithSpriteFrameName("text_m.png");
	m_musice->setPosition(Vec2(m_left->getContentSize().width / 2 + m_musice->getContentSize().width, m_left->getContentSize().height / 2 + m_musice->getContentSize().height * 2));
	m_left->addChild(m_musice, Z_1);
	//创建开关按钮
	auto m_music_control = ControlSwitch::create(Sprite::create(s_mask), Sprite::create(s_on), Sprite::create(s_off), Sprite::create(s_adjust), Label::createWithSystemFont("ON", "Arial", 20), Label::createWithSystemFont("OFF", "Arial", 20));
	m_music_control->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + m_music_control->getContentSize().height * 2 - 10));
	this->addChild(m_music_control, Z_1);
	if (!GetBooleanFromXML("MyMusic"))
	{
		m_music_control->setOn(true, false);
	}
	else
	{
		m_music_control->setOn(false, false);
	}
	m_music_control->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::MusicCallback), Control::EventType::VALUE_CHANGED);

	auto m_sound= Sprite::createWithSpriteFrameName("text_s.png");
	m_sound->setPosition(Vec2(m_left->getContentSize().width / 2+m_sound->getContentSize().width, m_left->getContentSize().height / 2));
	m_left->addChild(m_sound, Z_1);
	auto m_sound_control = ControlSwitch::create(Sprite::create(s_mask), Sprite::create(s_on), Sprite::create(s_off), Sprite::create(s_adjust), Label::createWithSystemFont("ON", "Arial", 20), Label::createWithSystemFont("OFF", "Arial", 20));
	m_sound_control->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	if (!GetBooleanFromXML("MySound"))
	{
		m_sound_control->setOn(true, false);
	}
	else
	{
		m_sound_control->setOn(false, false);
	}
	this->addChild(m_sound_control, Z_1);
	m_sound_control->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::SoundCallback), Control::EventType::VALUE_CHANGED);

	auto m_effect = Sprite::createWithSpriteFrameName("text_e.png");
	m_effect->setPosition(Vec2(m_left->getContentSize().width / 2+m_effect->getContentSize().width, m_left->getContentSize().height / 2-m_effect->getContentSize().height*2));
	m_left->addChild(m_effect, Z_1);
	//后面扩展
	auto m_effect_control = ControlSwitch::create(Sprite::create(s_mask), Sprite::create(s_on), Sprite::create(s_off), Sprite::create(s_adjust), Label::createWithSystemFont("ON", "Arial", 20), Label::createWithSystemFont("OFF", "Arial", 20));
	m_effect_control->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2-m_effect_control->getContentSize().height*2+10));
	this->addChild(m_effect_control, Z_1);
	m_effect_control->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::EffectCallback), Control::EventType::VALUE_CHANGED);
	//创建关闭菜单
	auto p_close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("close_up.png"), Sprite::createWithSpriteFrameName("close_down.png"), CC_CALLBACK_1(SetLayer::SetCloseCallback, this));
	p_close->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_close->setPosition(Vec2(m_right->getContentSize().width-p_close->getContentSize().width/2, m_right->getContentSize().height-p_close->getContentSize().height));

	auto menu = Menu::create(p_close, NULL);
	menu->setPosition(Vec2::ZERO);
	m_right->addChild(menu, Z_2);

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

	this->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 0.9f), ScaleTo::create(0.1f, 1.0f), NULL));
	return true;
}
void SetLayer::MusicCallback(Ref* sender, Control::EventType controlEvent)
{
	if (controlEvent == Control::EventType::VALUE_CHANGED)
	{
		if (!GetBooleanFromXML("MyMusic"))
		{
			SetBooleanToXML("MyMusic",true);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			SetBooleanToXML("MyMusic",false);
			SimpleAudioEngine::getInstance()->playBackgroundMusic(s_start_music,true);//因为这里需要读取配置文件中的键值，初始化后无法在读取第二次开始层中的背景音乐。所以这里再次重新启动播放
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
}
void SetLayer::SoundCallback(Ref* sender, Control::EventType controlEvent)
{
	if (controlEvent == Control::EventType::VALUE_CHANGED)
	{
		if (!GetBooleanFromXML("MySound"))
		{
			SetBooleanToXML("MySound", true);
			AudioEngine::pauseAll();
		}
		else
		{
			SetBooleanToXML("MySound", false);
			AudioEngine::resumeAll();
		}
	}
}
void SetLayer::EffectCallback(Ref* sender, Control::EventType controlEvent)
{
	
}
void SetLayer::SetCloseCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}