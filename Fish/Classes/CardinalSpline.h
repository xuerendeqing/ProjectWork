#ifndef _CARDINAL_SPLINE_H_
#define _CARDINAL_SPLINE_H_

#include "GameDefine.h"

class CardinalSpline : public CardinalSplineTo
{
public:
	CardinalSpline();

	virtual ~CardinalSpline();

	static CardinalSpline* create(float duration, PointArray* points, float tension);

	bool initWithDuration(float duration, PointArray* points, float tension);
	
	virtual void update(float dt);
};
#endif