#pragma once

#include <cocos2d.h>

class Sphere
{
public:
	cocos2d::Vec3 center;
	float radius;
	Sphere()
	{
		radius = 1.0f;
	}
};

class Segment
{
public:
	cocos2d::Vec3 start;
	cocos2d::Vec3 end;
};

class Capsule
{
public:
	Segment segment;
	float radius;

	Capsule()
	{
		segment.start = cocos2d::Vec3(0.f, 0.f, 0.f);
		segment.end = cocos2d::Vec3(0.f, 1.f, 0.f);
		radius = 1.f;
	}
};
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, cocos2d::Vec3* inter = nullptr);
bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, cocos2d::Vec3* inter = nullptr);
bool CheckCapsule2Capsule(const Capsule& capsuleA, const Capsule& capsuleB, cocos2d::Vec3* inter = nullptr);
bool CheckTouch2Sphere(const cocos2d::Vec2& touch, const Sphere& sphere, cocos2d::Camera* camera, cocos2d::Vec3* inter = nullptr);

inline float Clamp(float _x, float _min, float _max) { return std::min(std::max(_x, _min), _max); }

void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, cocos2d::Vec3* _closest0, cocos2d::Vec3* _closest1);
void ClosestPtPoint2Segment(const cocos2d::Vec3& _point, const Segment& _segment, cocos2d::Vec3* _closest);
float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1);
float GetSqDistancePoint2Segment(const cocos2d::Vec3& _point, const Segment& _segment);
float Distance3DSQ(const cocos2d::Vec3& p1, const cocos2d::Vec3& p2);
float VectorLenghtSQ(const cocos2d::Vec3& v);