#include "Score.h"


Score::Score()
{

}


Score::~Score()
{

}
Score* Score::create(unsigned short m_Coin, Vec2 point)
{
	auto m_score= new (std::nothrow)Score();
	if (m_score&&m_score->init(m_Coin, point))
	{
		m_score->autorelease();
		return m_score;
	}
	else
	{
		CC_SAFE_DELETE(m_score);
		return NULL;
	}
}

bool Score::init(unsigned short m_Coin, Vec2 point)
{
	if (!Sprite::init())
	{
		return false;
	}
	auto m_score =Label::createWithCharMap(s_core, 36, 47, '0');
	m_score->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	m_score->setAlignment(TextHAlignment::CENTER);
	char score[50];
	sprintf(score, "%d", m_Coin);
	m_score->setString(score);
	m_score->setPosition(point);
	this->addChild(m_score);
	//判断字体显示的位置,修正字体显示超出屏幕位置，导致无法看清
	if (m_score->getPositionY()>=origin.y+visibleSize.height-50)
	{
		m_score->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0,-30)), CallFunc::create(CC_CALLBACK_0(Score::ScoreActionCallback, this)), NULL));
	}
	else
	{
		m_score->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0, 30)), CallFunc::create(CC_CALLBACK_0(Score::ScoreActionCallback, this)), NULL));
	}
	if (m_score->getPositionX()>=origin.x+visibleSize.width-50)
	{
		m_score->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(-10, 30)), CallFunc::create(CC_CALLBACK_0(Score::ScoreActionCallback, this)), NULL));
	}
	else if (m_score->getPositionX()<origin.x+50)
	{
		m_score->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(10, 30)), CallFunc::create(CC_CALLBACK_0(Score::ScoreActionCallback, this)), NULL));
	}
	return true;
}
void Score::ScoreActionCallback()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}