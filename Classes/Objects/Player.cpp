//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/05
//!	
//!	Player.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Player.h"

USING_NS_CC;

#define MAX_SHIELD_SCALE 0.02f
#define MIN_SHIELD_SCALE 0.01f

Crystal * Crystal::create()
{
	//メモリ
	auto player = new (std::nothrow) Crystal();
	if (player && player->init())
	{
		player->_contentSize = player->getBoundingBox().size;

		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;

}

bool Crystal::init()
{
	if (!Obj3D::init())
	{
		return false;
	}

	//HPの初期化
	_hp = MAX_HP;

	_pCrystal = Obj3D::create("crystal/crystal.c3b");
	_pCrystal->setScale(0.05);
	this->addChild(_pCrystal);

	{
		_pCollisionNodeBody = SphereNode::create();
		_pCollisionNodeBody->SetRadius(1.5f);
		_pCollisionNodeBody->setPosition3D(Vec3(0.f,1.5f,0.f));
		this->addChild(_pCollisionNodeBody);

	}


	//行列----------------------------
	Mat4 transm;
	Mat4::createTranslation(_position.x, _position.y, _positionZ, &transm);
	_transform = Mat4::IDENTITY;
	_transform *= transm;


	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Crystal::onKeyPressed, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();
	return true;

}

void Crystal::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{

	switch (keyCode)
	{
	
	case EventKeyboard::KeyCode::KEY_1:
		if (CollisionNode::GetDebugVisible())
			CollisionNode::SetDebugVisible(false);
		else 
			CollisionNode::SetDebugVisible(true);
		
		break;
	}
}
