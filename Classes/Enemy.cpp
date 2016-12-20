//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/12
//!	
//!	Enemy.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Enemy.h"
//----------------
USING_NS_CC;
//------------------------------------
//@! クラス作成
//------------------------------------
Enemy * Enemy::create()
{
	auto obj3d = new (std::nothrow) Enemy();
	if (obj3d && obj3d->init())
	{
		obj3d->_contentSize = obj3d->getBoundingBox().size;

		obj3d->autorelease();
		return obj3d;
	}
	CC_SAFE_DELETE(obj3d);
	return nullptr;

}
//------------------------------------
//@! クラスの初期化
//------------------------------------
bool Enemy::init()
{
	if (!Obj3D::init())
	{
		return false;
	}

	//敵のスピードを設定する
	float speed = (rand() % 10) + 5;

	//敵のオブジェクトの作成
	_pEnemyObj = Obj3D::create("enemy/asteroid.c3b");
	this->addChild(_pEnemyObj);

	//敵の当たり判定をつける
	_pCollisionNodeEnemy = SphereNode::create();
	_pCollisionNodeEnemy->SetRadius(1.5f);
	_pCollisionNodeEnemy->setPosition3D(Vec3(_pEnemyObj->getPosition3D().x, _pEnemyObj->getPosition3D().y + 1, _pEnemyObj->getPosition3D().z));
	this->addChild(_pCollisionNodeEnemy);

	//方向の初期化
	_dir = Vec3(5344, 9321,12312).getNormalized();
	
	this->scheduleUpdate();
	return true;

}
//------------------------------------
//@! 更新を呼び出す
//------------------------------------
void Enemy::callEnemyUpdate()
{
	_pCollisionNodeEnemy->update(0.0f);
}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void Enemy::update(float dt)
{
	
	//スピード
	float speed = 0.25f;
	//誘導係数
	float coef = 0.05f;

	//座標を取得
	Vec3 currentPos = this->getPosition3D();
	//距離を計算する
	Vec3 dir = _targetPos - currentPos;
	//方向を決める(正規化）
	dir.normalize();
	// 旋回角度を制限する
	_dir = _dir * (1.0f - coef) + dir * coef;
	//正規化する
	_dir.normalize();

	//移動を方向とスピードを計算する
	auto mover = _dir*speed;
	//座標をずらす
	currentPos += mover;

	//動かす
	this->setPosition3D(currentPos);
}
