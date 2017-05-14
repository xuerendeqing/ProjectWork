#include "GameLayer.h"
#include "BackLayer.h"
#include "WaterLayer.h"
#include "Fish.h"
#include "FishLine.h"
#include "Config.h"
#include "Bullet.h"

GameLayer::GameLayer() :m_State(GAME_STATE_START)
{

}
GameLayer::~GameLayer()
{
	SetIntegerToXML("MyGold", Config::getInstance()->getCoinValue());
	SetIntegerToXML("MyDiamond", Config::getInstance()->getDiamondValue());
	SetIntegerToXML("MyCannonType",m_UiLayer->m_CannonType);
	fish_array->release();
	group_array->release();
	bullet_array->release();
	score_array->release();

	this->unscheduleAllCallbacks();

	//�ͷ���Դ
	Director::getInstance()->getTextureCache()->removeAllTextures();

	SpriteFrameCache::getInstance()->removeSpriteFrameByName("water/water.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("battery/cannon.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("bullet/Bullet.plist");//�����ӵ�
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("bullet/net.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("battery/CannonEffectFrame.plist");//�����ڻ���Ч
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("battery/WeaponSwitch.plist");//�����ڵ�ת����Ч
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("ui/touch.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("gold/Gold.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("ui/ui.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("ui/lianji0.plist");

	SpriteFrameCache::getInstance()->removeSpriteFrameByName("start/start.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("start/achievement.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("start/achievement_word.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("start/seting.plist");

	SpriteFrameCache::getInstance()->removeSpriteFrameByName("pao_1.plist");//������

	for (unsigned short i = 0; i < 18; i++)
	{
		SpriteFrameCache::getInstance()->removeSpriteFrameByName(s_fish_plist[i]);
	}

}
Scene *GameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLayer::create();

	scene->addChild(layer);
	     
	return scene;
}
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//��������
	if (!GetBooleanFromXML("MyMusic"))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(s_back_music[3], true);
	}
	//��ʼ������
	auto m_Back = BackLayer::create();
	this->addChild(m_Back, Z_0);
	//����ˮ��
	auto m_Water = WaterLayer::create();
	this->addChild(m_Water, Z_3);
	//����UI��
	m_UiLayer=UILayer::create();
	this->addChild(m_UiLayer, Z_4);
	//���������
	fish_array = __Array::createWithCapacity(MAX_FISH_COUNT);
	fish_array->retain();
	//��Ⱥ����
	group_array = __Array::create();
	group_array->retain();
	//�ӵ�����
	bullet_array = __Array::create();
	bullet_array->retain();
	//����
	score_array = __Array::create();
	score_array->retain();
	
	this->scheduleUpdate();//��Ϸ��ײ���߼����

	this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::updateFish), 0.1f);//��Ĵ���

	this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::createFishLine),5.0f);//��Ⱥ�Ͷ��еĴ���ʱ��

	return true;
}

void GameLayer::updateFish(float dt)
{
	if (fish_array->count()<MAX_FISH_COUNT)//С������������һ����
	{
		//this->addFish();
		int n = MAX_FISH_COUNT - fish_array->count();//���������
		int nAdd = rand() % n + 1;
		for (int i = 0; i <= nAdd; i++)
		{
			this->addFish();
		}
	}
}
void GameLayer::addFish()
{
	unsigned short m_FishType = 5 + rand() % 13;//������������
	unsigned short m_Direction =rand()%16;
	Vec2 m_start, m_end, m_control_1, m_control_2;
	switch (m_Direction)//��������еĿ�ʼ�������㣬�Ϳ��Ƶ�
	{
	case 0:
		//����,����
		m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 1:
		//��������
		m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 2:
		m_start = Vec2((rand()%(int)(origin.x + visibleSize.width)),(origin.y + visibleSize.height+150));
		m_end = Vec2((rand() %(int)(origin.x + visibleSize.width)),(origin.y-150));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 3:
		m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y-150));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y +visibleSize.height+150));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 4:
		m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y+visibleSize.height+150));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y-150));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 5:
		m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
		m_end = Vec2(origin.x- 150, origin.y + (rand() % (int)(origin.y + visibleSize.height/2)));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height / 2)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width/2)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 6:
		m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
		m_end = Vec2(origin.x+visibleSize.width+150, origin.y + (rand() % (int)(origin.y + visibleSize.height / 2)));
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height / 2)));
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height)));
		break;
	case 7:
		m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y+visibleSize.height+150);
		m_control_1 = Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2);
		m_control_2 = Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height);
		break;
	case 8:
		m_start = Vec2(origin.x+visibleSize.width+150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width/2+200)), origin.y + visibleSize.height + 150);
		m_control_1 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		m_control_2 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2);
		break;
	case 9:
		m_start = Vec2((origin.x-150), (origin.y + visibleSize.height));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width))-150, origin.y - 150);
		m_control_1 =Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height);
		m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y);
		break;
	case 10:
		m_start = Vec2((origin.x - 150), origin.y);
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y+visibleSize.height+150);
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height);
		m_control_2 = Vec2(origin.x + visibleSize.width, origin.y);
		break;
	case 11:
		m_start = Vec2((origin.x+visibleSize.width+150), (origin.y+visibleSize.height));
		m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y-150);
		m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height);
		m_control_2 = Vec2(origin.x, origin.y);
		break;
	case 12:
		//s����
		m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_control_1 = Vec2(400, 720);
		m_control_2 = Vec2(900, 100);
		break;
	case 13:
		m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_end = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
		m_control_1 = Vec2(400, 720);
		m_control_2 = Vec2(900, 100);
		break;
	case 14:
		//�����������·����Բ
		m_start = Vec2(origin.x - 150, origin.y + visibleSize.height / 2);
		m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + visibleSize.height / 2);
		m_control_1 = Vec2(300, 720);
		m_control_2 = Vec2(1000, 720);
		break;
	case 15:
		m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + visibleSize.height / 2);
		m_end = Vec2(origin.x - 100, origin.y + visibleSize.height / 2);
		m_control_1 = Vec2(300, 720);
		m_control_2 = Vec2(1000, 720);
		break;
	default:
		break;
	}
	//auto m_Fish = Fish::create(m_FishType, m_Direction, m_start, m_end, m_control_1, m_control_2);
	//this->addChild(m_Fish, Z_2);
	//fish_array->addObject(m_Fish);
	for (int i = 0; i < GET_ARRAY_LEN(FishBatchNode); i++)
	{
		if (m_FishType == FishBatchNode[i])
		{
			auto m_Fish = Fish::create(m_FishType, m_Direction, m_start, m_end, m_control_1, m_control_2);
			this->addChild(m_Fish, Z_2);
			fish_array->addObject(m_Fish);
			break;
		}
	}
}
void GameLayer::createFishLine(float dt)
{
	if (group_array->count()<3)
	{

		unsigned short m_LineType = rand() % 5;
		unsigned short m_Group =rand() % 2;
		unsigned short m_Num = 0;
		Vec2 m_start, m_end, m_control_1, m_control_2, p_start, p_end;
		unsigned short m_Direction = rand() % 16;
		switch (m_Direction)//��������еĿ�ʼ�������㣬�Ϳ��Ƶ�
		{
		case 0:
			//����,����
			m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 1:
			//��������
			m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 2:
			m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y - 150));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 3:
			m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y - 150));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 4:
			m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y - 150));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 5:
			m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
			m_end = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height / 2)));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height / 2)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 6:
			m_start = Vec2((rand() % (int)(origin.x + visibleSize.width)), (origin.y + visibleSize.height + 150));
			m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height / 2)));
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height / 2)));
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width / 2)), (rand() % (int)(origin.y + visibleSize.height)));
			break;
		case 7:
			m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height + 150);
			m_control_1 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
			m_control_2 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);
			break;
		case 8:
			m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width / 2 + 200)), origin.y + visibleSize.height + 150);
			m_control_1 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
			m_control_2 = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
			break;
		case 9:
			m_start = Vec2((origin.x - 150), (origin.y + visibleSize.height));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)) - 150, origin.y - 150);
			m_control_1 = Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height);
			m_control_2 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y);
			break;
		case 10:
			m_start = Vec2((origin.x - 150), origin.y);
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height + 150);
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height);
			m_control_2 = Vec2(origin.x + visibleSize.width, origin.y);
			break;
		case 11:
			m_start = Vec2((origin.x + visibleSize.width + 150), (origin.y + visibleSize.height));
			m_end = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y - 150);
			m_control_1 = Vec2((rand() % (int)(origin.x + visibleSize.width)), origin.y + visibleSize.height);
			m_control_2 = Vec2(origin.x, origin.y);
			break;
		case 12:
			//s����
			m_start = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_control_1 = Vec2(400, 720);
			m_control_2 = Vec2(900, 100);
			break;
		case 13:
			m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_end = Vec2(origin.x - 150, origin.y + (rand() % (int)(origin.y + visibleSize.height)));
			m_control_1 = Vec2(400, 720);
			m_control_2 = Vec2(900, 100);
			break;
		case 14:
			//�����������·����Բ
			m_start = Vec2(origin.x - 150, origin.y + visibleSize.height / 2);
			m_end = Vec2(origin.x + visibleSize.width + 150, origin.y + visibleSize.height / 2);
			m_control_1 = Vec2(300, 720);
			m_control_2 = Vec2(1000, 720);
			break;
		case 15:
			m_start = Vec2(origin.x + visibleSize.width + 150, origin.y + visibleSize.height / 2);
			m_end = Vec2(origin.x - 100, origin.y + visibleSize.height / 2);
			m_control_1 = Vec2(300, 720);
			m_control_2 = Vec2(1000, 720);
			break;
		default:
			break;
		}
		switch (m_Group)
		{
		case 0:

			if (m_LineType == 0 || m_LineType == 1 || m_LineType == 2 || m_LineType == 3 || m_LineType == 4)
			{
				switch (m_LineType)
				{
				case 0:
					m_Num = 6 + rand() % 3;
					break;
				case 1:
					m_Num = 5 + rand() % 3;
					break;
				case 2:
					m_Num = 4 + rand() % 3;
					break;
				case 3:
					m_Num = 3 + rand() % 3;
					break;
				case 4:
					m_Num = 5 + rand() % 3;
					break;
				default:
					break;
				}
			}
			break;
		case 1:
			if (m_LineType == 0 || m_LineType == 2 || m_LineType == 4)
			{
				switch (m_LineType)
				{
				case 0:
					m_Num = 6 + rand() % 3;
					break;
				case 2:
					m_Num = 5 + rand() % 3;
					break;
				case 4:
					m_Num = 5 + rand() % 3;
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
		for (unsigned short i = 0; i < m_Num; i++)
		{
			auto m_Line = FishLine::create(m_Group, m_LineType, i, m_Direction, m_start, m_end, m_control_1, m_control_2);
			this->addChild(m_Line, Z_2);
			group_array->addObject(m_Line);
		}

	}
	
}
Rect shrinkRect(Rect rc, float xr, float yr)
{
	float w = rc.size.width * xr;
	float h = rc.size.height * yr;
	Vec2 pt = Vec2(rc.origin.x + rc.size.width * (1.0f - xr) / 2, rc.origin.y + rc.size.height * (1.0f - yr) / 2);
	return Rect(pt.x, pt.y, w, h);
}

void GameLayer::update(float dt)
{

	Ref *p_Fish = NULL;
	Ref *p_Bullet = NULL;
	Ref *p_FishLine = NULL;
	//����ӵ��������ײ
	CCARRAY_FOREACH(bullet_array, p_Bullet)//������ײЧ�ʲ��С�
	{
		auto s_bullet = (Bullet*)p_Bullet;

		if (s_bullet->m_status == BULLET_FLY)
		{
			CCARRAY_FOREACH(fish_array, p_Fish)//�����ı���
			{
				auto s_fish = (Fish*)p_Fish;
				if (s_fish == NULL)
				{
					continue;
				}
				if (s_bullet->getPositionX() >= s_fish->getPositionX() - s_fish->getContentSize().width / 2 && s_bullet->getPositionX() <= s_fish->getPositionX() + s_fish->getContentSize().width / 2 && s_bullet->getPositionY() >= s_fish->getPositionY() - 20 && s_bullet->getPositionY() <= s_fish->getPositionY() + 20)
				{
					s_bullet->ShowNet();
				}
			}
			CCARRAY_FOREACH(group_array, p_FishLine)//��Ⱥ
			{
				auto s_fishline = (FishLine*)p_FishLine;
				if (s_fishline == NULL)
				{
					continue;
				}
				if (s_bullet->getPositionX() >= s_fishline->getPositionX() - s_fishline->getContentSize().width / 2 && s_bullet->getPositionX() <= s_fishline->getPositionX() + s_fishline->getContentSize().width / 2 && s_bullet->getPositionY() >= s_fishline->getPositionY() - 20 && s_bullet->getPositionY() <= s_fishline->getPositionY() + 20)
				{
					s_bullet->ShowNet();
				}
			}

			if (s_bullet->m_status == BULLET_NET)
			{
				CCARRAY_FOREACH(fish_array, p_Fish)
				{
					auto s_fish = (Fish*)p_Fish;
					Rect netRect = shrinkRect(s_bullet->getBoundingBox(), 0.5, 0.5);
					if (netRect.intersectsRect(s_fish->getBoundingBox()))
					{
						s_fish->FishBlink();
						if (netRect.containsPoint(s_fish->getPosition()))
						{
							s_fish->FishDestroy();
						}
					}

				}
				CCARRAY_FOREACH(group_array, p_FishLine)
				{
					auto s_fishline = (FishLine*)p_FishLine;
					Rect netRect = shrinkRect(s_bullet->getBoundingBox(), 0.5, 0.5);
					if (netRect.intersectsRect(s_fishline->getBoundingBox()))
					{
						s_fishline->FishBlink();
						if (netRect.containsPoint(s_fishline->getPosition()))
						{
							s_fishline->Destroy();

						}
					}
				}
				s_bullet->m_status = BULLET_END;
			}
		}
	}
	//����������Ҫ����
	if (Config::getInstance()->getFishLock()==true)
	{
		//��ⴥ�����λ���������ײ����ʼ��ײ��ǰ�������ǡ����ܰ�ť�������
		CCARRAY_FOREACH(fish_array, p_Fish)//�����ı���
		{
			auto s_fish = (Fish*)p_Fish;
			//�����⿪ʼ�������λ�ú������ײλ��
			if (m_UiLayer->m_TouchPoint.x >= s_fish->getPositionX() - s_fish->getContentSize().width / 2 && m_UiLayer->m_TouchPoint.x <= s_fish->getPositionX() + s_fish->getContentSize().width / 2 && m_UiLayer->m_TouchPoint.y >= s_fish->getPositionY() - 20 && m_UiLayer->m_TouchPoint.y <= s_fish->getPositionY() + 20)
			{
				//�жϴ����Ƿ�����ɣ���ɺ�ʼ����ͼ��
				if (m_UiLayer->p_islock == true)
				{
					m_UiLayer->p_islock = false;
					//�ж��Ƿ��д�������ͼ�ꡣ���û����ô�ʹ���һ�Ρ����ͼ����ڣ��򲻴���
					s_fish->IinitCreateLockImage();
				}

			}
		}
	}
	//��������
	if (Config::getInstance()->getPauseFish() == PAUSE_TRUE)
	{
		CCARRAY_FOREACH(fish_array, p_Fish)
		{
			auto s_fish = (Fish*)p_Fish;
			s_fish->PauseFishAction();
		}
		CCARRAY_FOREACH(group_array, p_FishLine)//��Ⱥ
		{
			auto s_fishline = (FishLine*)p_FishLine;
			s_fishline->PauseFishAction();
		}
	}
	else if (Config::getInstance()->getPauseFish() == PAUSE_FALSE)
	{
		CCARRAY_FOREACH(fish_array, p_Fish)
		{
			auto s_fish = (Fish*)p_Fish;
			s_fish->RecoverFishAction();
		}
		CCARRAY_FOREACH(group_array, p_FishLine)//��Ⱥ
		{
			auto s_fishline = (FishLine*)p_FishLine;
			s_fishline->RecoverFishAction();
		}
	}



}


void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
