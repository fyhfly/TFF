#pragma once
#include"cocos2d.h"

USING_NS_CC;

class Bullet:public Sprite
{
private:
	Size s;
	float speedX ;
	float speedY;
	bool remove;

public:

	virtual bool init();

	CREATE_FUNC(Bullet);


	virtual void update(float dt);

	void setMod(int select, Vec2 v,float sinTmp);

	void setSpeed(float x,float y);
	

};



