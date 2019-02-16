#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite
{
private:
	Layer * _layer;
	Sprite * _sprite;
	Vec2 _v;
	int lifePoint;
	int liveTime;


private:

public:
	virtual bool init(Layer * layer,Vec2 v,Sprite * s);
	//virtual void die();
	static Enemy * create(Layer * layer,Vec2 v, Sprite * s);
	
};
