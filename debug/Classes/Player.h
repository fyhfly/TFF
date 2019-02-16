#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite
{
private:
	cocos2d::Size visibleSize;
	EventListenerKeyboard * listenerKeyboard;
	Sprite* boomSprite;
	Size reallyBody;
	Vec2 initPosition = Vec2(300,300);
	Layer* _layer;
	bool ableBomb;
	int tempPasue;
	int life;
	int boom = 2;
	int boomRadius;
	bool isGameOver;
	int speed;
public:
	 virtual bool init(Layer * layer);

	static Player* create(Layer * layer);


	virtual void planeMoveR(float dt);
	virtual void planeMoveL(float dt);
	virtual void planeMoveU(float dt);
	virtual void planeMoveD(float dt);

	void onShot(float dt);
	void onBoom();
	void removeBoom(float dt);

	int getLife();
	int getBomb();

	bool died();
	void removePlayer();
	
};

