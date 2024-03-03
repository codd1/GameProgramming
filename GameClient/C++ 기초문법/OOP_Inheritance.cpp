#include <iostream>
using namespace std;

// 객체지향 (Object Oriented Programming)
// 데이터 + 로직

/*
	OOP 3대 요소
	- 상속성 (Is-A vs Has-A)
	- 은닉성
	- 다형성
*/

/* 
	GameObject
	- Creature
		- Player, Monster, Npc, Pet
	- Projectile (투사체)
		- Arrow, Fireball
	- Env (수집품)
*/

/*
	Item
	- Weapon
		- Sword, Bow, Lance
	- Armor
		- Helmet, Boots, Armor, Glove
	- Consumable
		- Potion, Scroll
*/

class Player {
public:
	void Move() {}
	void Attack() {}
	void Die() {}

public:
	int m_hp;
	int m_attack;
	int m_defence;
};

class Knight : public Player {
public:

public:
	int m_stemina;
};

class Archer : public Player {
public:

public:
	int m_arrowCount;
};

class Mage : public Player {
public:

public:
	int m_mp;
};

void Fight(Player* p1, Player* p2) {
	p1->m_hp -= p2->m_attack;
}

int main() {
	Knight k1;
	Player* p1 = &k1;

	Mage m1;
	Player* p2 = &m1;

	Fight(&k1, &m1);
}