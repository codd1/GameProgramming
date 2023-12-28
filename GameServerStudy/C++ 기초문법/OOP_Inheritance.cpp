#include <iostream>
using namespace std;

// ��ü���� (Object Oriented Programming)
// ������ + ����

/*
	OOP 3�� ���
	- ��Ӽ� (Is-A vs Has-A)
	- ���м�
	- ������
*/

/* 
	GameObject
	- Creature
		- Player, Monster, Npc, Pet
	- Projectile (����ü)
		- Arrow, Fireball
	- Env (����ǰ)
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