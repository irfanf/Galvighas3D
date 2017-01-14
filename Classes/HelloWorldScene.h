#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include "GameSystem.h"
#include "Satellite.h"


class Obj3D;
class ReadySetGo;

enum RunningScene
{
	CUT_IN,
	PLAY,
	OVER,
	CLEAR,
};

class HelloWorld : public cocos2d::Layer
{
private:
	Obj3D* _pSkydome;
	Crystal* _pCrystal;
	std::vector<Enemy*> _pMeteors;
	GameSystem* _pGameSystem;
	cocos2d::Vec2 _touchPos;
	Satellite* _pSatellite;
	ReadySetGo* _pRDS;


	RunningScene _scene;

	float _spawnRate;
	int _meteorNum;
	float _time;
	
	
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)override;

	void update(float dt)override;

	void createAsteroid(Type type);

	void onCutIn();
	void onPlay();
	void gameOver();

	//bool onCollision2Crystal();
	//bool onCollision2Touch();

};

#endif // __HELLOWORLD_SCENE_H__
