//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/09
//!	
//!	Satellite.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//------------------------------
#include "cocos2d.h"
#include "../Objects/Player.h"
//-------------------------------------------------
class Satellite : public cocos2d::Camera
{
private:
	cocos2d::Vec2 _touchPrev;		//前のタッチ座標
	Crystal* _pCrystal;				//ターゲット（プレイヤー）

public:
	// 透視投影でカメラを作成
	static Satellite* createPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// 透視投影でカメラを初期化
	bool initPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//void rotateEnable(bool flag);
};
//-------------------------------------------------
