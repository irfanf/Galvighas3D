#pragma once
#include "cocos2d.h"

class ReadySetGo : public cocos2d::Node
{
private:
	cocos2d::Sprite* _numSpr;

	bool _runningFlag;
	int _time;


public:
	static ReadySetGo* create();
	void update(float dt)override;
	virtual bool init();

	bool IsRunning()const;

};

