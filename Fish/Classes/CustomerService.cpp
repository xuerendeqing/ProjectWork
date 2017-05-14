#include "CustomerService.h"

CustomerService::CustomerService()
{

}

CustomerService::~CustomerService()
{

}
bool CustomerService::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//读取客服配置文件
	auto message = Dictionary::createWithContentsOfFile("config/ServiceFile.xml");
	
	//创建客服层背景
	auto m_service_back=cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("bg.png");
	m_service_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_service_back->setScale9Enabled(true);
	m_service_back->setContentSize(Size(m_service_back->getContentSize().width *9, m_service_back->getContentSize().height*7));
	this->addChild(m_service_back,Z_0);

	const char *m_Title = ((__String*)message->valueForKey("ServiceTitle"))->getCString();
	const char *m_PhoneTitle =((__String*)message->valueForKey("Phone"))->getCString();
	const char *m_QQTitle = ((__String*)message->valueForKey("QQ"))->getCString();
	const char *m_WenXinTitle = ((__String*)message->valueForKey("WenXin"))->getCString();
	const char *m_MesageTitle = ((__String*)message->valueForKey("DisplayMesage"))->getCString();

	auto p_Title = Label::createWithSystemFont(m_Title, "Arial",40, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	p_Title->setPosition(Vec2(m_service_back->getContentSize().width / 2-p_Title->getContentSize().width, m_service_back->getContentSize().height-p_Title->getContentSize().height-10));
	m_service_back->addChild(p_Title,Z_1);

	//分界线
	auto m_up_line = Sprite::createWithSpriteFrameName("line.png");
	m_up_line->setPosition(Vec2(m_service_back->getContentSize().width / 2, m_service_back->getContentSize().height / 2 + 120));
	m_service_back->addChild(m_up_line, Z_1);
	//分界线
	auto m_down_line = Sprite::createWithSpriteFrameName("line.png");
	m_down_line->setPosition(Vec2(m_service_back->getContentSize().width / 2, m_service_back->getContentSize().height / 2-120));
	m_service_back->addChild(m_down_line, Z_1);
	//电话图标
	auto m_Phone = Sprite::createWithSpriteFrameName("ico_tel.png");
	m_Phone->setPosition(Vec2(m_service_back->getContentSize().width / 2-200, m_service_back->getContentSize().height / 2+80));
	m_service_back->addChild(m_Phone,Z_1);
	auto p_PhoneTitle = Label::createWithSystemFont(m_PhoneTitle, "Arial", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	p_PhoneTitle->setPosition(Vec2(m_service_back->getContentSize().width / 2 -25, m_service_back->getContentSize().height / 2 + 80));
	m_service_back->addChild(p_PhoneTitle, Z_1);
	//QQ
	auto m_QQ = Sprite::createWithSpriteFrameName("ico_qq.png");
	m_QQ->setPosition(Vec2(m_service_back->getContentSize().width / 2-200, m_service_back->getContentSize().height/2));
	m_service_back->addChild(m_QQ, Z_1);
	auto p_QQTitle = Label::createWithSystemFont(m_QQTitle, "Arial", 24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	p_QQTitle->setPosition(Vec2(m_service_back->getContentSize().width / 2-45, m_service_back->getContentSize().height/2));
	m_service_back->addChild(p_QQTitle, Z_1);
	//微信
	auto m_Weixin= Sprite::createWithSpriteFrameName("ico_wx.png");
	m_Weixin->setPosition(Vec2(m_service_back->getContentSize().width / 2-200, m_service_back->getContentSize().height / 2-80));
	m_service_back->addChild(m_Weixin, Z_1);
	auto p_WeiXinTitle = Label::createWithSystemFont(m_WenXinTitle, "Arial",24, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	p_WeiXinTitle->setPosition(Vec2(m_service_back->getContentSize().width / 2- 25, m_service_back->getContentSize().height / 2-80));
	m_service_back->addChild(p_WeiXinTitle, Z_1);
	//确定按钮
	m_Confirm = Sprite::createWithSpriteFrameName("btn_ok.png");
	m_Confirm->setPosition(Vec2(m_service_back->getContentSize().width / 2, m_service_back->getContentSize().height /6-m_Confirm->getContentSize().height/2-10));
	m_service_back->addChild(m_Confirm, Z_1);
	auto p_MesageTitle = Label::createWithSystemFont(m_MesageTitle, "Arial", 17, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
	p_MesageTitle->setColor(Color3B::YELLOW);
	p_MesageTitle->setPosition(Vec2(m_service_back->getContentSize().width / 2, m_service_back->getContentSize().height /5-p_MesageTitle->getContentSize().height/2));
	m_service_back->addChild(p_MesageTitle, Z_1);
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
			m_Confirm->setOpacity(125);
			return true;
		}
		return false;
	};

	listener1->onTouchMoved = [](Touch* touch, Event* event)
	{

	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{
		//结束客服界面
		m_Confirm->setOpacity(255);
		this->removeAllChildrenWithCleanup(true);
		this->removeFromParentAndCleanup(true);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, m_Confirm);

	//触摸事件
	auto m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(CustomerService::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(CustomerService::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(CustomerService::onTouchEnded, this);
	m_listener->onTouchCancelled = CC_CALLBACK_2(CustomerService::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	this->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 0.9f), ScaleTo::create(0.1f, 1.0f),NULL));

	return true;
}
bool CustomerService::onTouchBegan(Touch* touch, Event* event)
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
}

void CustomerService::onTouchMoved(Touch* touch, Event* event)
{

}
void CustomerService::onTouchEnded(Touch* touch, Event* event)
{
	
}
void CustomerService::onTouchCancelled(Touch* touch, Event* event)
{

}