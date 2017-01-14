//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/19
//!	
//!	Radar.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//------------------
#include "cocos2d.h"
#include "Enemy.h"
#include "Dot.h"
//------------------------------------------------
class Radar : public cocos2d::Node
{
private:
	cocos2d::Sprite* _pRadarSpr;					//レーダーのスプライト
	cocos2d::Node* _pEmptyNode;						//空のノード
	float range;									//レーダー範囲

	std::list<Dot*> _dots;

public:
	void setRadarRot(const cocos2d::Vec3& cameraPos,const cocos2d::Vec3& playerPos);
	static Radar* create();
	bool init()override;
	void update(float dt)override;
	void createMeteorDot(Enemy* enemy);
	void deleteMeteorDot(Enemy* enemy);




};
//------------------------------------------------

