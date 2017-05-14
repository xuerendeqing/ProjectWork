#ifndef _UI_LAYER_H_
#define _UI_LAYER_H_

#include "GameDefine.h"
#include "Cannon.h"
#include "TouchEffect.h"

class UILayer :public Layer
{
public:
	UILayer();

	virtual ~UILayer();

	virtual bool init();

	CREATE_FUNC(UILayer);

	Cannon *m_Cannon;
	TouchEffect *m_TouchEffect;
	unsigned short m_CannonType;
	unsigned short Cannon_Value;
	bool p_islock;

	Label *L_Coin, *L_Diamond, *Cannon_Coin,*L_Kill;
	cocos2d::ui::Button *m_Skill_1;
	cocos2d::ui::Button *m_Skill_2;
	cocos2d::ui::Button *m_Skill_3;
	cocos2d::ui::Button *m_Skill_4;
	 
	Vec2 m_startPoint,m_TouchPoint;
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
	
	void addButton(Ref* pSender);
	void subButton(Ref* pSender);
	void AudioButtonFinish();
	void CannonChangeCallBack();
	void CannonEffect();


	void updateUI(float dt);//游戏UI的更新

	void updateSingleDelay(float dt);
	void updateLongDelay(float dt);
	void CannonQuickModel(float dt);//大炮的极速模式

	void onSingClick();//单击函数
	void onLongClick();//长按

	void CoinCallback(Ref* pSender);//金币回调函数
	void DiamondCallback(Ref* pSender);//钻石回调函数
	void CameraCallback(Ref* pSender);

	void afterCapture(bool succeed, const std::string& outputFile);//截图
	void SkillButtonCallback_1(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);//极速技能回调
	void SkillButtonCallback_2(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);//锁定技能回调
	void SkillButtonCallback_3(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);//定屏技能回调
	void SkillButtonCallback_4(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);//暴走技能回调
	void SkillClickCallBack(ButtonType m_buttonType);
	void SkillFinishRemove_1();
	void SkillFinishRemove_2();
	void SkillFinishRemove_3();
	void SkillFinishRemove_4();

protected:
	bool m_isLongPress, m_isMove, m_isTouch, m_isAdd, m_isSub, m_isButton, m_isChange, m_isSkill_1,
		 m_isSkill_2, m_isSkill_3, m_isSkill_4,m_isKillAction;
	int m_PressTime, m_TouchCounts;
	unsigned short m_GoldCount;//金币计数
	int total_points, diamond_points, kill_count;//总金币数,钻石总数
	std::string m_filename;
	Sprite			*m_click_1, *m_click_2, *m_click_3,*m_click_4;
	ProgressTimer	*m_ProgressTimer_1, *m_ProgressTimer_2, *m_ProgressTimer_3, *m_ProgressTimer_4;
	ProgressTo		*m_progress_1, *m_progress_2, *m_progress_3, *m_progress_4;
	CannonModel m_Model;
	TouchModel  m_TouchModel;
	Sprite *m_Frozen;
};
#endif