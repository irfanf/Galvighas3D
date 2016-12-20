#pragma once

#include"cocos2d.h"
//#include"HelloWorldScene.h"
class Obj3D : public cocos2d::Sprite3D
{
public:
	cocos2d::Sprite3D* getSprite3D() { return m_spr3D; }

	static Obj3D* create(const std::string&modelPath);

	bool initWithFile(const std::string& path);

	void playAnimation(const std::string& filename, bool isLoop = false);

	void stopAnimation();
 
 const cocos2d::Mat4& getNodeToParentTransform()const override;

 void setLightMask(unsigned int mask);

private:
	cocos2d::RepeatForever* _rep;
	cocos2d::Sprite3D* m_spr3D;
};