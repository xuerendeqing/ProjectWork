#include "TouchEffect.h"


TouchEffect::TouchEffect()
{

}
TouchEffect::~TouchEffect()
{

}
bool TouchEffect::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	for (short int i =1; i <=3; i++)
	{
		auto frameName = String::createWithFormat("water00%d.png", i);
		auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		if (pFrame)
		{
			m_effectArray.pushBack(pFrame);
		}
	}
	return true;
}
void TouchEffect::playEffect(const Vec2& point)
{
	this->setVisible(true);
	this->setPosition(point);
	this->stopAllActions();
	this->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(m_effectArray, 0.05f)), CallFunc::create(CC_CALLBACK_0(TouchEffect::setHide, this)), NULL));
}

void TouchEffect::setHide()
{
	this->setVisible(false);
}