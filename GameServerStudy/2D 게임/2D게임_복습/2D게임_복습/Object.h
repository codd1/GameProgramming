#pragma once

// 12. Object 클래스 생성 (순수가상함수)
enum class ObjectType {
	None,
	Player,
	Monster,
	Projectile		// 투사체
};

class Object
{
public:
	Object(ObjectType type);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

public:
	ObjectType GetObjectType() { return _type; }

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	// 81. 필요한 멤버변수, 메소드 추가
	void SetRadius(float radius) { _radius = radius; }
	float GetRadius() { return _radius; }

protected:
	ObjectType _type = ObjectType::None;
	Pos _pos = {};

	Stat _stat = {};
	
	Dir _dir = Dir::Left;

	float _radius = 50.f;	// Bullet (반지름) 크기
};

