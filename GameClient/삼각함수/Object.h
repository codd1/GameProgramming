#pragma once

enum class ObjectType {
	None,
	Player,
	Monster,
	Projectile		// ����ü
};

class Object
{
public:
	Object(ObjectType type);
	virtual ~Object();

public:
	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
public:
	ObjectType GetObjectType() { return _type; }

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }

	float SetRadius(float radius) { _radius = radius; }
	float GetRadius() { return _radius; }

protected:
	ObjectType _type = ObjectType::None;
	Stat _stat = {};
	Pos _pos = {};
	Dir _dir = Dir::Left;
	float _radius = 50.f;
};

