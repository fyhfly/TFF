#include "BossBullet.h"

bool BossBullet::init() {
	Sprite::init();
	s = Director::getInstance()->getVisibleSize();
	setTexture("Bullet.png");
	setPosition(Vec2(100, 100));
	setScale(0.5);
	s = Size(960, 930);
	speedX = 0;
	speedY = 0;
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
	getPhysicsBody()->setTag(0);
	getPhysicsBody()->setDynamic(false);


	return true;
}

void BossBullet::update(float dt)
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


void BossBullet::setSpeed(float x, float y) {

	speedX = x;
	speedY = y;

}