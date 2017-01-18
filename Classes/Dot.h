//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2017/1/14
//!	
//!	Dot.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once

#include "cocos2d.h"
#include "Enemy.h"

class Dot : public cocos2d::Node
{
	cocos2d::Sprite* _pDotSpr;			//ドットのスプライト
	Meteor* _pMeteor;					//隕石の情報を得るため



public:
	static Dot* create(Meteor* enemy);	
	bool init(Meteor* enemy);
	void update(float dt)override;

	//隕石を取得
	Meteor* getMeteor()const { return _pMeteor; }	
	//ドットのスプライトを取得
	cocos2d::Sprite* getDotSpr()const { return _pDotSpr; }
};

