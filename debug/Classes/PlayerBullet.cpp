#include "PlayerBullet.h"


bool PlayerBullet::init() {
	Sprite::init();
	s = Director::getInstance()->getVisibleSize();
	setTexture("PlayerBullet.png");

	setPosition(Vec2(100, 100));
	s = Size(960, 930);
	speedX = 0;
	speedY = 10;
	scheduleUpdate();
	setPhysicsBody(PhysicsBody::createBox(Size(20, 20)));
	getPhysicsBody()->setPositionOffset(Vec2(-29, 4));
	getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
	getPhysicsBody()->setContactTestBitmask(0x02);    // 0010
	getPhysicsBody()->setCollisionBitmask(0x02);    // 0010
	getPhysicsBody()->setTag(101);
	//getPhysicsBody()->setContactTestBitmask(1);
	getPhysicsBody()->setDynamic(false);


	return true;
}

void PlayerBullet::update(float dt)
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

//void Bullet::onStart(Vec2 v) {
//setPosition(v);
//scheduleUpdate();
//}
