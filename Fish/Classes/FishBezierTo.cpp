#include "FishBezierTo.h"
#include "Fish.h"

FishBezierTo* FishBezierTo::create(float t, const ccBezierConfig& c)//¹¹Ôìº¯Êı
{
	auto m_bezier = new (std::nothrow)FishBezierTo();
	if (m_bezier&&m_bezier->initWithDuration(t, c))
	{
		m_bezier->autorelease();
		return m_bezier;
	}
	else
	{
		CC_SAFE_DELETE(m_bezier);
		return NULL;
	}

}

bool FishBezierTo::initWithDuration(float t, const ccBezierConfig &c)
{
	return BezierTo::initWithDuration(t, c);
}
void FishBezierTo::update(float dt)
{
	Vec2 last = ((Fish*)this->getTarget())->m_lastPoint;
	Vec2 current = this->getTarget()->getPosition();

	double angle = atan2((current.y - last.y), (current.x - last.x));

	this->getTarget()->setRotation(180-(angle * 360) / (2 * 3.1415926));

	((Fish*)this->getTarget())->m_lastPoint = current;
	return BezierTo::update(dt);
};
