#include "Collision.h"

USING_NS_CC;

bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB,Vec3* inter)
{
	//���`�Ƃa�̒��S���W�̍����v�Z����
	//Vec3 sub = sphereA.center - sphereB.center;
	
	//float distance = Distance3D(sphereA.center, sphereB.center);
	float distanceSQ = Distance3DSQ(sphereA.center, sphereB.center);

	float radius_sum = sphereA.radius + sphereB.radius;

	float radius_sumSQ = radius_sum * radius_sum;

	if (distanceSQ > radius_sumSQ)
	{
		return false;
	}

	if (inter)
	{
		Vec3 sub = sphereB.center - sphereA.center;
		Vec3 BtoInter = sub * sphereB.radius / (sphereA.radius + sphereB.radius);
		*inter = sphereB.center + BtoInter;
	}

	return true;
}

bool CheckSphere2Capsule(const Sphere & sphere, const Capsule & capsule, Vec3* inter)
{
	float distance = GetSqDistancePoint2Segment(sphere.center, capsule.segment);

	float radius = sphere.radius + capsule.radius;

	if(distance > radius*radius) return false;

	if (inter)
	{
		Vec3 cpointB;

		ClosestPtPoint2Segment(sphere.center, capsule.segment, &cpointB);

		Vec3 sub = sphere.center - cpointB;

		Vec3 BtoInter = sub * capsule.radius / (sphere.radius + capsule.radius);
		
		*inter = cpointB + BtoInter;
	}

	return true;
}

bool CheckCapsule2Capsule(const Capsule & capsuleA, const Capsule & capsuleB,Vec3* inter)
{
	float distanceSQ = GetSqDistanceSegment2Segment(capsuleA.segment, capsuleB.segment);

	float radiusSum = capsuleA.radius + capsuleB.radius;
	float radiusSumSQ = radiusSum * radiusSum;

	if (distanceSQ > radiusSumSQ) return false;

	if (inter)
	{
		Vec3 cpointA, cpointB;

		ClosestPtSegment2Segment(capsuleA.segment, capsuleB.segment, &cpointA, &cpointB);
		Vec3 sub = cpointA - cpointB;

		Vec3 BtoInter = sub * capsuleB.radius / (capsuleA.radius + capsuleB.radius);
		*inter = cpointB + BtoInter;
		
	}

	return true;
}

bool CheckTouch2Sphere(const cocos2d::Vec2 & touch, const Sphere & sphere, cocos2d::Camera* camera, cocos2d::Vec3 * inter)
{

	Vec3 nearP(touch.x, touch.y, 0.0f);
	Vec3 farP(touch.x, touch.y, 1.0f);

	//3D���E���W����2D�̐��E�ɕϊ�����
	Segment segment;
	//�X�^�[�g�ƃG���h�̓_�����߂�
	segment.start = camera->unproject(nearP);
	segment.end = camera->unproject(farP);
	
	//�������擾
	Vec3 dir(segment.end - segment.start);
	dir.normalize();

	Vec3 p = sphere.center;

	Vec3 m = segment.start - p;

	//float A = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
	//float A = 1.0f;
	//float B = dir.x * p.x + dir.y * p.y + dir.z * p.z;
	float B = dir.dot(m);
	float C = m.lengthSquared() - sphere.radius * sphere.radius;

	//if (A == 0.0f)
	//	return false;

	float s = B * B - C;
	if (s < 0.0f)
		return false;

	s = sqrtf(s);
	//�O�̓_
	float a1 = -B - s;
	//���̓_
	float a2 = -B + s;

	if (a1 < 0.f || a2 < 0.f)
		return false;

	if (inter)
	{
		inter->x = segment.start.x + a1 * dir.x;
		inter->y = segment.start.y + a1 * dir.y;
		inter->z = segment.start.z + a1 * dir.z;

		Vec3 inter2;

		inter2.x = segment.start.x + a2 * dir.x;
		inter2.y = segment.start.y + a2 * dir.y;
		inter2.z = segment.start.z + a2 * dir.z;

		float distance1 = inter->distance(sphere.center);
		float distance2 = inter2.distance(sphere.center);

		static int a = 0;
		a++;
	}

	return true;
}

float Distance3DSQ(const cocos2d::Vec3& p1, const cocos2d::Vec3& p2)
{
	Vec3 sub = p1 - p2;
	return VectorLenghtSQ(sub);

}

float VectorLenghtSQ(const cocos2d::Vec3& v)
{

	float distance_x = v.x * v.x;
	float distance_y = v.y * v.y;
	float distance_z = v.z * v.z;

	float distance = distance_x + distance_y + distance_z;
	return distance;
}



//float VectorLenght(const Vec3& v)
//{
//	float distance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//	return distance;
//}



//float Distance3D(const Vec3& p1, const Vec3& p2)
//{
//	Vec3 sub = p1 - p2;
//	return VectorLenght(sub);
//}

//--------------------------------------------------------------------------------------------
// ���@�� : �_�Ɛ����̋����̓����擾
// ���@�� : _point	�_
//			_segment	����
// �߂�l : �_�Ɛ����̋����̓��
// ���@�� : ���������Z�o���Ȃ���
//	�����̒[�_��A,B	�_��C�Ƃ��āA
//	�@AB�x�N�g����AC�x�N�g���̓��ς����̎��A�_A���_C�̍ŋߖT�ł���
//	�ABA�x�N�g����BC�x�N�g���̓��ς����̎��A�_B���_C�̍ŋߖT�ł���
//	�B�@�@�A�A�ɊY�����Ȃ��ꍇ�A�_C�̎ˉe��AC�̓����ɑ��݂��邽�߁A���̓_���ŋߖT�ł���
//--------------------------------------------------------------------------------------------
float GetSqDistancePoint2Segment(const Vec3& _point, const Segment& _segment)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 SegmentSub;
	Vec3 SegmentPoint;
	Vec3 CP;

	// �����̎n�_����I�_�ւ̃x�N�g��
	SegmentSub = _segment.end - _segment.start;

	// �����̎n�_����_�ւ̃x�N�g��
	SegmentPoint = _point - _segment.start;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̎n�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// �_��������̏I�_�ւ̃x�N�g��
	SegmentPoint = _segment.end - _point;
	if (SegmentSub.dot(SegmentPoint) < epsilon)
	{// �Q�x�N�g���̓��ς����Ȃ�A�����̏I�_���ŋߖT
		return SegmentPoint.dot(SegmentPoint);
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	Vec3::cross(SegmentSub, SegmentPoint, &CP);

	return CP.dot(CP) / SegmentSub.dot(SegmentSub);
}


//--------------------------------------------------------------------------------------------
// ���@�� : �����Ɛ����̋����̓����擾
// ���@�� : _segment0	����0
//			_segment1	����1
// �߂�l : �����Ɛ����̋����̓��
// ���@�� : ���������Z�o���Ȃ���
//	�@������̍Őڋߓ_�������̐����̓����ɑ��݂��鎞
//	�A������̍Őڋߓ_������݂̂̐����̓����ɑ��݂��鎞
//	�B������̍Őڋߓ_�������̐����̊O���ɑ��݂��鎞
//	���ꂼ��̃P�[�X�œ�̐�����̍Őڋߓ_�����߁A���̋������Z�o����
//--------------------------------------------------------------------------------------------
float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 d0, d1, r;
	Vec3 c0, c1;	// ��̐�����̍Őڋߓ_
	Vec3 v;		// c1��c0�x�N�g��
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;	// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start; // ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start; // ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.dot(d0);		// ����0�̋����̓��
	e = d1.dot(d1);		// ����1�̋����̓��
						//	b = d0.dot(d1);		// �œK���̈׌���Ɉړ�����
						//	c = d0.dot(r);		// �œK���̈׌���Ɉړ�����
						//	f = d1.dot(r);		// �œK���̈׌���Ɉړ�����

						// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		v = _segment0.start - _segment1.start;

		return v.dot(v);
	}

	if (a <= epsilon)
	{// ����0������0
		return GetSqDistancePoint2Segment(_segment0.start, _segment1);
	}

	if (e <= epsilon)
	{// ����1������0
		return GetSqDistancePoint2Segment(_segment1.start, _segment0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	c0 = s * d0 + _segment0.start;
	c1 = t * d1 + _segment1.start;
	v = c0 - c1;

	return v.dot(v);
}


//--------------------------------------------------------------------------------------------
// ���@�� : �_�Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _point	�_
//			_segment	����
//			_closest	�ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtPoint2Segment(const Vec3& _point, const Segment& _segment, Vec3* _closest)
{
	Vec3 segv;
	Vec3 s2p;
	float t;

	segv = _segment.end - _segment.start;
	s2p = _point - _segment.start;
	t = segv.dot(s2p) / segv.dot(segv);

	// �����̊O���ɂ���ꍇ�At���Őڋߓ_�܂ŃN�����v
	t = Clamp(t, 0, 1);

	// �N�����v����Ă���t����̎ˉe����Ă���ʒu���v�Z
	*_closest = t * segv + _segment.start;
}

//--------------------------------------------------------------------------------------------
// ���@�� : �����Ɛ����̍ŋߐړ_���v�Z
// ���@�� : _segment0	����0
//			_segment1	����1
//			_closest0	����0��̍ŋߐړ_(���ʏo�͗p�j
//			_closest1	����1��̍ŋߐړ_(���ʏo�͗p�j
// �߂�l : �Ȃ�
// ���@�� : 
//--------------------------------------------------------------------------------------------
void ClosestPtSegment2Segment(const Segment& _segment0, const Segment& _segment1, Vec3* _closest0, Vec3* _closest1)
{
	const float epsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl
	Vec3 d0, d1, r;
	float a, b, c, e, f;
	float s, t;
	float denom;
	float tnom;

	d0 = _segment0.end - _segment0.start;		// ����0�̕����x�N�g��
	d1 = _segment1.end - _segment1.start;		// ����1�̕����x�N�g��
	r = _segment0.start - _segment1.start;	// ����1�̎n�_�������0�̎n�_�ւ̃x�N�g��
	a = d0.dot(d0);	// ����0�̋����̓��
	e = d1.dot(d1);	// ����1�̋����̓��
					//	b = d0.dot(d1);	// �œK���̈׌���Ɉړ�����
					//	c = d0.dot(r);	// �œK���̈׌���Ɉړ�����
					//	f = d1.dot(r);	// �œK���̈׌���Ɉړ�����

					// ���Âꂩ�̐����̒�����0���ǂ����`�F�b�N
	if (a <= epsilon && e <= epsilon)
	{// ��������0
		*_closest0 = _segment0.start;
		*_closest1 = _segment1.start;
		return;
	}

	if (a <= epsilon)
	{// ����0������0
		*_closest0 = _segment0.start;
		ClosestPtPoint2Segment(_segment0.start, _segment1, _closest1);
	}

	if (e <= epsilon)
	{// ����1������0
		*_closest1 = _segment1.start;
		ClosestPtPoint2Segment(_segment1.start, _segment0, _closest0);
	}

	b = d0.dot(d1);
	f = d1.dot(r);
	c = d0.dot(r);

	denom = a * e - b * b;	// ��ɔ�
							// ���������s�łȂ��ꍇ�A����0��̒���1�ɑ΂���ŋߐړ_���v�Z�A������
							// ����0��ɃN�����v�B�����łȂ��ꍇ�͔C�ӂ�s��I��
	if (denom != 0)
	{
		s = Clamp((b * f - c * e) / denom, 0, 1);
	}
	else
	{
		s = 0;
	}

	// ����1��̍Őڋߓ_���v�Z
	tnom = b * s + f;

	if (tnom < 0)
	{
		t = 0;
		s = Clamp(-c / a, 0, 1);
	}
	else if (tnom > e)
	{
		t = 1;
		s = Clamp((b - c) / a, 0, 1);
	}
	else
	{
		t = tnom / e;
	}

	*_closest0 = s * d0 + _segment0.start;
	*_closest1 = t * d1 + _segment1.start;
}


