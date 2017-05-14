#include "Gold.h"
#include "Config.h"

Gold::Gold() :g_delay(0.05f), m_GoldSpeed(20)
{

}

Gold::~Gold()
{
	AnimationCache::getInstance()->removeAnimation("RunGoldAnimation");
}
Gold* Gold::create(GoldType type, Vec2 point)
{
	auto m_gold= new (std::nothrow)Gold();
	if (m_gold&&m_gold->init(type, point))
	{
		m_gold->autorelease();
		return m_gold;
	}
	else
	{
		CC_SAFE_DELETE(m_gold);
		return NULL;
	}
}

bool Gold::init(GoldType type, Vec2 point)
{
	if (!Sprite::init())
	{
		return false;
	}
	if (!GetBooleanFromXML("MySound"))
	{
		AudioEngine::play2d(s_gold_effect, false, 1.0f);
	}
	switch (type)
	{
	case COIN_TYPE_GOLDSMALL:
		g_GoldFrames = 12;
		g_String = "1_coin_";
		break;
	case COIN_TYPE_GOLDBIG:
		g_GoldFrames = 12;
		g_String = "5_coin_";
		break;
	default:
		break;
	}
	this->setPosition(point);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	m_targetPoint =Config::getInstance()->getGoldPoint();

	auto g_Animation = createAnimation(g_String, g_GoldFrames, g_delay);
	g_Animation->retain();
	AnimationCache::getInstance()->addAnimation(g_Animation, "RunGoldAnimation");
	this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunGoldAnimation")));
	this->runAction(Sequence::create(DelayTime::create(1.0f),Spawn::createWithTwoActions(ScaleTo::create(0.5f,0.6f),MoveTo::create(0.5f, Vec2(m_targetPoint.x-this->getContentSize().width-14,m_targetPoint.y+5))), CallFunc::create(CC_CALLBACK_0(Gold::GlodActionCallback, this)), NULL));
	return true;
}
void Gold::GlodActionCallback()
{
	this->removeFromParentAndCleanup(true);
}
Animation* Gold::createAnimation(std::string prefixName, unsigned short framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%02d.png", i);
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