#include "BackLayer.h"

BackLayer::BackLayer() 
{

}

BackLayer::~BackLayer()
{
	
}
bool BackLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//显示背景
	auto m_back = Sprite::create(s_back[2]);
	m_back->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_back->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(m_back, Z_0);
	//创建海星
	auto m_start = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_star), Rect(0, 0, 80, 82));
	m_start->setPosition(Vec2(origin.x + visibleSize.width / 4 - m_start->getContentSize().width / 2, origin.y + visibleSize.height / 2 + m_start->getContentSize().height));
	this->addChild(m_start, Z_1);
	auto animation = Animation::create();
	for (unsigned short i = 0; i < 24; i++)
	{
		animation->addSpriteFrameWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_star), Rect(i * 107, 0, 107, 107));
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	auto animate = Animate::create(animation);
	m_start->runAction(animate);

	//创建珊瑚
	auto m_coral = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_coral), Rect(0, 0, 295, 314));
	m_coral->setPosition(Vec2(origin.x + visibleSize.width /2, origin.y + visibleSize.height / 2+m_coral->getContentSize().height/2 ));
	this->addChild(m_coral, Z_1);
	auto c_animation = Animation::create();
	for (unsigned short i = 0; i <9; i++)
	{
		c_animation->addSpriteFrameWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(s_coral), Rect(i * 295, 0, 295, 314));
	}
	c_animation->setDelayPerUnit(0.1f);
	c_animation->setRestoreOriginalFrame(true);
	c_animation->setLoops(-1);
	auto c_animate = Animate::create(c_animation);
	m_coral->runAction(c_animate);


	return true;
}
