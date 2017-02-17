//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/12
//!	
//!	Enemy.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//------------------------
#include "../Systems/CollisionNode.h"
#include "Obj3d.h"
//------------------------

//---------------------------------------------------------------------
class Meteor : public Obj3D
{
private:
	Obj3D* _pEnemyObj;					//敵のオブジェクト
	SphereNode* _pCollisionNodeEnemy;	//敵自体当たり判定
	cocos2d::Vec3 _targetPos;			//狙うところ

	cocos2d::Vec3 _dir;					//方向

public:
	static Meteor* create();			//関数を作成する
	void update(float dt)override;				//更新
	virtual bool init();				//初期化

	//ターゲットを決める
	void setTargetPos(cocos2d::Vec3 targetPos) { _targetPos = targetPos; }

	//当たり判定を取得
	const SphereNode* GetCollisionNodeEnemy() { return _pCollisionNodeEnemy; }

	//死ぬかどうかのチェック関数
	bool GetDeath()
	{
		if (_pEnemyObj == nullptr) return true;
		return false;
	}

	//死んだ後の処理
	void SetDeath()
	{
		if (_pEnemyObj != nullptr)
		{
			_pEnemyObj->removeFromParent();
			_pCollisionNodeEnemy->removeFromParent();
			_pEnemyObj = nullptr;
		}
	}

	
	//敵のオブジェクトを取得
	Obj3D* getObj() { return _pEnemyObj; }

	//敵の更新を呼び出す
	void callEnemyUpdate();
};
//---------------------------------------------------------------------
