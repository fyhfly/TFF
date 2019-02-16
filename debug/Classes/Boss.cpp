#include "Boss.h"
#include"BossBullet.h"
#include<cmath>


Boss * Boss::create(Layer * layer, Vec2 v, Sprite * s)
{
	auto _ins = new Boss();
	_ins->init(layer, v,s);
	_ins->autorelease();
	return _ins;
}

bool Boss::init(Layer * layer, Vec2 v, Sprite * s) {
	Sprite::init();
	_layer = layer;
	_player = s;
	setPosition(v);
	setTexture("boss.png");

	//visibleSize = Director::getInstance()->getVisibleSize();
	visibleSize = Size(960, 930);
	cardNum = 1;
	life = 20;
	r = 1.5;

	tmp = 0;

	setScale(0.25);
	setPhysicsBody(PhysicsBody::createBox(getBoundingBox().size * 3));
	//getPhysicsBody()->setContactTestBitmask(1);
	getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
	getPhysicsBody()->setContactTestBitmask(0x02);    // 0010
	getPhysicsBody()->setCollisionBitmask(0x02);    // 0010
	getPhysicsBody()->setTag(200);   

	schedule(schedule_selector(Boss::shotStart), 1.0f / 60.0f, kRepeatForever, 0);

	return true;
}

void Boss::circleShot(int num, Vec2 position,int mod) {

	
	float ra = CCRANDOM_0_1() * 6.28;
	for (int i = 0; i < num; i++) {

		auto b = BossBullet::create();
		b->setPosition(position);
		_layer->addChild(b);

		if (mod == 0) {
			b->setSpeed(5 * sin(ra + i*6.28 / num), 5 * cos(ra + i*6.28 / num));
		}
		else {
			b->setSpeed(CCRANDOM_0_1()*10 - 5, CCRANDOM_0_1() * 10 - 5);
			//b->setTexture("PlayerBullet.png");
			//b->setScale(1);
		}
		

	}


}

void Boss::shotStart(float dt) {

	tmp++;

	if (cardNum == 1) {
		card_0ne();
	}
	if (cardNum == 2) {
		card_Two();
	}
	if (cardNum == 3) {
		card_Three();
	}
	if (cardNum == 4) {
		card_Four();
	}
	if (cardNum == 5) {
		card_Five();
	}




}

bool Boss::onAttack() {

	bool isDie = false;
	life = life - 1;
	if (life == 0) {
		life = 100;
		cardNum++;
		if (cardNum > 5) {
			isDie = true;
		}
	}

	return isDie;

}

int Boss::getLife() {
	return life;
}

int Boss::getCardNum() {
	return cardNum;
}

void Boss::card_0ne() {

	if (tmp % 30 == 0) {
		circleShot(20, Vec2(600, 600),0);
	}

	if (tmp % 30 == 15) {
		circleShot(20, Vec2(200, 600),0);
	}





}

void Boss::card_Two() {

	if (tmp % 5 == 0) {
	if (tmp % 300 < 75) {
	r = r + 0.2;
	}
	else if(tmp % 300 > 75 && tmp % 300 < 150){
	r = r - 0.05;
	}
	else if (tmp % 300 > 150 && tmp % 300 < 225) {
	r = r + 0.05;
	}
	else {
	r = r - 0.2;
	}

	for (int i = 0; i < 6; i++) {
	auto bullet = BossBullet::create();
	bullet->setPosition(getPosition() + Vec2(50 * sin(6.28*i / 6+ r), 50 * cos(6.28*i / 6 + r)));
	bullet->setSpeed(5 * sin(6.28*i / 6 + 0.5 + r), 5 * cos(6.28*i / 6 + 0.5 + r));
	_layer->addChild(bullet);

	}


	}

}

void Boss::card_Three() {

	if (tmp % 4 == 0) {

		auto bullet = BossBullet::create();
		bullet->setPosition(random() % 960, 10);
		bullet->setSpeed(0, 2);
		_layer->addChild(bullet);
	}

}

void Boss::card_Four() {

	
	if (tmp % 3 == 0) {

		auto bullet = BossBullet::create();
		bullet->setPosition(random() % 960, visibleSize.height);
		bullet->setSpeed(4 - CCRANDOM_0_1() * 8, -4);
		_layer->addChild(bullet);
	}
	

}

void Boss::card_Five() {

	if (tmp % 60 == 0) {

		circleShot(40, Vec2(750, 850), 0);
		circleShot(40, Vec2(150, 850), 0);

	}

	if (tmp % 120 == 0) {
		circleShot(8, Vec2(800, 600), 0);
	}
	if (tmp % 120 == 15) {
		circleShot(6, Vec2(600, 600), 0);
	}
	if (tmp % 120 == 30) {
		circleShot(6, Vec2(400, 600), 0);
	}
	if (tmp % 120 == 45) {
		circleShot(6, Vec2(200, 600), 0);
	}

	if (tmp % 120 == 60) {
		circleShot(6, Vec2(200, 600), 0);
	}
	if (tmp % 120 == 75) {
		circleShot(6, Vec2(400, 600), 0);
	}
	if (tmp % 120 == 90) {
		circleShot(6, Vec2(600, 600), 0);
	}
	if (tmp % 120 == 105) {
		circleShot(6, Vec2(800, 600), 0);
	}


}