#include "Cannon.h"
#include "Config.h"
#include "Bullet.h"
#include "UILayer.h"

Cannon::Cannon() :m_Rotation(0.0f)
{

}

Cannon::~Cannon()
{
	
}
Cannon* Cannon::create(UILayer *s_UILayer)
{
	auto m_cannon = new (std::nothrow)Cannon();
	if (m_cannon&&m_cannon->init(s_UILayer))
	{
		m_cannon->autorelease();
		return m_cannon;
	}
	else
	{
		CC_SAFE_DELETE(m_cannon);
		return NULL;
	}
}

bool Cannon::init(UILayer *s_UILayer)
{
	if (!Sprite::init())
	{
		return false;
	}
	c_UILayer = s_UILayer;

	switch (GetIntegerFromXML("MyCannonType"))//因为创建中加减改变在ui层中，所以这里需要重新全部初始化一次。用于文件的保存读取
	{
	case 0:
		this->initWithSpriteFrameName("cannon001.png");
		Config::getInstance()->setCannonValue(50);
		break;
	case 1:
		this->initWithSpriteFrameName("cannon002.png");
		Config::getInstance()->setCannonValue(100);
		break;
	case 2:
		this->initWithSpriteFrameName("cannon003.png");
		Config::getInstance()->setCannonValue(150);
		break;
	case 3:
		this->initWithSpriteFrameName("cannon004.png");
		Config::getInstance()->setCannonValue(200);
		break;
	case 4:
		this->initWithSpriteFrameName("cannon005.png");
		Config::getInstance()->setCannonValue(250);
		break;
	case 5:
		this->initWithSpriteFrameName("cannon006.png");
		Config::getInstance()->setCannonValue(300);
		break;
	default:
		break;
	}
	this->setAnchorPoint(Vec2(0.5f, 0.4f));//注意锚点的设置可以改变炮台的旋转
	this->setPosition(Vec2(origin.x + visibleSize.width/2-this->getContentSize().width/2+52, origin.y +this->getContentSize().height/2-50));

	return true;
}
void Cannon::RotationToFire(Vec2 m_Point)//这里计算出了炮台需要旋转的方向和角度
{
	if (m_Point.y < Director::getInstance()->getWinSize().height / 20)
		return;
	Vec2 ptFrom = this->getPosition();
	float angle = atan((m_Point.x - ptFrom.x) / (m_Point.y - ptFrom.y));
	this->setRotation(angle * 180 / M_PI);
	m_Direction = m_Point;
}
void Cannon::Fire()
{
	if (Config::getInstance()->getCoinValue() >= c_UILayer->Cannon_Value)
	{
		if (!GetBooleanFromXML("MySound"))
		{
			AudioEngine::play2d(s_fire, false, 0.5f);
		}
		auto m_Bullet = Bullet::create(this, c_UILayer->m_CannonType, c_UILayer->Cannon_Value);
		m_Bullet->shootTo(m_Direction);
		this->getParent()->addChild(m_Bullet, Z_R);
		bullet_array->addObject(m_Bullet);
	}
	else
	{
		if (!GetBooleanFromXML("MySound"))
		{
			AudioEngine::play2d(s_firefail, false, 0.5f);
		}
	}
}
void Cannon::CannonAction()
{
	this->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Cannon::ScaleCallbackA, this)), DelayTime::create(0.05f), CallFunc::create(CC_CALLBACK_0(Cannon::ScaleCallbackB, this)), NULL));
}
void Cannon::ScaleCallbackA()
{
	this->setScaleY(0.9f);
	this->Fire();
}
void Cannon::ScaleCallbackB()
{
	this->setScaleY(1.0f);
}
