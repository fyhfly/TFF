#include "yaojing.h"
#include"Bullet.h"
#include<cmath>


yaojing * yaojing::create(Layer * layer, Vec2 v, Sprite * s,int mod, int enemyMode)
{
	auto _ins = new yaojing();
	_ins->init(layer, v, s,mod,enemyMode);
	_ins->autorelease();
	return _ins;
}

bool yaojing::init(Layer * layer, Vec2 v, Sprite * s, int mod, int enemyMode)
{
	Enemy::init(layer, v, s);
	_v = v;
	_layer = layer;
	_player = s;
	ModNum = 0;
	sinTmp = 0;
	//life = 10;
	wait = 0;
	next = 1;
	isDie = false;
	haveDiedBomb = false;
	setMod(mod);

	setEnemyMode(enemyMode);




	//setTexture("enemy.png");
	//setScale(0.2);
	//setPhysicsBody(PhysicsBody::createBox(getBoundingBox().size * 3));
	////getPhysicsBody()->setContactTestBitmask(1);
	//getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
	//getPhysicsBody()->setContactTestBitmask(0x02);    // 0010
	//getPhysicsBody()->setCollisionBitmask(0x02);    // 0010
	//getPhysicsBody()->setTag(0);    // 0010
	//getPhysicsBody()->setDynamic(false);

	schedule(schedule_selector(yaojing::shotStart), 1.0f/60.0f, kRepeatForever, 0);

	return true;
}


void yaojing::shotStart(float dt) {

	wait++;
	if (wait == next) {
		
		wait = 0;
		auto b = Bullet::create();
		b->setPosition(getPosition());
		b->setMod(ModNum, _player->getPosition(), sinTmp);
		_layer->addChild(b);

		if (ModNum == 2) {
			auto b2 = Bullet::create();
			b2->setPosition(getPosition());
			b2->setMod(ModNum, _player->getPosition(), sinTmp + 3.14159);
			_layer->addChild(b2);
		}

		if (ModNum == 3) {
			auto b2 = Bullet::create();
			b2->setPosition(getPosition());
			b2->setMod(ModNum, _player->getPosition(), -sinTmp);
			_layer->addChild(b2);
		}

		sinTmp = sinTmp + 0.2;
		if (sinTmp > 100) {
			sinTmp = 0;
		}
	}
}

void yaojing::setMod(int select) {
	ModNum = select;
	if (select == 1) {
		next = 6;
	}
	else
	{
		next = 2;
	}
}

bool yaojing::onAttack() {

	isDie = false;

	life = life - 1;

	if (!life) {
		isDie = true;
	}

	return isDie;

}

//void yaojing::setLife(int l) {
//
//	life = l;
//
//}

void yaojing::setNext(int n) {

	next = n;

}

void yaojing::circleShot(int num) {


		int r = random() % 5;

		for (int i = 0; i < num; i++) {

			auto b = Bullet::create();
			b->setSpeed(5 * sin(r + i*6.28 / num), 5 * cos(r + i*6.28 / num));
			_layer->addChild(b);
			b->setPosition(getPosition());

		}


}

void yaojing::setHaveDiedBomb(bool h) {

	haveDiedBomb = h;
	
}

bool yaojing::getHaveDiedBomb() {
	return haveDiedBomb;
}


void yaojing::setEnemyMode(int enemyMode)
{
	if (enemyMode == 1)
	{
		life = 10;
		setTexture("enemy.png");
		setScale(0.2);
		setPhysicsBody(PhysicsBody::createBox(getBoundingBox().size * 3));
		//getPhysicsBody()->setContactTestBitmask(1);
		getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
		getPhysicsBody()->setContactTestBitmask(0x02);    // 0010
		getPhysicsBody()->setCollisionBitmask(0x02);    // 0010
		getPhysicsBody()->setTag(0);    // 0010
	}

	if (enemyMode == 2)
	{
		life = 1;
		setTexture("zibao.png");
		setScale(0.3);
		setPhysicsBody(PhysicsBody::createBox(Size(120,120)));
		//getPhysicsBody()->setContactTestBitmask(1);
		getPhysicsBody()->setCategoryBitmask(0x02);    // 0010
		getPhysicsBody()->setContactTestBitmask(0x02);    // 0010
		getPhysicsBody()->setCollisionBitmask(0x02);    // 0010
		getPhysicsBody()->setTag(0);    // 0010
	}
}
