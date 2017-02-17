//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/11/24
//!	
//!	Obj3d.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Obj3d.h"


USING_NS_CC;

//オブジェクトの生成
Obj3D * Obj3D::create(const std::string & modelPath)
{
	CCASSERT(modelPath.length() >= 4, "invalid filename for Sprite3D");

	//メモリ
	auto obj3d = new (std::nothrow) Obj3D();
	if (obj3d && obj3d->initWithFile(modelPath))
	{
		obj3d->_contentSize = obj3d->getBoundingBox().size;

		obj3d->autorelease();
		return obj3d;
	}
	CC_SAFE_DELETE(obj3d);
	return nullptr;

}


bool Obj3D::initWithFile(const std::string & path)
{
	if (!Sprite3D::init())
	{
		return false;
	}
	m_spr3D = Sprite3D::create(path);
	this->addChild(m_spr3D);
	m_spr3D->setCameraMask((unsigned short)CameraFlag::USER1);
	//ライト０番を指定
	m_spr3D->setLightMask((unsigned int)LightFlag::LIGHT0);


	return true;
}

void Obj3D::playAnimation(const std::string & filename, bool isLoop)
{
	Animation3D* animation = Animation3D::create(filename, "mixamo.com");
	Animate3D* animate = Animate3D::create(animation);

	if (isLoop)
	{
		m_spr3D->runAction(RepeatForever::create(animate));
	}
	else
	{
		m_spr3D->runAction(animate);
	}


}

void Obj3D::stopAnimation()
{
	if(m_spr3D != nullptr)
	m_spr3D->stopAllActions();
}

const cocos2d::Mat4 & Obj3D::getNodeToParentTransform() const
{
	Mat4 scalem;

	Mat4::createScale(_scaleX, _scaleY, _scaleZ, &scalem);

	Mat4 rotm_z;
	Mat4::createRotationZ(CC_DEGREES_TO_RADIANS(_rotationZ_X), &rotm_z);

	Mat4 rotm_x;
	Mat4::createRotationX(CC_DEGREES_TO_RADIANS(_rotationX), &rotm_x);

	Mat4 rotm_y;
	Mat4::createRotationY(CC_DEGREES_TO_RADIANS(_rotationY), &rotm_y);

	Mat4 rotm = Mat4::IDENTITY;
	rotm *= rotm_y;
	rotm *= rotm_x;
	rotm *= rotm_z;

	Mat4 transm;
	Mat4::createTranslation(_position.x, _position.y, _positionZ, &transm);

	_transform = Mat4::IDENTITY;
	_transform *= transm;
	_transform *= rotm;
	_transform *= scalem;

	return _transform;
	// TODO: return ステートメントをここに挿入します
}
void Obj3D::setLightMask(unsigned int mask)
{
	//sprite3Dのライト番号をセット
	m_spr3D->setLightMask(mask);

}

