//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/19
//!	
//!	Radar.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Radar.h"
//-------------------
USING_NS_CC;
//------------------------------------
//@! クラス作成
//------------------------------------
Radar* Radar::create()
{
	auto radar = new (std::nothrow) Radar();
	if (radar && radar->init())
	{
		radar->_contentSize = radar->getBoundingBox().size;

		radar->autorelease();
		return radar;
	}
	CC_SAFE_DELETE(radar);
	return nullptr;
	
}
//------------------------------------
//@! クラスの初期化
//------------------------------------
bool Radar::init()
{
	
	if (!Node::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

		
	_pEmptyNode = Node::create();
	this->addChild(_pEmptyNode);

	//レーダーのスプライトを出す
	_pRadarSpr = Sprite::create("radar/radar.png");
	_pEmptyNode->addChild(_pRadarSpr);


	//更新に進む
	this->scheduleUpdate();
	return true;
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void Radar::update(float dt)
{

}
//------------------------------------
//@! 隕石のドットスプライトを作成
//------------------------------------
void Radar::createMeteorDot()
{
	_pMeteorDotSpr = Sprite::create("radar/dotRed.png");
	_pEmptyNode->addChild(_pMeteorDotSpr);
}
