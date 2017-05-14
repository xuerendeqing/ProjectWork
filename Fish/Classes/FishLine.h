#ifndef _FISH_LINE_H_
#define _FISH_LINE_H_

#include "GameDefine.h"
#include "Fish.h"

class FishLine :public Fish
{
public:
	FishLine();

	virtual ~FishLine();

	static FishLine *create(unsigned short m_Group,unsigned short type, unsigned short i, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2);

	bool init(unsigned short m_Group, unsigned short type, unsigned short i, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2);

	void Destroy();

	void MoveFinish();
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float interval;
	unsigned short f_Group;
	Sequence *m_FishAction_1;
	Sequence *m_FishAction_2;
};
#endif