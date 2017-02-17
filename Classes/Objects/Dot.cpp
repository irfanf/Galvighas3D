//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2017/1/14
//!	
//!	Dot.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Dot.h"

USING_NS_CC;

//------------------------------------
//@! クラス作成
//------------------------------------
Dot* Dot::create(Meteor* enemy)
{
	auto dot = new (std::nothrow) Dot();
	if (dot && dot->init(enemy))
	{
		dot->_contentSize = dot->getBoundingBox().size;

		dot->autorelease();
		return dot;
	}
	CC_SAFE_DELETE(dot);
	return nullptr;

}
//------------------------------------
//@! クラスの初期化
//------------------------------------
bool Dot::init(Meteor* meteor)
{
	if (!Node::init())
		return false;

	_pMeteor = meteor;

	//スプライト
	_pDotSpr = Sprite::create("radar/dotRed.png");
	_pDotSpr->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(_pDotSpr);

	//更新に進む
	this->scheduleUpdate();
	return true;
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void Dot::update(float dt)
{
	//座標をずっと更新される
	_pDotSpr->setPosition(_pMeteor->getPosition3D().x, -_pMeteor->getPosition3D().z);

}
