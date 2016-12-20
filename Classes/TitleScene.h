//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/07
//!	
//!	TitleScene.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
#include "cocos2d.h"
//---------------------------------------------------
class TitleScene : public cocos2d::Layer
{
private:
	float _time;					//時間
	float _opacity;					//透明度
	float _startOpacity;			//透明度の初期値

	cocos2d::Sprite* _titleName;	//タイトル名のスプライト
	cocos2d::Sprite* _start;		//スタートのスプライト
public:
	//---------------------------------------------------------------------
	static cocos2d::Scene* createScene();
	virtual bool init()override;
	CREATE_FUNC(TitleScene);
	void update(float dt)override;
	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//---------------------------------------------------------------------

};

