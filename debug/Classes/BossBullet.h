#pragma once
#include"cocos2d.h"

USING_NS_CC;

class BossBullet : public Sprite
{
private:
	Sprite * player;
	Size s;
	float speedX;
	float speedY;
	bool remove;

public:

	virtual bool init();

	CREATE_FUNC(BossBullet);


	virtual void update(float dt);

	void setSpeed(float x, float y);

};

