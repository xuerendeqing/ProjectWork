#ifndef _FISH_BEZIER_TO_H_
#define _FISH_BEZIER_TO_H_

#include "GameDefine.h"

class FishBezierTo : public BezierTo
{
public:
	static FishBezierTo* create(float t, const ccBezierConfig& c);

	bool initWithDuration(float t, const ccBezierConfig &c);

	virtual void update(float dt);
};
#endif 