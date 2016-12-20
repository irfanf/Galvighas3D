#include "Satellite.h"

USING_NS_CC;



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

bool Satellite::initPerspective(Crystal* crystal, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{

	if (!Camera::initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane))
	{
		return false;
	}

	_pCrystal = crystal;
	setPosition3D(Vec3(0.0f, 2.f, 5.0f));

	auto lookAt = crystal->getPosition3D();

	Vec3 cameraPos = Vec3(0.0f, 1.0f, 5.0f);
	cameraPos.x = cosf(0.0f)*5.0f;
	cameraPos.z = sinf(0.0f)*5.0f;
	this->setPosition3D(cameraPos);
	this->lookAt(Vec3(lookAt.x, lookAt.y + 1.f, lookAt.z));

	auto touchLis = EventListenerTouchOneByOne::create();
	touchLis->onTouchBegan = CC_CALLBACK_2(Satellite::onTouchBegan, this);
	touchLis->onTouchMoved = CC_CALLBACK_2(Satellite::onTouchMoved, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLis, this);

	return true;
}

bool Satellite::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	_touchPrev = touch->getLocation();
	return true;
}

void Satellite::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	static float rotate = 0.0f;
	auto camera = this;
	auto lookAt = _pCrystal->getPosition3D();

	auto cameraPos = camera->getPosition3D();
	cameraPos.x = cosf(rotate)*5.0f;
	cameraPos.z = sinf(rotate)*5.0f;
	camera->setPosition3D(cameraPos);
	camera->lookAt(Vec3(lookAt.x, lookAt.y + 1.f, lookAt.z));

	rotate += (_touchPrev - touch->getLocation()).x / 100.f;
	_touchPrev = touch->getLocation();
}


