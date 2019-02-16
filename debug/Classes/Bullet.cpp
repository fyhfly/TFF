#include "Bullet.h"



bool Bullet::init() {
	Sprite::init();
	s = Director::getInstance()->getVisibleSize();
	setTexture("Bullet.png");
	setPosition(Vec2(100, 100));
	setScale(0.5);
	 s = Size(960, 930);
	 speedX = random() % 20 - 10;
	speedY = random() % 20 - 10;
	if (speedX == 0) {
		if (speedY == 0) {
			speedY = 5;
		}
	}
	scheduleUpdate();
	setPhysicsBody(PhysicsBody::createBox(Size(30, 30)));
	getPhysicsBody()->setContactTestBitmask(0x05);  // 0101
	getPhysicsBody()->setCategoryBitmask(0x05);		// 0101
	getPhysicsBody()->setCollisionBitmask(0x05);	// 0101
	getPhysicsBody()->setDynamic(false);


	return true;
}

void Bullet::update(float dt)
{
	
	setPositionX(getPositionX() + speedX);
	setPositionY(getPositionY() + speedY);
	remove = true;
	if (getPositionY() < 0)
	{
		remove = false;
	}

	if (getPositionX() < 0)
	{
		remove = false;
	}

	if (getPositionY() > s.height)
	{
		remove = false;
	}

	if (getPositionX() > s.width)
	{
		remove = false;
	}
	if (!remove) {
		unscheduleUpdate();
		removeFromParent();
	}


}

void Bullet::setMod(int select,Vec2 v,float sinTmp) {

	switch (select) {
	case 1:
		speedX = (v.x - getPositionX()) / 50;
		speedY = (v.y - getPositionY()) / 50;
		break;
	case 2 :
		speedX = sin(sinTmp)*5;
		speedY = cos(sinTmp)*5;
		break;
	case 3:
		speedX = sin(sinTmp) * 5;
		speedY = cos(sinTmp) * 5;
		break;
	case 4:
		speedX = 0;
		speedY = -10;
		setPositionX((random() % (int)s.width));
		setPositionY(s.height - 10);
		break;
	default:
		break;
	}

}

void Bullet::setSpeed(float x, float y) {

	speedX = x;
	speedY = y;

}