#pragma once

#include "cocos2d.h"
#include "Enemy.h"

class Dot : public cocos2d::Node
{
	cocos2d::Sprite* _pDotSpr;
	Enemy* _pMeteor;



public:
	static Dot* create(Enemy* enemy);
	bool init(Enemy* enemy);
	void update(float dt)override;

	Enemy* getMeteor()const { return _pMeteor; }
	cocos2d::Sprite* getDotSpr()const { return _pDotSpr; }
};

