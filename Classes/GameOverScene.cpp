#include "GameOverScene.h"
#include "TitleScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
//-------------------------------------------
USING_NS_CC;
using namespace cocostudio::timeline;
//-------------------------------------------
const float BG_SPEED = 10.0f;
const float TIME_CONVERTER = 60.0f;
const int MAX_OPACITY = 200;
//------------------------------------
//@! �N���X�쐬
//------------------------------------
Scene* GameOverScene::createScene(int score,int highScore)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create(score,highScore);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
//------------------------------------
//@! �N���X�̏�����
//------------------------------------
bool GameOverScene::init(int score,int highScore)
{
	if (!Layer::init())
	{
		return false;
	}

	//��ʃT�C�Y
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* go = Sprite::create("gameOver.png");
	go->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100.f);
	this->addChild(go);

	//�^�b�`��L���ɂ���
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	Label* pScoreLabel = Label::create("Total Score = ", "Jokerman", 50);
	pScoreLabel->setPosition(visibleSize.width/2,visibleSize.height/2 - 170.f);
	pScoreLabel->setTextColor(Color4B::YELLOW);
	this->addChild(pScoreLabel);
	String* str = String::createWithFormat("Total Score = %d", score);
	pScoreLabel->setString(str->getCString());

	Label* pHighScoreLabel = Label::create("High Score = ", "Jokerman", 50);
	pHighScoreLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100.f);
	this->addChild(pHighScoreLabel);
	String* str2 = String::createWithFormat("High Score = %d", highScore);
	pHighScoreLabel->setString(str2->getCString());

	
	return true;
}

GameOverScene* GameOverScene::create(int score,int highScore)
{
	//������
	auto go = new (std::nothrow) GameOverScene();
	if (go && go->init(score,highScore))
	{
		go->_contentSize = go->getBoundingBox().size;

		go->autorelease();
		return go;
	}

	CC_SAFE_DELETE(go);
	return nullptr;
}

//------------------------------------
//@! ���Ԃ�������,�V�[���ړ�����
//@! ����
//@! �߂�l�@bool
//------------------------------------
bool GameOverScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	//�ړ���V�[���̍쐬
	auto scene = TitleScene::createScene();
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);

	this->unscheduleAllSelectors();

	return false;
}