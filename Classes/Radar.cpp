//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/12/19
//!	
//!	Radar.cpp
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#include "Radar.h"
//-------------------
USING_NS_CC;
//------------------------------------
//@! �N���X�쐬
//------------------------------------
Radar* Radar::create()
{
	auto radar = new (std::nothrow) Radar();
	if (radar && radar->init())
	{
		radar->_contentSize = radar->getBoundingBox().size;

		radar->autorelease();
		return radar;
	}
	CC_SAFE_DELETE(radar);
	return nullptr;
	
}
//------------------------------------
//@! �N���X�̏�����
//------------------------------------
bool Radar::init()
{
	
	if (!Node::init())
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

		
	_pEmptyNode = Node::create();
	this->addChild(_pEmptyNode);

	//���[�_�[�̃X�v���C�g���o��
	_pRadarSpr = Sprite::create("radar/radar.png");
	_pEmptyNode->addChild(_pRadarSpr);


	//�X�V�ɐi��
	this->scheduleUpdate();
	return true;
}
//------------------------------------
//@! �X�V
//@! ����
//------------------------------------
void Radar::update(float dt)
{

}
//------------------------------------
//@! 覐΂̃h�b�g�X�v���C�g���쐬
//------------------------------------
void Radar::createMeteorDot()
{
	_pMeteorDotSpr = Sprite::create("radar/dotRed.png");
	_pEmptyNode->addChild(_pMeteorDotSpr);
}
