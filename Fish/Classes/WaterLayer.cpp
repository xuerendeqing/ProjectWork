#include "WaterLayer.h"


WaterLayer::WaterLayer() :w_delay(0.05f)
{

}

WaterLayer::~WaterLayer()
{
	AnimationCache::getInstance()->removeAnimation("RunDartEffect");
}
bool WaterLayer::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	this->setScaleX(5.0f);
	this->setScaleY(2.8f);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	
	w_ActiveFrames = 32;//特效的帧数
	w_String = "wave_";//特效文件

	auto w_Animation = createAnimation(w_String, w_ActiveFrames, w_delay);
	w_Animation->retain();
	AnimationCache::getInstance()->addAnimation(w_Animation, "RunWaterEffect");
	this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunWaterEffect")));
	
	return true;
}
Animation* WaterLayer::createAnimation(std::string prefixName, unsigned short framesNum, float delay)
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
	return Animation::createWithSpriteFrames(animFrames, delay, -1);
}
