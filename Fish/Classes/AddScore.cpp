#include "AddScore.h"
#include "Config.h"

AddScore::AddScore()
{

}

AddScore::~AddScore()
{

}
AddScore* AddScore::create(unsigned short m_Coin)
{
	auto m_addscore = new (std::nothrow)AddScore();
	if (m_addscore&&m_addscore->init(m_Coin))
	{
		m_addscore->autorelease();
		return m_addscore;
	}
	else
	{
		CC_SAFE_DELETE(m_addscore);
		return NULL;
	}
}

bool AddScore::init(unsigned short m_Coin)
{
	if (!Sprite::init())
	{
		return false;
	}
	auto m_addscore = Label::createWithCharMap(s_addcore, 23,30,'+');
	m_addscore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	m_addscore->setAlignment(TextHAlignment::CENTER);
	char addscore[50];
	sprintf(addscore, "+%d", m_Coin);
	m_addscore->setString(addscore);

	Vec2 m_addFontPoint = Config::getInstance()->getGoldPoint();
	m_addscore->setPosition(Vec2(m_addFontPoint.x+m_addscore->getContentSize().width/2, m_addFontPoint.y));
	this->addChild(m_addscore, Z_2);
	m_addscore->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(0,40)), CallFunc::create(CC_CALLBACK_0(AddScore::addScroeActionCallback, this)), NULL));

	return true;
}
void AddScore::addScroeActionCallback()
{
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}