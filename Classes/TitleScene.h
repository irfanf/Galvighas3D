#pragma once
#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
private:
	float _time;
	float _opacity;
	float _startOpacity;

	cocos2d::Sprite* _titleName;
	cocos2d::Sprite* _start;
public:
	//---------------------------------------------------------------------
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);

	void update(float dt)override;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//---------------------------------------------------------------------

};

