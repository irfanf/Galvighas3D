//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//!
//!	IRFAN FAHMI RAMADHAN
//!
//!	2016/11/19
//!	
//!	GameSystem.h
//!
//! Copyright ©2016 IrGame All Right Reserved
//!
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
#pragma once
//----------------------------------
#include "cocos2d.h"
#include "../Objects/Radar.h"
//----------------------------------
class GameSystem : public cocos2d::Node
{
private:
	float _timer;				//タイマー
	int _gameDuration;			//制限時間
	float _hpBarScale;			//クリスタルのＨＰゲージ
	int _score;					//スコア
	int _highScore;				//ハイスコア

	cocos2d::UserDefault* _pUserDefault;	//ユーザーデフォールト（スコアを保存ためのやつ）
	cocos2d::Label* _scoreText;				//スコアのラベル
	cocos2d::Label* _timeText;				//時間のラベル
	cocos2d::Label* _plusTimeText;			//隕石破壊できたら時間たされるためのラベル
	cocos2d::Sprite* _hpBarSpr;				//ＨＰゲージのスプライト
	cocos2d::BillBoard* _billboard;			//ビルボード
	Radar* _pRadar;							//レーダー

	cocos2d::Vec3 _crystalPos;				//クリスタルの位置			
	cocos2d::Vec3 _cameraPos;				//カメラの位置

	bool _start;							//始まっているかどうかのフラグ					



public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	//static cocos2d::Scene* createScene();
	CREATE_FUNC(GameSystem);


	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//HPゲージのスケールのSet・Get関数
	void setHPBarScale(float scale) { _hpBarSpr->setScaleX(scale); }
	float getHPBarScale() { return _hpBarScale; }

	//スコアとハイスコアのSet・Get関数
	void setScore(int score) { _score += score; }
	int getScore() { return _score; }
	int getHighScore() { return _highScore; }
	
	//更新
	void update(float dt)override;
	
	//破壊されたときのいくつたされるかの計算
	void setBonusTime(float bonusTime);

	//カメラとクリスタル
	void setCurrentCrystalPos(const cocos2d::Vec3& pos) { _crystalPos = pos; }
	void setCurrentCameraPos(const cocos2d::Vec3& pos) { _cameraPos = pos; }
	void setStartSystem(bool start) { _start = start; }
	
	//レーダーを取得
	Radar* getRadar() { return _pRadar; }
};
