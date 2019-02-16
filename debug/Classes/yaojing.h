#pragma once
#include"cocos2d.h"
#include"Enemy.h"
#include"Bullet.h"

USING_NS_CC;

class yaojing:public Enemy
{
private:
	Sprite * _player;
	Vec2 _v;
	Layer * _layer;
	bool isDie;
	bool haveDiedBomb;
	int ModNum;
	int next;
	int life;
	float sinTmp;
	int wait;
public:
	virtual bool init(Layer * layer, Vec2 v, Sprite * s, int mod,int enemyMod);
	static yaojing * create(Layer * layer, Vec2 v, Sprite * s, int mod, int enemyMod);

	void setMod(int select);

	void shotStart(float dt);

	bool onAttack();

	//void setLife(int l);

	void setNext(int n);

	void circleShot(int num);

	void setEnemyMode(int enemyMode);

	void setHaveDiedBomb(bool h);
	bool getHaveDiedBomb();

};

