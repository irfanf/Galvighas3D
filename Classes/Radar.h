//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/19
//!	
//!	Radar.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//-----------
#include "cocos2d.h"
//------------------------------------------------
class Radar : public cocos2d::Node
{
private:
	cocos2d::Sprite* _pRadarSpr;					//レーダーのスプライト
	cocos2d::Node* _pEmptyNode;						//空のノード
	cocos2d::Sprite* _pMeteorDotSpr;				//敵のドットスプライト
	float range;									//レーダー範囲

public:
	static Radar* create();
	bool init()override;
	void update(float dt)override;

	
	void createMeteorDot();							

};
//------------------------------------------------

