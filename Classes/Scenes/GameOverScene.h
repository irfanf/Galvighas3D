//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/15
//!	
//!	GameOverScene.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#pragma once
//--------------------------
#include "cocos2d.h"
//--------------------------

//---------------------------------------------------------------------
class GameOverScene : public cocos2d::Layer
{
public:
	//---------------------------------------------------------------------
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int score,int highScore);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(int score,int highScore);

	static GameOverScene* create(int score, int highScore);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//---------------------------------------------------------------------
};
//---------------------------------------------------------------------

