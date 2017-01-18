//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/10
//!	
//!	HelloWorldScene.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//----------------------------------
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include "GameSystem.h"
#include "Satellite.h"
//----------------------------------

class Obj3D;
class ReadySetGo;

//今動いているシーン
enum RunningScene
{
	CUT_IN,
	PLAY,
	OVER,
	CLEAR,
};
//メインクラス
class HelloWorld : public cocos2d::Layer
{
private:
	Obj3D* _pSkydome;						//Skydome
	Crystal* _pCrystal;						//クリスタル
	std::vector<Meteor*> _pMeteors;			//隕石
	GameSystem* _pGameSystem;				//ゲームシステム
	cocos2d::Vec2 _touchPos;				//タッチ座標
	Satellite* _pSatellite;					//カメラ
	ReadySetGo* _pRDS;						//カウント


	RunningScene _scene;					//今動いてるシーン

	float _spawnRate;						//隕石が出るレート
	int _meteorNum;							//隕石の数
	float _time;							//時間(秒）
	
	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)override;

	void update(float dt)override;

	void createMeteor();

	void onCutIn();
	void onPlay();
	void goToGameOver();
};

#endif // __HELLOWORLD_SCENE_H__
