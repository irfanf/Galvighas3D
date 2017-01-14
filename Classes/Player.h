//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/05
//!	
//!	Player.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once

//----------------------------
#include "Obj3d.h"
#include "CollisionNode.h"
//----------------------------
const int MAX_HP = 100;
//--------------------------------------------------
class Crystal : public Obj3D
{
public:
	static Crystal* create();
	virtual bool init();
	const SphereNode* GetCollisionNodeBody() { return _pCollisionNodeBody; }
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

protected:
	SphereNode* _pCollisionNodeBody;

private:
	
	Obj3D* _pCrystal;
	int _hp;
	bool debugCollision;
};