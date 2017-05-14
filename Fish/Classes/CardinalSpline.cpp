#include "CardinalSpline.h"
#include "Fish.h"

CardinalSpline::CardinalSpline()
{

}


CardinalSpline::~CardinalSpline()
{

}

CardinalSpline* CardinalSpline::create(float duration, PointArray *points, float tension)
{
	auto m_cardinalSpline = new (std::nothrow)CardinalSpline();
	if (m_cardinalSpline&&m_cardinalSpline->initWithDuration(duration, points, tension))
	{
		m_cardinalSpline->autorelease();
		return m_cardinalSpline;
	}
	else
	{
		CC_SAFE_DELETE(m_cardinalSpline);
		return NULL;
	}

}

bool CardinalSpline::initWithDuration(float duration, PointArray *points, float tension)
{
	return CardinalSplineTo::initWithDuration(duration, points, tension);
}

void CardinalSpline::update(float dt)
{

	Vec2 last = ((Fish*)this->getTarget())->m_lastPoint;
	Vec2 current = this->getTarget()->getPosition();

	double angle = atan2((current.y - last.y), (current.x - last.x));
	this->getTarget()->setRotation(180-(angle * 360) / (2 * 3.1415926));
	//this->getTarget()->setRotation(270-(angle * 360) / (2 * 3.1415926));
	((Fish*)this->getTarget())->m_lastPoint = current;

	return CardinalSplineTo::update(dt);
};