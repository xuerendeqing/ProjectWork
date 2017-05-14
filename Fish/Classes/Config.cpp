#include "Config.h"

__Array *fish_array;
__Array *group_array;
__Array *bullet_array;
__Array *score_array;
static  Config *g_config = NULL;

Config::Config() :m_coinValue(GetIntegerFromXML("MyGold")), m_diamondValue(GetIntegerFromXML("MyDiamond")), m_cannonValue(0), m_goldPoint(0, 0),
m_diamondPoint(0, 0), m_isPauseState(PAUSE_IDLE), m_isLock(false), m_isLockImage(true), m_isKillValue(0), m_isKillShow(false), p_FishType(0)
{
	
}
Config::~Config()
{
	
}
Config* Config::getInstance()
{
	if (!g_config)
	{
		g_config = new (std::nothrow)Config();
	}
	return g_config;
}
void Config::setCoinValue(int score)
{
	m_coinValue += score;
}
int Config::getCoinValue()
{
	return m_coinValue;
}
void Config::setDiamondValue(int diamond)
{
	m_diamondValue += diamond;
}
int Config::getDiamondValue()
{
	return m_diamondValue;
}

void Config::setGoldPoint(Vec2 s_goldpoint)
{
	m_goldPoint = s_goldpoint;
}
Vec2 Config::getGoldPoint()
{
	return m_goldPoint;
}
void Config::setDiamondPoint(Vec2 s_diamondpoint)
{
	m_diamondPoint = s_diamondpoint;
}
Vec2 Config::getDiamondPoint()
{
	return m_diamondPoint;
}

void Config::setCannonValue(unsigned short cannonValue)//������ֵ̨
{
	m_cannonValue = cannonValue;
}
unsigned short Config::getCannonValue()
{
	return m_cannonValue;
}
void Config::setBulletValue(unsigned short bulletValue)//�����Ҳ����������
{
	if (m_coinValue >= bulletValue)
	{
		m_coinValue -= bulletValue;
	}
}
void Config::setSkillValue(unsigned short skillValue)//������ʯ�����������
{
	if (m_diamondValue >= skillValue)
	{
		m_diamondValue -= skillValue;
	}
}


void Config::setPauseFish(PauseState m_PauseState)//���ö������ܵ����ֵ
{
	m_isPauseState=m_PauseState;
}
PauseState Config::getPauseFish()
{
	return m_isPauseState;
}
void Config::setFishLock(bool l_lock)//���������������ֵ
{
	m_isLock = l_lock;
}
bool Config::getFishLock()
{
	return m_isLock;
}
void Config::setKillValue(unsigned short kill)//��Ļ�ɱ����
{
	m_isKillValue += kill;
}
unsigned short Config::getKillValue()
{
	return m_isKillValue;
}

void Config::setKillShow(bool m_kill)//���������������ֵ
{
	m_isKillShow = m_kill;
}
bool Config::getKillShow()
{
	return m_isKillShow;
}
void Config::setFishType(unsigned short s_fishType)//��ȡ�������
{
	p_FishType = s_fishType;
}
unsigned short Config::getFishType()
{
	return p_FishType;
}

