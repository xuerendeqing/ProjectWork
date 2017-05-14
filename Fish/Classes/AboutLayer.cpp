#include "AboutLayer.h"


AboutLayer::AboutLayer()
{

}
AboutLayer::~AboutLayer()
{

}
bool AboutLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//创建关于层背景
	auto m_About_back = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("9Box.png");
	m_About_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_About_back->setScale9Enabled(true);
	m_About_back->setContentSize(Size(m_About_back->getContentSize().width *4, m_About_back->getContentSize().height *3));
	this->addChild(m_About_back, Z_0);
	//创建背景上下花边
	auto m_decorate_up = Sprite::createWithSpriteFrameName("decorate_up.png");
	m_decorate_up->setPosition(m_About_back->getContentSize().width/2,m_About_back->getContentSize().height+m_decorate_up->getContentSize().height/2);
	m_About_back->addChild(m_decorate_up, Z_1);

	auto m_decorate_down = Sprite::createWithSpriteFrameName("decorate_down.png");
	m_decorate_down->setPosition(m_About_back->getContentSize().width / 2,-m_decorate_down->getContentSize().height/2);
	m_About_back->addChild(m_decorate_down, Z_1);
	//创建菜单按钮
	//新浪
	auto p_sina = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonUp.png"), Sprite::createWithSpriteFrameName("buttonDown.png"), CC_CALLBACK_1(AboutLayer::SinaCallback, this));
	p_sina->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_sina->setPosition(Vec2(m_About_back->getContentSize().width / 2, m_About_back->getContentSize().height-p_sina->getContentSize().height));
	//创建显示精灵
	auto m_sin = Sprite::createWithSpriteFrameName("sina.png");
	m_sin->setPosition(Vec2(p_sina->getContentSize().width/2,p_sina->getContentSize().height/2));
	p_sina->addChild(m_sin, Z_1);
	//关于
	auto p_about = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonUp.png"), Sprite::createWithSpriteFrameName("buttonDown.png"), CC_CALLBACK_1(AboutLayer::AboutCallback, this));
	p_about->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_about->setPosition(Vec2(m_About_back->getContentSize().width / 2, m_About_back->getContentSize().height / 2));
	//创建显示精灵
	auto m_bout = Sprite::createWithSpriteFrameName("about.png");
	m_bout->setPosition(Vec2(p_about->getContentSize().width / 2, p_about->getContentSize().height / 2));
	p_about->addChild(m_bout, Z_1);
	//退出
	auto p_exit = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonUp.png"), Sprite::createWithSpriteFrameName("buttonDown.png"), CC_CALLBACK_1(AboutLayer::ExitCallBack, this));
	p_exit->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_exit->setPosition(Vec2(m_About_back->getContentSize().width / 2, m_About_back->getContentSize().height /5));
	//创建显示精灵
	auto m_exit = Sprite::createWithSpriteFrameName("exit.png");
	m_exit->setPosition(Vec2(p_exit->getContentSize().width / 2, p_exit->getContentSize().height / 2));
	p_exit->addChild(m_exit, Z_1);
	//创建关闭菜单
	auto p_close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("close_up.png"), Sprite::createWithSpriteFrameName("close_down.png"), CC_CALLBACK_1(AboutLayer::CloseCallback, this));
	p_close->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	p_close->setPosition(Vec2(m_About_back->getContentSize().width, m_About_back->getContentSize().height-5));

	auto menu = Menu::create(p_sina, p_about, p_exit, p_close, NULL);
	menu->setPosition(Vec2::ZERO);
	m_About_back->addChild(menu, Z_2);

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
void AboutLayer::CloseCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}
void AboutLayer::AboutCallback(Ref* pSender)
{
	//创建关于层
}
void AboutLayer::SinaCallback(Ref* pSender)
{
	//创建新浪微博分享功能
}
void AboutLayer::ExitCallBack(Ref* pSender)
{
	//退出游戏
	Director::getInstance()->end();
}