#include "FishLine.h"
#include "FishBezierTo.h"
#include "CardinalSpline.h"
#include "Config.h"

static float angle=0;

FishLine::FishLine() :interval(0.5f)
{

}

FishLine::~FishLine()
{

}
FishLine* FishLine::create(unsigned short m_Group, unsigned short type, unsigned short i, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2)
{
	auto m_fishline = new (std::nothrow)FishLine();
	if (m_fishline&&m_fishline->init(m_Group, type, i, m_Direction, m_start, m_end, m_control_1, m_control_2))
	{
		m_fishline->autorelease();
		return m_fishline;
	}
	else
	{
		CC_SAFE_DELETE(m_fishline);
		return NULL;
	}
}
bool FishLine::init(unsigned short m_Group, unsigned short type, unsigned short i, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2)
{
	if (!Sprite::init())
	{
		return false;
	}

	this->initFish(type, m_Direction, m_start, m_end, m_control_1, m_control_2);
	Size m_size= this->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	int r = sqrt(m_size.width*m_size.width + m_size.height/2*m_size.height/2);

	angle +=30;
	m_start = m_start + Vec2(rand() % r*cos(angle) + m_size.width, rand() % r*sin(angle) + m_size.height);
	m_end = m_end + Vec2(rand() % r*cos(angle) + m_size.width, rand() % r*sin(angle) + m_size.height);

	ccBezierConfig bezier_first;
	FishBezierTo *m_firstFish;
	f_Group = m_Group;
	switch (m_Group)
	{
	case 0:
		interval = this->m_speedTime * this->getContentSize().width / visibleSize.width;
		m_FishAction_1 = Sequence::create(DelayTime::create(interval*i), m_first, CallFunc::create(CC_CALLBACK_0(FishLine::MoveFinish, this)), NULL);
		this->runAction(m_FishAction_1);
		break;
	case 1:
		if (m_Direction == 0 || m_Direction == 2 || m_Direction == 4 || m_Direction == 5 || m_Direction == 7 || m_Direction == 9 || m_Direction == 11 || m_Direction == 12 || m_Direction == 14)
		{
			bezier_first.controlPoint_1 = m_control_1 + Vec2(r*cos(angle) + m_size.width, r*sin(angle) + m_size.height);
			bezier_first.controlPoint_2 = m_control_2 + Vec2(r*cos(angle) + m_size.width, r*sin(angle) + m_size.height);
			bezier_first.endPosition = m_end;
		}
		else if (m_Direction == 1 || m_Direction == 3 || m_Direction == 6 || m_Direction == 8 || m_Direction == 10 || m_Direction == 13 || m_Direction == 15)
		{
			bezier_first.controlPoint_2 = m_control_1 + Vec2(r*cos(angle) + m_size.width, r*sin(angle) + m_size.height);
			bezier_first.controlPoint_1 = m_control_2 + Vec2(r*cos(angle) + m_size.width, r*sin(angle) + m_size.height);
			bezier_first.endPosition = m_end;
		}
		this->setPosition(m_start);
		m_firstFish = FishBezierTo::create(m_speedTime+rand()%2, bezier_first);
		m_FishAction_2 = Sequence::create(m_firstFish, CallFunc::create(CC_CALLBACK_0(FishLine::MoveFinish, this)), NULL);
		this->runAction(m_FishAction_2);
		break;
	default:
		break;
	}

	return true;
}
void FishLine::MoveFinish()
{
	this->stopAllActions();
	group_array->removeObject(this);
	this->removeFromParentAndCleanup(true);
}
void FishLine::Destroy()
{
	Config::getInstance()->setKillValue(1);
	this->stopAllActions();
	group_array->removeObject(this);
	this->setVisible(false);
	this->createGold();
}
