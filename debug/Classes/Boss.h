#pragma once
#include"cocos2d.h"

USING_NS_CC;


class Boss:public Sprite
{
	Sprite * _player;
	Vec2 _v;
	Layer * _layer;
	Size visibleSize;
	float r;
	int life;
	int cardNum;
	int tmp;





public:


	virtual bool init(Layer * layer, Vec2 v, Sprite * s);
	static Boss * create(Layer * layer, Vec2 v, Sprite * s);


	void shotStart(float dt);

	void card_0ne();
	void card_Two();
	void card_Three();
	void card_Four();
	void card_Five();

	bool onAttack();
	int getLife();
	int getCardNum();

	void circleShot(int num,Vec2 position,int mod);

};

