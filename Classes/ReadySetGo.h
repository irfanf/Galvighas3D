//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/16
//!	
//!	ReadySetGo.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//------------------
#include "cocos2d.h"
//----------------------------------------
class ReadySetGo : public cocos2d::Node
{
private:
	cocos2d::Sprite* _numSpr;			//スプライト

	bool _runningFlag;					//カウントしてるかどうかのフラグ
	int _time;							//時間


public:
	//-----------------------------------
	static ReadySetGo* create();
	void update(float dt)override;
	virtual bool init()override;
	//-----------------------------------
	//カウントしてるかどうかを返す
	bool IsRunning()const { return _runningFlag; }
};

