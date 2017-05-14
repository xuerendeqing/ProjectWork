#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "GameDefine.h"

class Config : public Ref
{
private:
	Config();
	Vec2 m_goldPoint, m_diamondPoint;
	int m_coinValue, m_diamondValue;
	unsigned short  m_cannonValue, p_FishType;
	PauseState m_isPauseState;
	bool m_isLock,m_isLockImage,m_isKillShow;
	unsigned short m_isKillValue;
public:
	virtual ~Config();

	static Config* getInstance();

	int getCoinValue();//获取分数值
	void setCoinValue(int coin);

	int getDiamondValue();//获取钻石数值
	void setDiamondValue(int diamond);

	//获取炮台值
	unsigned short getCannonValue();
	void setCannonValue(unsigned short cannonValue);
	//子弹值消耗金币的方法
	void setBulletValue(unsigned short bulletValue);
	//处理技能消耗钻石的方法
	void setSkillValue(unsigned short skillValue);

	//获取金币菜单的位置
	void setGoldPoint(Vec2 s_goldpoint);
	Vec2 getGoldPoint();

	//获取钻石菜单的位置
	void setDiamondPoint(Vec2 s_diamondpoint);
	Vec2 getDiamondPoint();
	//获取定屏的状态值
	void setPauseFish(PauseState m_PauseState);
	PauseState getPauseFish();
	//获取锁定的真假值
	void setFishLock(bool l_lock);
	bool getFishLock();
	//鱼的击杀计数
	void setKillValue(unsigned short kill);
	unsigned short getKillValue();
	//鱼的死亡计数
	void setKillShow(bool m_kill);
	bool getKillShow();
	//获取鱼的类型
	void setFishType(unsigned short s_fishType);
	unsigned short getFishType();

};
#endif