#include "Loading.h"
#include "Config.h"
#include "StartLayer.h"
Loading::Loading()
{
	current_number = 0;
	total_number =42;
}
Loading::~Loading()
{
	
}
Scene* Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_load_plist);//加载道具图标资源
	Director::getInstance()->getTextureCache()->addImage(s_load_fish);

	auto m_loadback = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage(s_load));
	m_loadback->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_loadback->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(m_loadback, Z_0, LOAD_BACK_TAG);

	auto m_ProgressBack = Sprite::create(s_progback);
	m_ProgressBack->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_ProgressBack->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(m_ProgressBack, Z_0,PROG_BACK_TAG);
	//加载进度条
	auto m_Progress = ProgressTimer::create(Sprite::create(s_prog));
	m_Progress->setType(ProgressTimer::Type::BAR);
	m_Progress->setMidpoint(Vec2(0, 0));
	m_Progress->setBarChangeRate(Vec2(0, 1));
	m_Progress->setPercentage(0);
	m_Progress->setPosition(m_ProgressBack->getPosition());
	this->addChild(m_Progress, Z_1,PROGRESS_TAG);
	
	Vector<SpriteFrame*> loadfish;
	for (short int i = 1; i <=8; i++)
	{
		auto frameName = String::createWithFormat("fish0%d.png", i);
		auto pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		if (pFrame)
		{
			loadfish.pushBack(pFrame);
		}
	}
	auto animation = Animation::createWithSpriteFrames(loadfish, 0.1f);
	auto animate = Animate::create(animation);
	auto originalFrameName = String::createWithFormat("fish01.png");
	auto m_pSprite= Sprite::createWithSpriteFrameName(originalFrameName->getCString());
	m_pSprite->setPosition(m_ProgressBack->getPosition());
	m_pSprite->runAction(RepeatForever::create(animate));
	this->addChild(m_pSprite,Z_3,LOAD_FISH_TAG);
	loadfish.clear();

	TTFConfig ttfConfig("fonts/arial.ttf", 30);
	auto m_pLoadLabel = Label::createWithTTF(ttfConfig, "0%", TextHAlignment::CENTER, visibleSize.width);
	m_pLoadLabel->setColor(Color3B(238, 0, 0));
	m_pLoadLabel->setPosition(Vec2(m_ProgressBack->getPositionX(),m_ProgressBack->getPositionY()-m_pSprite->getContentSize().height/2-20));
	this->addChild(m_pLoadLabel,Z_2,LABEL_TAG);
	

	Director::getInstance()->getTextureCache()->addImageAsync(s_start, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_ui, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_achiev, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_word, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_Bg, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_head, CC_CALLBACK_1(Loading::LoadingResource, this));
	
	//纹理加载顺序按照从大到小加载
	for (unsigned short i = 0; i <4;i++)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(s_back[i], CC_CALLBACK_1(Loading::LoadingResource, this));//加载的背景
	}
	//加载水波纹图片
	Director::getInstance()->getTextureCache()->addImageAsync(s_battery_back, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_cannon, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_battery_effect, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_weapon, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_star, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_coral, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_water, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_set_back, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_setting, CC_CALLBACK_1(Loading::LoadingResource, this));

	//加载鱼图片
	for (unsigned short i = 0; i <17; i++)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(s_fish[i], CC_CALLBACK_1(Loading::LoadingResource, this));
	}
	Director::getInstance()->getTextureCache()->addImageAsync("ui/touch.png", CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync("bullet/Bullet.pvr.ccz", CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync("bullet/net.pvr.ccz", CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync("gold/Gold.pvr.ccz", CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_ianji, CC_CALLBACK_1(Loading::LoadingResource, this));
	Director::getInstance()->getTextureCache()->addImageAsync(s_lianji_font, CC_CALLBACK_1(Loading::LoadingResource, this));
	

	return true;
}

void Loading::LoadingResource(Texture2D *texture)
{
	current_number++;
	char m_pString[10];
	sprintf(m_pString, "%d%%", (int)(((float)current_number / total_number) * 100));
	auto m_Load = (Label*)this->getChildByTag(LABEL_TAG);
	m_Load->setString(m_pString);
	
	int percentage = (int)(((float)current_number / total_number) * 100);

	auto m_progress = (ProgressTimer*)this->getChildByTag(PROGRESS_TAG);

	m_progress->setPercentage(percentage);

	if (current_number == total_number)
	{
		log("%s\n", Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());//打印加载到缓存的纹理
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, StartLayer::createScene()));
		this->removeFromParentAndCleanup(true);
	}
}
