#pragma once
#include"cocos2d.h"

USING_NS_CC;

class PlayerBullet:public Sprite
{
private:
	Size s;
	int speedX;
	int speedY;
	bool remove;
public:

	virtual bool init();

	CREATE_FUNC(PlayerBullet);


	virtual void update(float dt);

};

