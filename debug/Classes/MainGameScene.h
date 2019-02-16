#pragma once
#include"cocos2d.h"
#include"Enemy.h"
#include"yaojing.h"
#include"Player.h"
#include"Boss.h"
#include<vector>

USING_NS_CC;

class MainGameScene : public cocos2d::LayerColor
{
private:
	int tmp;
	Player * player;
	Boss  * boss;
	Size visibleSize;
	int enemyMode = 1;


	int playerLife;
	int bomb;

	bool dieP;
	Vec2 diePosition;

	Sprite *energy1 = Sprite::create("bomb.png");
	Sprite *energy2 = Sprite::create("bomb.png");

public:
	
	static cocos2d::Scene* createScene();

	
	virtual bool init();
	Vector<yaojing*> yaojings;
	
	CREATE_FUNC(MainGameScene);

	void mainAction(float dt);
	void enemyInit();

	void setLife();
	void setBomb();

	void update(float dt);
};

