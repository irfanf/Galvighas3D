#include "HelloWorldScene.h"
#include "../Objects/Obj3d.h"
#include "../Systems/ReadySetGo.h"
#include "Particle3D\PU\CCPUParticleSystem3D.h"
#include "GameOverScene.h"
#include "audio\include\AudioEngine.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{   
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	srand((unsigned int)time(NULL));

	_spawnRate = 2;
	_meteorNum = 0;
	_time = 0;
	_scene = CUT_IN;

	experimental::AudioEngine::stopAll();
	int bgm = experimental::AudioEngine::play2d("sounds/bgm.mp3");
	experimental::AudioEngine::setLoop(bgm, true);

	_pCrystal = Crystal::create();
	_pCrystal->setPosition3D(Vec3(0.f,-1.f,0.f));
	_pCrystal->setHP(MAX_HP);
	this->addChild(_pCrystal);

	_pSkydome = Obj3D::create("skydome/skydome.c3b");
	this->addChild(_pSkydome);
	
	_pSatellite = Satellite::createPerspective(_pCrystal, 60.0f, 800.0f / 450.0f, 0.1f, 1000.0f);
	_pSatellite->setCameraFlag(CameraFlag::USER1);
	this->addChild(_pSatellite);

	_pGameSystem = GameSystem::create();
	_pGameSystem->setCameraMask((unsigned short)CameraFlag::USER1);
	_pGameSystem->setStartSystem(false);
	this->addChild(_pGameSystem);

	//���̕����x�N�g��
	Vec3 dLightDirection(1.0f, -1.0f, -1.0f);
	//���̓���
	Color3B dLightColor(0xff, 0xff, 0xff);
	//���s�����̍쐬
	DirectionLight* directionLight = DirectionLight::create(dLightDirection, dLightColor);
	//���C�g���O�ԂɊ���U��
	directionLight->setLightFlag(LightFlag::LIGHT0);
	this->addChild(directionLight);

	//���̐F
	Color3B aLightColor(0x40, 0x40, 0x40);
	//�������̍쐬
	AmbientLight* ambient = AmbientLight::create(aLightColor);
	//���C�g��0�ԂɊ���U��
	ambient->setLightFlag(LightFlag::LIGHT0);
	this->addChild(ambient);

	//�V���̃��C�e�B���O�𖳌��ɂ���
	_pSkydome->setLightMask(0);

	_pRDS = ReadySetGo::create();
	this->addChild(_pRDS);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	//createAsteroid(Meteor);
	//createAsteroid(Meteor);
	//createAsteroid(Meteor);

	this->scheduleUpdate();

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	//�^�b�`���W���擾
	_touchPos = touch->getLocationInView();
	

	for (int i = 0; i < _pMeteors.size(); )
	{
		//�����Ă��邩�ǂ����̊m�F
		if (_pMeteors[i]->GetDeath()) continue;

		//���ꂼ���覐΂ɓ����蔻����擾
		const Sphere* enemySphere = _pMeteors[i]->GetCollisionNodeEnemy();

		Vec3 inter;

		//�����蔻��
		if (CheckTouch2Sphere(_touchPos, *enemySphere, _pSatellite, &inter))
		{
			log("Touched");

			//�������������------------------------------------------
			_pGameSystem->getRadar()->deleteMeteorDot(_pMeteors[i]);
			_pMeteors[i]->SetDeath();
			_pMeteors.erase(_pMeteors.begin() + i);       //  3�Ԗڂ̗v�f�i9�j���폜
			//�������炷
			_meteorNum--;

			int exp = experimental::AudioEngine::play2d("sounds/explode.mp3");
			
			_spawnRate -= 0.075f;
			_pGameSystem->setBonusTime(1);
			_pGameSystem->setScore(100);
			//--------------------------------------------------------
			log("%f", _spawnRate);

			//�p�[�e�B�N��������
			PUParticleSystem3D* particle = PUParticleSystem3D::create("particle/explosionSystem.pu");
			particle->setPosition3D(inter);
			particle->setScale(0.1f);
			particle->startParticleSystem();
			particle->setCameraMask((unsigned short)CameraFlag::USER1);
			this->addChild(particle, 0);

			//3�b�ɂȂ�����p�[�e�B�N��������
			DelayTime* dl = DelayTime::create(3);
			RemoveSelf* removeSelf = RemoveSelf::create();
			Sequence* seq = Sequence::create(dl, removeSelf, nullptr);
			particle->runAction(seq);
		}
		else
			i++;
		
	}

	return false;
}
//-----------------------------
//!@ �X�V
//!@ ����
//-----------------------------
void HelloWorld::update(float dt)
{
	switch (_scene)
	{
	case CUT_IN:
		onCutIn();
		break;
	case PLAY:
		onPlay();
		break;
	case OVER:
		goToGameOver();
		break;
	case CLEAR:
		break;
	default:
		break;
	}

}

void HelloWorld::createMeteor()
{

	float x = random(-200, 200);
	float z = random(-200, 200);

	//覐Γo�^����
	_pMeteors.push_back(Meteor::create());

	//覐΂̐��𐔂���
	_meteorNum++;
	
	std::vector<Meteor*>::iterator p = _pMeteors.begin();

	for (int i = 0; i < _meteorNum - 1; i++)
	{
		p++;
	}
	
	auto obj = *p;
	obj->setPosition3D(Vec3(x, 0.0f, z));
	obj->setTargetPos(_pCrystal->getPosition3D());
	this->addChild(obj);
	obj->callEnemyUpdate();

	_pGameSystem->getRadar()->createMeteorDot(obj);

}

void HelloWorld::onCutIn()
{
	if (!_pRDS->IsRunning())
	{
		_pGameSystem->setStartSystem(true);
		_scene = PLAY;
	}
}

void HelloWorld::onPlay()
{

	//����
	_time++;


	//覐΂��o���^�C�~���O
	if (_time > 60 * _spawnRate)
	{
		createMeteor();
		_time = 0;
	}

	//覐΂̃^�C�~���O���[�g
	if (_spawnRate < 0.5f)
	{
		_spawnRate = 0.5f;
	}

	float hp = _pCrystal->getHP();

	if (hp <= 0)
	{
		_scene = OVER;
	}

	//�����蔻��
	if (_pCrystal->GetCollisionNodeBody())
	{
		const Sphere* crystalSphere = _pCrystal->GetCollisionNodeBody();
		for (int i = 0; i < _pMeteors.size(); )
		{
			if (_pMeteors[i]->GetDeath()) continue;

			const Sphere* enemySphere = _pMeteors[i]->GetCollisionNodeEnemy();

			Vec3 inter;

			if (CheckSphere2Sphere(*enemySphere, *crystalSphere, &inter))
			{
				log("Hit");

				//---------------------------------------------------------------
				_pGameSystem->getRadar()->deleteMeteorDot(_pMeteors[i]);
				_pMeteors[i]->SetDeath();
				_pMeteors.erase(_pMeteors.begin() + i);       //  3�Ԗڂ̗v�f�i9�j���폜
				_meteorNum--;
				//--------------------------------------------------------------

				int exp = experimental::AudioEngine::play2d("sounds/explode.mp3");

				hp -= 10;

				PUParticleSystem3D* particle = PUParticleSystem3D::create("particle/explosionSystem.pu");
				particle->setPosition3D(inter);
				particle->setScale(0.1f);
				particle->startParticleSystem();
				particle->setCameraMask((unsigned short)CameraFlag::USER1);
				this->addChild(particle, 0);

				DelayTime* dl = DelayTime::create(3);
				RemoveSelf* removeSelf = RemoveSelf::create();

				Sequence* seq = Sequence::create(dl, removeSelf, nullptr);
				particle->runAction(seq);
			}
			else
			{
				i++;
			}
		}
	}

	float hpScale = _pGameSystem->getHPBarScale();
	hpScale = hp / MAX_HP;

	_pCrystal->setHP(hp);
	_pGameSystem->setHPBarScale(hpScale);
	_pGameSystem->setCurrentCameraPos(_pSatellite->getPosition3D());
	_pGameSystem->setCurrentCrystalPos(_pCrystal->getPosition3D());
}

void HelloWorld::goToGameOver()
{
	auto scene = GameOverScene::createScene(_pGameSystem->getScore(), _pGameSystem->getHighScore());
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);

	this->unscheduleAllSelectors();
}
