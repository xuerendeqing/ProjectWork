#include "Fish.h"
#include "CardinalSpline.h"
#include "Config.h"
#include "Gold.h"
#include "Score.h"
#include "AddScore.h"

Fish::Fish() :m_delay(0.1f), m_originColor(getColor())
{

}
Fish::~Fish()
{
	AnimationCache::getInstance()->removeAnimation("RunFishAnimation");
}
Fish* Fish::create(unsigned short type, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2)
{
	auto m_fish = new (std::nothrow)Fish();
	if (m_fish&&m_fish->init(type, m_Direction, m_start, m_end, m_control_1, m_control_2))
	{
		m_fish->autorelease();
		return m_fish;
	}
	else
	{
		CC_SAFE_DELETE(m_fish);
		return NULL;
	}
}

bool Fish::init(unsigned short type, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2)
{
	if (!Sprite::init())
	{
		return false;
	}
	m_FishType = type;
	this->initFish(type,m_Direction, m_start, m_end, m_control_1, m_control_2);
	this->runAction(Sequence::create(m_first, CallFunc::create(CC_CALLBACK_0(Fish::MoveFinishCallBack, this)), NULL));

	return true;
}
void Fish::FishBlink()
{
	if (!Director::getInstance()->getScheduler()->isScheduled(CC_SCHEDULE_SELECTOR(Fish::updateShine), this))
	{
		this->schedule(CC_SCHEDULE_SELECTOR(Fish::updateShine), 0.1f, 5, 0);
	}
}
void Fish::MoveFinishCallBack()
{
	
	this->stopAllActions();
	fish_array->removeObject(this);
	this->setVisible(false);
	//这里创建金币函数
}
void Fish::FishDestroy()
{
	//获取鱼的类型
	Config::getInstance()->setFishType(m_FishType);
	this->stopAllActions();
	fish_array->removeObject(this);
	this->setVisible(false);
	this->createGold();//创建金币函数
}
void Fish::createGold()
{
	Config::getInstance()->setCoinValue(m_Coin);
	//创建鱼死后所值的分数
	auto m_Score = Score::create(m_Coin, this->getPosition());
	this->getParent()->addChild(m_Score, Z_2);
	//创建加分数的字体显示
	auto m_AddScore = AddScore::create(m_Coin);
	this->getParent()->addChild(m_AddScore, Z_2);
	//这里创建金币掉落的动画
	auto m_Gold = Gold::create(COIN_TYPE_GOLDBIG, this->getPosition());
	this->getParent()->addChild(m_Gold, Z_2);
	Config::getInstance()->setKillValue(1);
	Config::getInstance()->setKillShow(true);
}
void Fish::IinitCreateLockImage()
{
	auto m_Lock= Sprite::create("ui/lock_image.png");//这里是测试用
	m_Lock->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	this->addChild(m_Lock, Z_3, LOCK_SPRITE_1);
}
void Fish::PauseFishAction()//暂停鱼的活动
{
	//this->pauseSchedulerAndActions();
	this->getActionManager()->pauseTarget(this);
}

void Fish::RecoverFishAction()
{
	//this->resumeSchedulerAndActions();
	this->getActionManager()->resumeTarget(this);
}
void Fish::updateShine(float dt)
{
	Color3B c1 = getColor();
	if (c1.r != 125)
	{
		this->setColor(Color3B(125, 0, 0));
	}
	else
	{
		this->setColor(m_originColor);
	}
}
Animation* Fish::createAnimation(std::string prefixName, unsigned short framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		if (i == 1)
		{
			this->initWithSpriteFrame(frame);
		}
		if (frame)
		{
			animFrames.pushBack(frame);
		}
	}
	animFrames.popBack();
	return Animation::createWithSpriteFrames(animFrames, delay, -1);
}
void Fish::initFish(unsigned short type, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2)
{
	switch (type)
	{
	case 0:
		m_ActiveFrames = 8;
		m_String = "fish1000";
		m_speedTime =10;//队列鱼，鱼群的时间固定
		m_Coin = 10;
		break;
	case 1:
		m_ActiveFrames = 8;
		m_String = "fish2000";
		m_speedTime =10;
		m_Coin = 20;
		break;
	case 2:
		m_ActiveFrames = 8;
		m_String = "fish3000";
		m_speedTime = 10;
		m_Coin = 30;
		break;
	case 3:
		m_ActiveFrames = 8;
		m_String = "fish4000";
		m_speedTime = 10;
		m_Coin = 40;
		break;
	case 4:
		m_ActiveFrames = 8;
		m_String = "fish5000";
		m_speedTime =10;
		m_Coin = 50;
		break;
	case 5:
		m_ActiveFrames = 8;//单个鱼，时间随机。最好能设定不同的时间值。测试
		m_String = "fish6000";
		m_speedTime = 8+rand()%5;
		m_Coin = 60;
		break;
	case 6:
		m_ActiveFrames = 8;
		m_String = "fish7000";
		m_speedTime = 10 + rand() %5;
		m_Coin = 70;
		break;
	case 7:
		m_ActiveFrames = 8;
		m_String = "fish8000";
		m_speedTime = 10 + rand() %5;
		m_Coin = 80;
		break;
	case 8:
		m_ActiveFrames = 8;
		m_String = "fish9000";
		m_speedTime = 10+rand()%10;
		m_Coin = 90;
		break;
	case 9:
		m_ActiveFrames = 8;
		m_String = "fish10000";
		m_speedTime = 15 + rand() % 10;
		m_Coin = 100;
		break;
	case 10:
		m_ActiveFrames = 8;
		m_String = "fish11000";
		m_speedTime = 20+ rand() %5;
		m_Coin = 110;
		break;
	case 11:
		m_ActiveFrames = 8;
		m_String = "fish12000";
		m_speedTime = 15+ rand() % 10;
		m_Coin = 120;
		break;
	case 12:
		m_ActiveFrames = 8;
		m_String = "fish13000";
		m_speedTime = 15 + rand() % 10;
		m_Coin = 130;
		break;
	case 13:
		m_ActiveFrames = 8;
		m_String = "fish14000";
		m_speedTime = 20 + rand() % 10;
		m_Coin =140;
		break;
	case 14:
		m_ActiveFrames = 8;
		m_String = "fish15000";
		m_speedTime = 15 + rand() %5;
		m_Coin = 150;
		break;
	case 15:
		m_ActiveFrames = 8;
		m_String = "fish16000";
		m_speedTime = 15 + rand() %5;
		m_Coin = 160;
		break;
	case 16:
		m_ActiveFrames = 8;
		m_String = "fish17000";
		m_speedTime = 20 + rand() % 10;
		m_Coin = 170;
		break;
	case 17:
		m_ActiveFrames = 8;
		m_String = "fish18000";
		m_speedTime = 10 + rand() % 10;
		m_Coin =180;
		break;
	default:
		break;
	}
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	
	auto w_Animation = createAnimation(m_String, m_ActiveFrames, m_delay);
	w_Animation->retain();
	AnimationCache::getInstance()->addAnimation(w_Animation, "RunFishAnimation");
	this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunFishAnimation")));

	ccBezierConfig bezier_1;

	if (m_Direction == 0 || m_Direction ==2 || m_Direction ==4 || m_Direction ==5 || m_Direction ==7 || m_Direction ==9 || m_Direction ==11 || m_Direction ==12 || m_Direction ==14)
	{
		//左下,左上
		bezier_1.controlPoint_1 = m_control_1;
		bezier_1.controlPoint_2 = m_control_2;
		bezier_1.endPosition = m_end;
	}
	else if (m_Direction ==1|| m_Direction ==3|| m_Direction == 6 || m_Direction == 8 || m_Direction ==10 || m_Direction == 13|| m_Direction ==15)
	{
		//右下右上
		bezier_1.controlPoint_1 = m_control_2;
		bezier_1.controlPoint_2 = m_control_1;
		bezier_1.endPosition = m_end;
	}
	this->setPosition(m_start);
	m_first = FishBezierTo::create(m_speedTime, bezier_1);

}