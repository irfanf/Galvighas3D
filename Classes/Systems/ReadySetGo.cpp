//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/16
//!	
//!	ReadySetGo.cpp
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "ReadySetGo.h"
//------------------------
USING_NS_CC;
//------------------------------------
//@! クラス作成
//------------------------------------
ReadySetGo * ReadySetGo::create()
{
	//メモリ
	auto rds = new (std::nothrow) ReadySetGo();
	if (rds && rds->init())
	{
		rds->_contentSize = rds->getBoundingBox().size;

		rds->autorelease();
		return rds;
	}
	CC_SAFE_DELETE(rds);
	return nullptr;

}
//------------------------------------
//@! 初期化
//------------------------------------
bool ReadySetGo::init()
{
	if (!Node::init())
	{
		return false;
	}

	//初期化
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_time = 0;
	_runningFlag = true;


	//カウントスプライト
	_numSpr = Sprite::create("count/3.png");
	_numSpr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(_numSpr);


	this->scheduleUpdate();
	return true;

}
//------------------------------------
//@! 更新
//@! 時間
//------------------------------------
void ReadySetGo::update(float dt)
{
	//時間をincrementする
	_time++;

	//カウントしたら
	if (_runningFlag)
	{
		//時間によるテクスチャーを変える
		switch (_time)
		{
		case 60:
			_numSpr->setTexture("count/2.png");
			break;
		case 120:
			_numSpr->setTexture("count/1.png");
			break;
		case 180:
			_numSpr->setTexture("count/go.png");
			break;
		case 210:
			//見えないようにする
			_numSpr->setVisible(false);
			_runningFlag = false;
			_numSpr->removeFromParent();
			this->unscheduleUpdate();
			break;
		}
	}
}
