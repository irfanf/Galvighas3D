//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/09
//!	
//!	Satellite.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Satellite.h"
//---------------------
USING_NS_CC;
//---------------------
const float SATELLITE_CAMERA_RANGE = 5.f;
//------------------------------------
//@! クラス作成
//@! Target, FieldOfView, AspectRatio, NearPlane, FarPlane
//@! Satellite Camera
//------------------------------------
Satellite* Satellite::createPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	auto ret = new (std::nothrow) Satellite();
	if (ret)
	{
		ret->initPerspective(crystal, fieldOfView, aspectRatio, nearPlane, farPlane);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
//------------------------------------
//@! 初期化
//@! Target, FieldOfView, AspectRatio, NearPlane, FarPlane
//------------------------------------
bool Satellite::initPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	//CameraのinitPerspectiveじゃなければ、処理しない
	if (!Camera::initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane))
		return false;

	//ターゲットを設定する
	_pCrystal = crystal;
	setPosition3D(Vec3(0.0f, 2.f, 5.0f));
	//ターゲットの方に見る
	auto lookAt = crystal->getPosition3D();


	//初期設定-----------------------------------------------------------------------------
	//カメラの設定をする
	Vec3 cameraPos = Vec3(0.0f, 1.0f, 5.0f);
	//回転する
	cameraPos.x = cosf(0.0f) * SATELLITE_CAMERA_RANGE;
	cameraPos.z = sinf(0.0f) * SATELLITE_CAMERA_RANGE;
	this->setPosition3D(cameraPos);
	this->lookAt(Vec3(lookAt.x, lookAt.y + 1.f, lookAt.z));
	//--------------------------------------------------------------------------------------

	auto touchLis = EventListenerTouchOneByOne::create();
	touchLis->onTouchBegan = CC_CALLBACK_2(Satellite::onTouchBegan, this);
	touchLis->onTouchMoved = CC_CALLBACK_2(Satellite::onTouchMoved, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLis, this);

	return true;
}
//------------------------------------
//@! タッチするときの処理
//@! タッチとイベント
//------------------------------------
bool Satellite::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	_touchPrev = touch->getLocation();
	return true;
}
//------------------------------------
//@! タッチを動かす時
//@! タッチとイベント
//------------------------------------
void Satellite::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//回転の初期化
	static float rotate = 0.0f;

	//ターゲットの座標を取得
	Vec3 lookAt = _pCrystal->getPosition3D();
	
	//カメラの座標を設定する
	Vec3 cameraPos = this->getPosition3D();
	//回転をする
	cameraPos.x = cosf(rotate) * SATELLITE_CAMERA_RANGE;
	cameraPos.z = sinf(rotate) * SATELLITE_CAMERA_RANGE;
	this->setPosition3D(cameraPos);
	//回転してもターゲットをずっと見る
	this->lookAt(Vec3(lookAt.x, lookAt.y + 1.f, lookAt.z));

	//前のタッチした画面に戻らないようにする
	rotate += (_touchPrev - touch->getLocation()).x / 100.f;
	_touchPrev = touch->getLocation();
}


