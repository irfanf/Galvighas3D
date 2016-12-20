//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/5/24
//!	
//!	LogoScene.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//---------------------------------------------------------------------
#include "LogoScene.h"
#include "ui/CocosGUI.h"
#include "TitleScene.h"
//---------------------------------------------------------------------
USING_NS_CC;
//---------------------------------------------------------------------
//------------------------------------
//@! クラス作成
//------------------------------------
Scene* LogoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//------------------------------------
//@! クラスの初期化
//------------------------------------
bool LogoScene::init()
{

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	//タッチしたら移動
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(LogoScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//-----------------------------------------------------------------
	//ロゴを出す
	auto logo_bg = Sprite::create("Logo/Logo_bg.png");
	logo_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	logo_bg->setScale(0.0001);
	this->addChild(logo_bg);

	//ロゴ名を出す
	auto logo_tag = Sprite::create("Logo/Logo_name.png");
	logo_tag->setPosition(Vec2(-1000.0f, visibleSize.width / 2));
	this->addChild(logo_tag);

	//ロゴのパーティクル
	CCParticleSystemQuad* logo_particle = CCParticleSystemQuad::create("Logo/particleLogo2.plist");
	logo_particle->resetSystem();
	logo_particle->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	logo_particle->setScale(1.5);
	this->addChild(logo_particle);

	//ロゴのアクション
	DelayTime* delay = DelayTime::create(1.5f);
	RotateBy* rot = RotateBy::create(1.5f, 360);
	ScaleTo* scale = ScaleTo::create(1.0f,1);
	Spawn* spawn = Spawn::create(rot, scale, nullptr);
	Sequence* seq = Sequence::create(delay, spawn, nullptr);
	logo_bg->runAction(seq);

	//ロゴ名のアクション
	MoveTo* move = MoveTo::create(2.0f, Vec2(visibleSize.width / 2, visibleSize.height / 2));
	Sequence* seq2 = Sequence::create(delay, move, nullptr);
	logo_tag->runAction(seq2);

	//-----------------------------------------------------------------

	//シーン生成されてから4秒後に"ChangeScene"が呼ばれる
	this->scheduleOnce(schedule_selector(LogoScene::changeScene), 5.0f);

	//-----------------------------------------------------------------

	return true;
}


//------------------------------------
//@! 時間たったら,シーン移動する
//@! 時間
//------------------------------------
void LogoScene::changeScene(float dt)
{
	//移動先シーンの作成
	auto scene = TitleScene::createScene();
	scene = TitleScene::createScene();
	auto transition = TransitionFade::create(3.0f, scene);
	Director::getInstance()->replaceScene(transition);
}
//------------------------------------
//@! 時間たったら,シーン移動する
//@! 時間
//------------------------------------
bool LogoScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	//移動先シーンの作成
	auto scene = TitleScene::createScene();
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);

	this->unscheduleAllSelectors();

	return false;
}


