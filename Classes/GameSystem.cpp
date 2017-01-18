//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/11/19
//!	
//!	GameSystem.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//--------------------------------
#include "GameSystem.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameOverScene.h"
#include "ReadySetGo.h"
//-------------------------------

USING_NS_CC;

using namespace cocostudio::timeline;


// on "init" you need to initialize your instance
bool GameSystem::init()
{
	if (!Node::init())
	{
		return false;
	}

	//初期化
	_gameDuration = 60;
	_timer = 0;
	_score = 0;
	_hpBarScale = 1.f;
	_start = false;

	_pUserDefault = UserDefault::getInstance();
	_highScore = _pUserDefault->getIntegerForKey("highScore", 0);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Billboardの作成
	_billboard = BillBoard::create(BillBoard::Mode::VIEW_PLANE_ORIENTED);
	_billboard->setPosition3D(Vec3(0, 4.5, 0));
	_billboard->setScale(0.015f);
	_billboard->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(_billboard);

	//プレイヤーHPバー
	Sprite* emptyHpBarSpr = Sprite::create("emptyHP.png");
	emptyHpBarSpr->setCameraMask((unsigned short)CameraFlag::USER1);
	emptyHpBarSpr->setGlobalZOrder(1);
	_billboard->addChild(emptyHpBarSpr);

	//MAX HPの表示
	_hpBarSpr = Sprite::create("fullHP.png");
	_hpBarSpr->setCameraMask((unsigned short)CameraFlag::USER1);
	_hpBarSpr->setGlobalZOrder(2);
	_hpBarSpr->setAnchorPoint(Vec2::ZERO);
	_hpBarSpr->setPosition(-250, -25);
	_billboard->addChild(_hpBarSpr);

	//時間のラベル
	_timeText = Label::create("60", "Jokerman", 50);
	_timeText->setCameraMask((unsigned short)CameraFlag::USER1);
	_timeText->setPosition(Vec2(0.f, -50.f));
	_billboard->addChild(_timeText);

	//時間のラベル
	_scoreText = Label::create("Score = 0", "Jokerman", 60);
	_scoreText->setCameraMask((unsigned short)CameraFlag::USER1);
	_scoreText->setPosition(Vec2(-450.f, -50.f));
	_billboard->addChild(_scoreText);

	_pRadar = Radar::create();
	_pRadar->setCameraMask((unsigned short)CameraFlag::USER1);
	_pRadar->setPosition(Vec2(450.f, -75.f));
	_billboard->addChild(_pRadar);


	//スタートの前の4秒待ち
	DelayTime* dt = DelayTime::create(4);
	this->runAction(dt);

	this->scheduleUpdate();
	return true;
}
void GameSystem::update(float dt)
{
	//スタートしなければ、始まらない
	if (!_start)
		return;
	
	//タイムカウント
	_timer++;

	//HPバーを減らす
	setHPBarScale(_hpBarScale);

	//1秒になったらゲームの制限時間を減らす
	if (_timer >= 60)
	{
		_gameDuration--;
		//時間の表示
		String* str = String::createWithFormat("%d", _gameDuration);
		_timeText->setString(str->getCString());
		_timer = 0;
	}

	//制限時間になったら終了
	if (_gameDuration <= 0)
	{
		auto scene = GameOverScene::createScene(_score,_highScore);
		auto transition = TransitionFade::create(1.0f, scene);
		Director::getInstance()->replaceScene(transition);

		this->unscheduleAllSelectors();
		log("Game End");
	}

	//スコアの表示
	String* scoreStr = String::createWithFormat("Score = %d", _score);
	_scoreText->setString(scoreStr->getCString());

	//ハイスコア
	if (_score >= _highScore)
	{
		//ハイスコアを代入
		_highScore = _score;
		//ハイスコアを書き込む(仮）
		_pUserDefault->setIntegerForKey("highScore", _highScore);
	}

	_pRadar->setRadarRot(_crystalPos, _cameraPos);
}


void GameSystem::setBonusTime(float bonusTime)
{
	_gameDuration += bonusTime;
	String* str = String::createWithFormat("%d", _gameDuration);
	_timeText->setString(str->getCString());

	_plusTimeText = Label::create("+1", "Jokerman", 50);
	_plusTimeText->setCameraMask((unsigned short)CameraFlag::USER1);
	_plusTimeText->setPosition(Vec2(60.f, -100.f));
	_plusTimeText->setTextColor(Color4B::YELLOW);
	_billboard->addChild(_plusTimeText);

	MoveTo* move = MoveTo::create(1.5f, Vec2(60.f, -50.f));
	FadeOut* fo = FadeOut::create(1.5f);
	Sequence* seq = Sequence::create(move, fo, nullptr);
	_plusTimeText->runAction(seq);
}


