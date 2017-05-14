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

	int getCoinValue();//��ȡ����ֵ
	void setCoinValue(int coin);

	int getDiamondValue();//��ȡ��ʯ��ֵ
	void setDiamondValue(int diamond);

	//��ȡ��ֵ̨
	unsigned short getCannonValue();
	void setCannonValue(unsigned short cannonValue);
	//�ӵ�ֵ���Ľ�ҵķ���
	void setBulletValue(unsigned short bulletValue);
	//������������ʯ�ķ���
	void setSkillValue(unsigned short skillValue);

	//��ȡ��Ҳ˵���λ��
	void setGoldPoint(Vec2 s_goldpoint);
	Vec2 getGoldPoint();

	//��ȡ��ʯ�˵���λ��
	void setDiamondPoint(Vec2 s_diamondpoint);
	Vec2 getDiamondPoint();
	//��ȡ������״ֵ̬
	void setPauseFish(PauseState m_PauseState);
	PauseState getPauseFish();
	//��ȡ���������ֵ
	void setFishLock(bool l_lock);
	bool getFishLock();
	//��Ļ�ɱ����
	void setKillValue(unsigned short kill);
	unsigned short getKillValue();
	//�����������
	void setKillShow(bool m_kill);
	bool getKillShow();
	//��ȡ�������
	void setFishType(unsigned short s_fishType);
	unsigned short getFishType();

};
#endif