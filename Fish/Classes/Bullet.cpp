#include "Bullet.h"
#include "Config.h"
#include "Cannon.h"

Bullet::Bullet() :m_Speed(700), m_reflectTimes(0)
{

}
Bullet::~Bullet()
{
	
}
Bullet* Bullet::create(Cannon *m_cannon, unsigned short m_CannonType, unsigned short cannonValue)
{
	auto m_bullet = new (std::nothrow)Bullet();
	if (m_bullet&&m_bullet->init(m_cannon, m_CannonType, cannonValue))
	{
		m_bullet->autorelease();
		return m_bullet;
	}
	else
	{
		CC_SAFE_DELETE(m_bullet);
		return NULL;
	}
}

bool Bullet::init(Cannon *m_cannon, unsigned short m_CannonType, unsigned short cannonValue)
{
	if (!Sprite::init())
	{
		return false;
	}
	switch (m_CannonType)
	{
	case 0://依据炮台类型加载子弹
		m_BulletString = "bullet_1_1.png";
		m_NetString = "net_0.png";
		break;
	case 1:
		m_BulletString = "bullet_1_2.png";
		m_NetString = "net_1.png";//因为渔网图片不够，所以公用。或者使用调色的方法。
		break;
	case 2:
		m_BulletString = "bullet_1_3.png";
		m_NetString = "net_2.png";
		break;
	case 3:
		m_BulletString = "bullet_2_1.png";
		m_NetString = "net_2.png";
		break;
	case 4:
		m_BulletString = "bullet_2_2.png";
		m_NetString = "net_3.png";
		break;
	case 5:
		m_BulletString = "bullet_2_3.png";
		m_NetString = "net_3.png";
		break;
	default:
		break;
	}
	Config::getInstance()->setBulletValue(cannonValue);
	this->initWithSpriteFrameName(m_BulletString);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	float m_angle = 90 - m_cannon->getRotation();
	float m_radian = M_PI*m_angle / 180;
	//这里显示子弹子在跑台口为开始点
	Vec2 deltaPosition = Vec2((m_cannon->getContentSize().height / 2) *cos(m_radian), (m_cannon->getContentSize().height / 2) * sin(m_radian));
	this->setPosition(m_cannon->getPosition().x + deltaPosition.x, m_cannon->getPosition().y + deltaPosition.y);
	this->setRotation(90 - m_angle);
	//创建炮台开火特效
	m_status =BULLET_FLY;
	return true;  
}
void Bullet::shootTo(Vec2 targetDirection)
{
	Vec2 ptFrom = this->getPosition();
	Vec2 ptTo = targetDirection;


	ptLastStart = ptFrom;

	Vec2 targetPt;
	
	if (ptTo.x < ptFrom.x)
	{
		//left
		if ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) >(origin.y + visibleSize.height - ptFrom.y) / (0 - ptFrom.x))
		{
			//real left
			targetPt.x = 0;
			targetPt.y = (ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x);
		}
		else
		{
			//up
			targetPt.y = origin.y + visibleSize.height;
			targetPt.x = (origin.y + visibleSize.height - ((ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x))) / ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x));
		}
	}
	else if (ptTo.x > ptFrom.x)
	{
		//right
		if ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) < (origin.y + visibleSize.height - ptFrom.y) / (origin.x + visibleSize.width - ptFrom.x))
		{
			//real right
			targetPt.x = origin.x + visibleSize.width;
			targetPt.y = origin.x + visibleSize.width*(ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) + (ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x);
		}
		else
		{
			//up
			targetPt.y = origin.y + visibleSize.height;
			targetPt.x = (origin.y + visibleSize.height - ((ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x))) / ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x));
		}
	}
	else
	{
		//mid
		targetPt.x = ptTo.x;
		targetPt.y = origin.y + visibleSize.height;
	}
	
	if (targetPt.y < this->getPositionY())
	{
		//开始区分
		if (targetPt.x>this->getPositionX())
		{
			if ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) > (origin.y + visibleSize.height - ptFrom.y) / (0 - ptFrom.x))
			{
				//real left
				targetPt.x = 0;
				targetPt.y = (ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x);
			}
			else
			{
				//up
				targetPt.y = origin.y + visibleSize.height;
				targetPt.x = (origin.y + visibleSize.height - ((ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x))) / ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x));
			}
		}
		else if (targetPt.x<this->getPositionX())
		{
			//right
			if ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) < (origin.y + visibleSize.height - ptFrom.y) / (origin.x + visibleSize.width - ptFrom.x))
			{
				//real right
				targetPt.x = origin.x + visibleSize.width;
				targetPt.y = origin.x + visibleSize.width*(ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x) + (ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x);
			}
			else
			{
				//up
				targetPt.y = origin.y + visibleSize.height;
				targetPt.x = (origin.y + visibleSize.height - ((ptTo.x*ptFrom.y - ptFrom.x*ptTo.y) / (ptTo.x - ptFrom.x))) / ((ptTo.y - ptFrom.y) / (ptTo.x - ptFrom.x));
			}
		}
	}

	float moveSec = getBulletMoveTime(ptFrom, targetPt);
	this->runAction(Sequence::create(MoveTo::create(moveSec, targetPt), CallFunc::create(CC_CALLBACK_0(Bullet::reflect, this)), NULL));
}
float Bullet::getBulletMoveTime(Vec2 startPos, Vec2 endPos)
{
	float dis = sqrtf((startPos.x - endPos.x) * (startPos.x - endPos.x) + (startPos.y - endPos.y) * (startPos.y - endPos.y));
	float sec = dis / m_Speed;
	return sec;
}
void Bullet::reflect()
{
	m_reflectTimes++;
	if (m_reflectTimes >= BulletMaxReflect)
	{
		this->BulletDestroy();
	}

	Vec2 ptFrom = this->getPosition();
	
	float k = -(ptFrom.y - ptLastStart.y) / (ptFrom.x - ptLastStart.x);
	float b = ptFrom.y - k*ptFrom.x;
	Vec2 target[4];
	Vec2 realTarget;
	Rect rc;
	rc.setRect(0, 0, origin.x+visibleSize.width, origin.y+visibleSize.height);

	//cross with left
	target[0].x = 0;
	target[0].y = b;

	//cross with right
	target[1].x = origin.x+visibleSize.width;
	target[1].y = origin.x + visibleSize.width*k + b;

	//cross with down
	target[2].y = 0;
	target[2].x = -b / k;

	//cross with up
	target[3].y = origin.y + visibleSize.height;
	target[3].x = (origin.y + visibleSize.height - b) / k;

	for (int i = 0; i < 4; i++) 
	{
		if (((int)target[i].x != (int)ptFrom.x || (int)target[i].y != (int)ptFrom.y) && rc.containsPoint(target[i]))
		{
			realTarget = target[i];
			break;
		}
	}

	float angle = atan2f(realTarget.y - ptFrom.y, realTarget.x - ptFrom.x);
	float rotation = angle / M_PI * 180.0f;
	this->setRotation(90.0f - rotation);

	float moveSec = getBulletMoveTime(ptFrom, realTarget);

	this->runAction(Sequence::create(MoveTo::create(moveSec, realTarget), CallFunc::create(CC_CALLBACK_0(Bullet::reflect, this)), NULL));
	ptLastStart = ptFrom;
}
void Bullet::ShowNet()
{
	this->stopAllActions();
	m_status = BULLET_NET;
	this->initWithSpriteFrameName(m_NetString);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->runAction(Sequence::create(ScaleTo::create(0.1f, 1.3f), CallFunc::create(CC_CALLBACK_0(Bullet::BulletDestroy, this)), NULL));
}
void Bullet::BulletDestroy()
{
	this->stopAllActions();
	bullet_array->removeObject(this);
	this->removeFromParentAndCleanup(true);
}