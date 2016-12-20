//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/19
//!	
//!	Radar.h
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//-----------
#include "cocos2d.h"
//------------------------------------------------
class Radar : public cocos2d::Node
{
private:
	cocos2d::Sprite* _pRadarSpr;					//���[�_�[�̃X�v���C�g
	cocos2d::Node* _pEmptyNode;						//��̃m�[�h
	cocos2d::Sprite* _pMeteorDotSpr;				//�G�̃h�b�g�X�v���C�g
	float range;									//���[�_�[�͈�

public:
	static Radar* create();
	bool init()override;
	void update(float dt)override;

	
	void createMeteorDot();							

};
//------------------------------------------------

