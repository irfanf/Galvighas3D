#include "Dot.h"

USING_NS_CC;

//------------------------------------
//@! クラス作成
//------------------------------------
Dot* Dot::create(Enemy* enemy)
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
bool Dot::init(Enemy* enemy)
{
	if (!Node::init())
		return false;

	_pMeteor = enemy;

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
	_pDotSpr->setPosition(_pMeteor->getPosition3D().x, -_pMeteor->getPosition3D().z);

}
