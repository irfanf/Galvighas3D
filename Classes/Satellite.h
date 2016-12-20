#pragma once
#include "cocos2d.h"
#include "Player.h"

class Satellite : public cocos2d::Camera
{
private:
	cocos2d::Vec2 _touchPrev;
	Crystal* _pCrystal;

public:
	// �������e�ŃJ�������쐬
	static Satellite* createPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	// �������e�ŃJ������������
	bool initPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
};

