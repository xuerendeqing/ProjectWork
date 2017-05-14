#include "CannonEffect.h"

CannonEffect::CannonEffect() :e_delay(0.08f)
{

}


CannonEffect::~CannonEffect()
{
	AnimationCache::getInstance()->removeAnimation("RunCannonEffect");
}
bool CannonEffect::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	e_ActiveFrames =7;//特效的帧数
	e_String = "WeaponSwitch00";//特效文件
	auto m_Animation = createAnimation(e_String, e_ActiveFrames, e_delay);
	m_Animation->retain();
	AnimationCache::getInstance()->addAnimation(m_Animation, "RunCannonEffect");

	this->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("RunCannonEffect")), CallFunc::create(CC_CALLBACK_0(CannonEffect::EffectDestroy, this)), NULL));

	return true;
}
void CannonEffect::EffectDestroy()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
Animation* CannonEffect::createAnimation(std::string prefixName, unsigned short framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		if (i == 1)
		{
			this->initWithSpriteFrame(frame);
		}
		if (frame)
		{
			animFrames.pushBack(frame);
		}
	}
	animFrames.popBack();
	return Animation::createWithSpriteFrames(animFrames, delay);
}
