#include "Player.h"
#include"PlayerBullet.h"


Player * Player::create(Layer * layer)
{
	auto _ins = new Player();
	_ins->init(layer);
	_ins->autorelease();
	return _ins;
}

bool Player::init(Layer * layer) {
	Sprite::init();
	ableBomb = true;
	boomRadius = 250;
	tempPasue = 0;
	_layer = layer;
	speed = 7;
	life = 5;
	//visibleSize = Director::getInstance()->getVisibleSize();
	visibleSize = Size(960, 930);
	reallyBody = Size(90, 90);
	Vec2 x = Vec2(0, 0);
	setTexture("Reimu.PNG");
	setScaleX(0.18);
	setScaleY(0.18);
	setPosition(initPosition);

	setPhysicsBody(PhysicsBody::createBox(reallyBody));
	getPhysicsBody()->setPositionOffset(x);
	getPhysicsBody()->setContactTestBitmask(1);
	getPhysicsBody()->setCategoryBitmask(0x01); // 0001
	getPhysicsBody()->setCollisionBitmask(0x01); // 0001
	getPhysicsBody()->setTag(1);
	getPhysicsBody()->setRotationEnable(false);

	listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			schedule(schedule_selector(Player::planeMoveR), 1.0f / 60.0f, kRepeatForever, 0);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			schedule(schedule_selector(Player::planeMoveL), 1.0f / 60.0f, kRepeatForever, 0);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			schedule(schedule_selector(Player::planeMoveU), 1.0f / 60.0f, kRepeatForever, 0);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			schedule(schedule_selector(Player::planeMoveD), 1.0f / 60.0f, kRepeatForever, 0);
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			onShot(10);
			schedule(schedule_selector(Player::onShot), 1.0f / 10.0f, kRepeatForever, 0);
			break;
		case EventKeyboard::KeyCode::KEY_X:
			if(ableBomb)
				onBoom();
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			speed = 3;
			break;

		default:
			break;
		}

	};

	listenerKeyboard->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			unschedule(schedule_selector(Player::planeMoveR));
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			unschedule(schedule_selector(Player::planeMoveL));
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			unschedule(schedule_selector(Player::planeMoveU));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			unschedule(schedule_selector(Player::planeMoveD));
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			speed = 7;
			break;
		case EventKeyboard::KeyCode::KEY_Z:
			unschedule(schedule_selector(Player::onShot));
		default:
			break;
		}
	};
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerKeyboard,1);







	return true;
}


void Player::planeMoveR(float dt) {



	//setPositionX(getPositionX() + speed);
	if (getPositionX() < visibleSize.width - 20) {
		setPositionX(getPositionX() + speed);
	}
}

void Player::planeMoveL(float dt) {



	//setPositionX(getPositionX() - speed);
	if (getPositionX() > 0) {
		setPositionX(getPositionX() - speed);
	}
}

void Player::planeMoveU(float dt) {



	//setPositionY(getPositionY() + speed);
	if (getPositionY() < visibleSize.height) {
		setPositionY(getPositionY() + speed);
	}
}

void Player::planeMoveD(float dt) {



	//setPositionY(getPositionY() - speed);
	if (getPositionY() > 30) {
		setPositionY(getPositionY() - speed);
	}
}

bool Player::died() {
	isGameOver = false;

	life = life - 1;

	if (life == 0) {
		isGameOver = true;
	}
	else {
		isGameOver = false;
	}

	return isGameOver;

}

int Player::getLife() {
	return life;
}

int Player::getBomb()
{
	return boom;
}

void Player::onShot(float dt) {

	auto b = PlayerBullet::create();
	b->setPosition(Vec2(getPosition().x + 29, getPosition().y - 4));
	_layer->addChild(b);


}

void Player::onBoom() {



	if (boom > 0)
	{
		ableBomb = false;
		boomSprite = Sprite::create("dazhao.png");
		boomSprite->setScale(1.5);
		boomSprite->setOpacity(100);
		boomSprite->setPhysicsBody(PhysicsBody::createCircle(boomRadius));

		boomSprite->getPhysicsBody()->setCategoryBitmask(0x04);    // 0100
		boomSprite->getPhysicsBody()->setContactTestBitmask(0x04);    // 0100
		boomSprite->getPhysicsBody()->setCollisionBitmask(0x04);    // 0100
		boomSprite->getPhysicsBody()->setTag(100);
		//boomSprite->getPhysicsBody()->
		boomSprite->setPosition(getPosition());
		_layer->addChild(boomSprite);

		schedule(schedule_selector(Player::removeBoom), 1.0f / 60.0f, kRepeatForever, 0);

		boom--;
	}

}

void Player::removeBoom(float dt) {

	tempPasue++;
	if (tempPasue == 120) {
		tempPasue = 0;
		boomSprite->removeFromParent();
		ableBomb = true;
		unschedule(schedule_selector(Player::removeBoom));
	}
}


void Player::removePlayer() {

	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerKeyboard);
	unschedule(schedule_selector(Player::onShot));

	//getPhysicsBody()->getNode()->removeFromParent();
	//removeFromParent();

}