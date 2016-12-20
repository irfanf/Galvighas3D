#include "ReadySetGo.h"

USING_NS_CC;

ReadySetGo * ReadySetGo::create()
{
	//������
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

bool ReadySetGo::init()
{
	if (!Node::init())
	{
		return false;
	}

	//������
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_time = 0;
	_runningFlag = true;


	//�J�E���g�X�v���C�g
	_numSpr = Sprite::create("count/3.png");
	_numSpr->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(_numSpr);


	this->scheduleUpdate();
	return true;

}

bool ReadySetGo::IsRunning() const
{
	return _runningFlag;
}

void ReadySetGo::update(float dt)
{
	_time++;
	if (_runningFlag)
	{
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
			_numSpr->setVisible(false);
			_runningFlag = false;
			this->unscheduleUpdate();
			break;
		}
	}
}
