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

const float PI = 3.141592f;
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
	_pRadarSpr->setOpacity(128);
	//_pRadarSpr->setRotation(45);
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
void Radar::createMeteorDot(Enemy* enemy)
{
	auto dot = Dot::create(enemy);
	_dots.push_back(dot);
	_pEmptyNode->addChild(dot);
	
}
void Radar::deleteMeteorDot(Enemy * enemy)
{
	std::list<Dot*>::iterator it;
	for (it = _dots.begin(); it != _dots.end();it++)
	{
		if ((*it)->getMeteor() == enemy)
		{
			(*it)->removeFromParent();
			_dots.erase(it);
			return;
		}
	}
}

//------------------------------------
//@! 回転の設定
//@! 見るところ
//------------------------------------
void Radar::setRadarRot(const cocos2d::Vec3& cameraPos, const cocos2d::Vec3& playerPos)
{
	Vec3 dir =  playerPos - cameraPos;

	float rad = atan2f(dir.x, dir.z);
	float deg = -((rad * 180.0f) / PI);

	_pRadarSpr->setRotation(deg);
}
