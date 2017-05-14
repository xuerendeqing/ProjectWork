#ifndef _GAME_DEFINE_H_
#define _GAME_DEFINE_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "network/WebSocket.h"
#include "network/HttpClient.h"
#include "network/SocketIO.h"
#include <iostream>
#include "tinyxml2/tinyxml2.h"
#include <vector>
#include <string>
#include <list>
#include <map>
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace  cocos2d::network;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
using namespace cocos2d::experimental;
using namespace cocos2d::extension;
using namespace tinyxml2;
using namespace std;
using std::list;
using std::map;

#define MAX_FISH_COUNT 20//在屏幕中显示的鱼的最大个数
#define GET_ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))
#define BulletMaxReflect 3//子弹反弹次数




#define SetStringToXML UserDefault::getInstance()->setStringForKey  

#define SetIntegerToXML UserDefault::getInstance()->setIntegerForKey  

#define SetBooleanToXML UserDefault::getInstance()->setBoolForKey  

#define GetStringFromXML UserDefault::getInstance()->getStringForKey  

#define GetIntegerFromXML UserDefault::getInstance()->getIntegerForKey  

#define GetBooleanFromXML UserDefault::getInstance()->getBoolForKey  

/***************************************************************************/
struct PhysicsRippleSpriteConfig 
{
	int quadCountX{80};
	int quadCountY{80};
	int touchRadius{1};
	float updateInterval{1/30.0f};

	PhysicsRippleSpriteConfig(){}
	PhysicsRippleSpriteConfig(int countX, int countY, int radius, float interval) :quadCountX(countX),quadCountY(countY),touchRadius(radius),updateInterval(interval)
	{

	}
};

/******************Z轴序列**************************************************/
#define Z_R		-1
#define Z_0		0
#define Z_1		1
#define Z_2		2
#define Z_3		3
#define Z_4		4
#define Z_5		5
#define Z_6		6
/*************************************************************************/
#define PROGRESS_TAG	100
#define LABEL_TAG		101
#define LOAD_BACK_TAG	102
#define PROG_BACK_TAG   103
#define LOAD_FISH_TAG   104


#define LOCK_SPRITE_1   105
#define LOCK_SPRITE_2   106
/*************************************************************************/
enum GameState
{
	GAME_STATE_START = 0,
	GAME_STATE_OVER
};
/**************************************change*****************************************/
typedef enum 
{
	BULLET_FLY = 0,
	BULLET_NET,
	BULLET_END
}BulletStatus;

/***********************************effectType**************************************************/
typedef enum
{
	EFFECT_TYPE_0 = 0,
	EFFECT_TYPE_1,
	EFFECT_TYPE_2,
	EFFECT_TYPE_3
}EffectType;
/*************************************************************************/
typedef enum 
{
	COIN_TYPE_GOLDSMALL,
	COIN_TYPE_GOLDBIG
}GoldType;
/*************************************************************************/
typedef enum
{
	SKILLE_BUTTON_1 = 0,
	SKILLE_BUTTON_2,
	SKILLE_BUTTON_3,
	SKILLE_BUTTON_4
}ButtonType;

/*************************************************************************/
typedef enum
{
	PAUSE_IDLE= 0,//定屏的状态模式
	PAUSE_TRUE,
	PAUSE_FALSE,
}PauseState;
/*************************************************************************/
typedef enum
{
	COMMON_MODEL = 0,//普通模式
	QUICK_MODEL,//极速模式
	RAGE_MODEL,//狂爆模式
}CannonModel;
/*************************************************************************/
typedef enum
{
	TOUCH_MODEL = 0,//普通模式
	LOCK_MODEL,//技能锁定的触摸模式
}TouchModel;

/**************************************change*****************************************/
static const char s_change[] = "music/change.mp3";
static const char s_button[] = "music/button.mp3";
/*******************************************************************************/
static const char s_start_music[] = "music/start.mp3";
/*******************************************************************************/
static const char s_gold_effect[] = "music/drop_gold.mp3";
static const char s_camera[] = "music/camera.mp3";

/*************************************************************************************/
static const char *s_back_music[5] = { "music/back_1.mp3", "music/back_2.mp3", "music/back_3.mp3", "music/back_4.mp3","music/back_5.mp3" };

/**************************************fire*******************************************/
static const char s_fire[]="music/fire.mp3";
static const char s_firefail[] = "music/firefail.mp3";
/**************************************fish_effect************************************/
static const char *s_fish_effect[15] = { "music/fish_1.mp3", "music/fish_2.mp3", "music/fish_3.mp3", "music/fish_4.mp3", "music/fish_5.mp3" ,
								"music/fish_6.mp3", "music/fish_7.mp3", "music/fish_8.mp3", "music/fish_9.mp3", "music/fish_10.mp3",
								"music/fish_11.mp3", "music/fish_12.mp3", "music/fish_13.mp3", "music/fish_14.mp3", "music/fish_15.mp3"};
/**************************************back************************************/
static const char *s_back[4] = { "back/back0.png", "back/back1.png", "back/back2.png", "back/back3.png" };
/**************************************fish************************************/
static const char *s_fish[18] = { "fish/fish1.png", "fish/fish2.png", "fish/fish3.png", "fish/fish4.png", "fish/fish5.png", "fish/fish6.png", 
								"fish/fish7.png", "fish/fish8.png", "fish/fish9.png", "fish/fish10.png", "fish/fish11.png", "fish/fish12.png", 
								"fish/fish13.png", "fish/fish14.png", "fish/fish15.png", "fish/fish16.png", "fish/fish17.png", "fish/fish18.png" };

static const char *s_fish_plist[18] = { "fish/fish1.plist", "fish/fish2.plist", "fish/fish3.plist", "fish/fish4.plist", "fish/fish5.plist", "fish/fish6.plist",
										"fish/fish7.plist", "fish/fish8.plist", "fish/fish9.plist", "fish/fish10.plist", "fish/fish11.plist", "fish/fish12.plist",
										"fish/fish13.plist", "fish/fish14.plist", "fish/fish15.plist", "fish/fish16.plist", "fish/fish17.plist", "fish/fish18.plist" };
/**************************************net************************************/
static const char *s_fish_net[5] = { "bullet/net1.png", "bullet/net2.png", "bullet/net3.png", "bullet/net4.png", "bullet/net5.png" };


static const char *s_net_plist[5] = { "bullet/net1.plist", "bullet/net2.plist", "bullet/net3.plist", "bullet/net4.plist", "bullet/net5.plist" };

/**************************************loading************************************/
static const char s_load[] = "loading/loadBg.png";
static const char s_progback[] = "loading/bubble.png";
static const char s_prog[] = "loading/water.png";
static const char s_load_fish[] = "loading/load.png";
static const char s_load_plist[] = "loading/load.plist";
/**************************************battery************************************/
static const char s_battery_back[] = "battery/foundation.png";
static const char s_cannon[] = "battery/cannon.png";
static const char s_battery_effect[] = "battery/CannonEffectFrame.png";
static const char s_weapon[] = "battery/WeaponSwitch.png";
/**************************************start************************************/
static const char s_start_back[] = "start/startback.png";
static const char s_start[] = "start/start.png";
static const char s_Bg[] = "start/Bg.png";
static const char s_word[] = "start/achievement_word.png";
static const char s_achiev[] = "start/achievement.png";
static const char s_set_back[] = "start/settingBg.png";
static const char s_setting[] = "start/seting.png";
static const char s_mask[] = "start/switch-mask.png";
static const char s_off[] = "start/switch-off.png";
static const char s_on[] = "start/switch-on.png";
static const char s_adjust[] = "start/btn_adjust.png";
/**************************************water************************************/
static const char s_water[] = "water/water.png";
/**************************************back************************************/
static const char s_star[] = "back/star.png";
static const char s_coral[] = "back/coral.png";
/**************************************ui************************************/
static const char s_ui[] = "ui/ui.png";
static const char s_head[] = "ui/head.png";
static const char s_lock_up[] = "ui/lock_up.png";
static const char s_lock_down[] = "ui/lock_down.png";
static const char s_lock_default[] = "ui/lock_default.png";
static const char s_rage_up[] = "ui/rage_up.png";
static const char s_rage_down[] = "ui/rage_down.png";
static const char s_rage_default[] = "ui/rage_default.png";
static const char s_speed_up[] = "ui/speed_up.png";
static const char s_speed_down[] = "ui/speed_down.png";
static const char s_speed_default[] = "ui/speed_default.png";
static const char s_suspend_up[] = "ui/suspend_up.png";
static const char s_suspend_down[] = "ui/suspend_down.png";
static const char s_suspend_default[] = "ui/suspend_default.png";
static const char s_ianji[] = "ui/lianji0.png";



/**************************************number*****************************************/
static const char s_coin[] = "number/shop_num.png";
static const char s_core[] = "number/showup_gold.png"; 
static const char s_addcore[] = "number/getNumber.png";
static const char s_notice[] = "number/notice.png";
static const char s_lianji_font[] = "number/lianji_font.png";
/**************************************fish_array****************************/
extern __Array *fish_array;
extern __Array *group_array;
extern __Array *bullet_array;
extern __Array *score_array;
const int FishBatchNode[] = { 0,1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12, 13, 14,15,16,17};

#endif