//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/11/19
//!	
//!	GameSystem.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once

#include "cocos2d.h"
#include "Radar.h"


class GameSystem : public cocos2d::Node
{
private:
	float _timer;
	float _hpBarScale;
	int _score;
	int _gameDuration;
	int _highScore;

	cocos2d::UserDefault* _pUserDefault;
	cocos2d::Label* _scoreText;
	cocos2d::Label* _timeText;
	cocos2d::Label* _plusTimeText;
	cocos2d::Sprite* _hpBarSpr;
	cocos2d::BillBoard* _billboard;
	Radar* _pRadar;

	cocos2d::Vec3 _playerPos;
	cocos2d::Vec3 _cameraPos;

	bool _start;



public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	//static cocos2d::Scene* createScene();
	CREATE_FUNC(GameSystem);


	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void setHPBarScale(float scale) { _hpBarSpr->setScaleX(scale); }
	float getHPBarScale() { return _hpBarScale; }

	void setScore(int score) { _score += score; }
	int getScore() { return _score; }
	int getHighScore() { return _highScore; }

	void update(float dt)override;
	void setBonusTime(float bonusTime);
	void setCurrentPlayerPos(const cocos2d::Vec3& pos) { _playerPos = pos; }
	void setCurrentCameraPos(const cocos2d::Vec3& pos) { _cameraPos = pos; }
	void setStartSystem(bool start) { _start = start; }
	Radar* getRadar() { return _pRadar; }
};
