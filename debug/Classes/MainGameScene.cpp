#include "MainGameScene.h"
#include"Background.h"
#include"Player.h"
#include"Bullet.h"
#include"HelloWorldScene.h"
#include"SimpleAudioEngine.h"
#include"GameOverSecene.h"
#include<vector>

using namespace CocosDenshion;


Scene* MainGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	


	// 'layer' is an autorelease object
	auto layer = MainGameScene::create();
	auto background = Background::create();

	// add layer as a child to scene
	scene->addChild(background);
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainGameScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0,255)))
	{
		return false;
	}
	//visibleSize = Director::getInstance()->getVisibleSize();
	visibleSize = Size(960, 960);
	setContentSize(Size(960, 960));
 
	
	dieP = false;
	tmp = 0;



	player = Player::create(this);
	
	addChild(player);

	enemyInit();


	//lifeLable
	LabelTTF *lifeLabel = LabelTTF::create("Damaged Condition", "DotumChe", 30);
	addChild(lifeLabel);
	lifeLabel->setPosition(visibleSize.width + 180, visibleSize.height - 195);
	playerLife = player->getLife();
	setLife();

	//bombLable
	LabelTTF *bomb = LabelTTF::create("Energy", "DotumChe", 30);
	addChild(bomb);
	bomb->setPosition(visibleSize.width + 180, visibleSize.height - 80);


	//bombTexture
	addChild(energy1);
	addChild(energy2);
	energy1->setPosition(visibleSize.width + 132, visibleSize.height - 130);
	energy2->setPosition(visibleSize.width + 239, visibleSize.height - 130);
	energy1->setScaleX(0.32);
	energy1->setScaleY(0.3);
	energy2->setScaleX(0.32);
	energy2->setScaleY(0.3);



	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [this, listener](PhysicsContact & contact) {

		if (contact.getShapeA()->getBody()->getTag() == 1 || contact.getShapeB()->getBody()->getTag() == 1) {
			//log("<<<<");
			
			if (player->died()) {
				player->removePlayer();
				Director::getInstance()->replaceScene(GameOverSecene::createScene());
			}
			playerLife = player->getLife();
			setLife();
		}

		if (contact.getShapeA()->getBody()->getTag() == 200 || contact.getShapeB()->getBody()->getTag() == 200) {

			if (boss->onAttack()) {
				boss->removeFromParent();
				player->removePlayer();
				Director::getInstance()->replaceScene(GameOverSecene::createScene());
			}

			
		}

		for (auto it = yaojings.begin(); it != yaojings.end(); it++) {


			if (contact.getShapeA()->getBody()->getTag() == (*it)->getPhysicsBody()->getTag() || contact.getShapeB()->getBody()->getTag() == (*it)->getPhysicsBody()->getTag()) {
				if ((*it)->onAttack()) {
					diePosition = (*it)->getPosition();
					if ((*it)->getHaveDiedBomb()) {
						dieP = true;
					}
					(*it)->removeFromParent();
				}
			}

		}

		if (contact.getShapeA()->getBody()->getTag() == 0 || contact.getShapeB()->getBody()->getTag() == 0) {
			if (contact.getShapeA()->getBody()->getTag() == 0) {
				contact.getShapeA()->getBody()->getNode()->removeFromParent();
			}
			if (contact.getShapeB()->getBody()->getTag() == 0) {
				contact.getShapeB()->getBody()->getNode()->removeFromParent();
			}
		}

		if (contact.getShapeA()->getBody()->getTag() == 101 || contact.getShapeB()->getBody()->getTag() == 101) {
			if (contact.getShapeA()->getBody()->getTag() == 101) {
				contact.getShapeA()->getBody()->getNode()->removeFromParent();
			}
			if (contact.getShapeB()->getBody()->getTag() == 101) {
				contact.getShapeB()->getBody()->getNode()->removeFromParent();
			}
		}


		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);




	schedule(schedule_selector(MainGameScene::mainAction), 1.0f / 60.0f, kRepeatForever, 0);
	scheduleUpdate();

	//SimpleAudioEngine::sharedEngine()->playBackgroundMusic("001-Battle01.mid");



	return true;
}


void MainGameScene::mainAction(float dt) {

	

	tmp++;
	if (tmp == 100) {

		yaojings.at(0)->init(this, Vec2(300, visibleSize.height), player,1, 1);
		yaojings.at(0)->getPhysicsBody()->setTag(2);
		yaojings.at(0)->setHaveDiedBomb(false);
		this->addChild(yaojings.at(0));

		yaojings.at(1)->init(this, Vec2(600, visibleSize.height), player,0, 1);
		yaojings.at(1)->getPhysicsBody()->setTag(3);
		this->addChild(yaojings.at(1));
	
	}




	if (tmp < 300 && tmp>100) {

		yaojings.at(0)->setPositionY(yaojings.at(0)->getPositionY() - 1.5);
		yaojings.at(1)->setPositionY(yaojings.at(1)->getPositionY() - 1.5);

	}
	//
	if (tmp == 400) {

		yaojings.at(2)->init(this, Vec2(200, visibleSize.height), player, 2, 1);
		yaojings.at(2)->getPhysicsBody()->setTag(4);
		this->addChild(yaojings.at(2));

		yaojings.at(3)->init(this, Vec2(700, visibleSize.height), player, 2, 1);
		yaojings.at(3)->getPhysicsBody()->setTag(5);
		this->addChild(yaojings.at(3));

		//SimpleAudioEngine::sharedEngine()->getInstance()->stopBackgroundMusic(false);

	}

	if (tmp < 600 && tmp > 400) {

		yaojings.at(2)->setPositionY(yaojings.at(2)->getPositionY() - 1.5);
		yaojings.at(3)->setPositionY(yaojings.at(3)->getPositionY() - 1.5);
		

	}

	if (tmp == 1000) {

		yaojings.at(4)->init(this, Vec2(400, visibleSize.height), player, 3, 1);
		yaojings.at(4)->getPhysicsBody()->setTag(6);
		this->addChild(yaojings.at(4));

		yaojings.at(5)->init(this, Vec2(500, visibleSize.height), player, 3, 1);
		yaojings.at(5)->getPhysicsBody()->setTag(7);
		this->addChild(yaojings.at(5));

	}

	if (tmp < 1200 && tmp > 1000) {

		yaojings.at(4)->setPositionX(yaojings.at(4)->getPositionX() - 1);
		yaojings.at(4)->setPositionY(yaojings.at(4)->getPositionY() - 1.5);
		yaojings.at(5)->setPositionX(yaojings.at(5)->getPositionX() + 1);
		yaojings.at(5)->setPositionY(yaojings.at(5)->getPositionY() - 1.5);

	}



	if (tmp == 1400) {

		yaojings.at(5)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(5)->getPhysicsBody()->setTag(7);
		//yaojings.at(5)->setLife(1);
		yaojings.at(5)->setNext(20);
		yaojings.at(5)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(5));

	}

	if (tmp ==1450) {

		yaojings.at(6)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(6)->getPhysicsBody()->setTag(8);
		//yaojings.at(6)->setLife(1);
		yaojings.at(6)->setNext(20);
		yaojings.at(6)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(6));

	}
	
	if (tmp == 1500) {

		yaojings.at(7)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(7)->getPhysicsBody()->setTag(9);
		//yaojings.at(7)->setLife(1);
		yaojings.at(7)->setNext(20);
		yaojings.at(7)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(7));

	}
	if (tmp == 1550) {

		yaojings.at(8)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(8)->getPhysicsBody()->setTag(10);
		//yaojings.at(8)->setLife(1);
		yaojings.at(8)->setNext(20);
		yaojings.at(8)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(8));

	}
	if (tmp == 1600) {

		yaojings.at(9)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(9)->getPhysicsBody()->setTag(11);
		//yaojings.at(9)->setLife(1);
		yaojings.at(9)->setNext(20);
		yaojings.at(9)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(9));

	}
	if (tmp == 1650) {

		yaojings.at(10)->init(this, Vec2(0, visibleSize.height*0.8), player, 1, 2);
		yaojings.at(10)->getPhysicsBody()->setTag(12);
		//yaojings.at(10)->setLife(1);
		yaojings.at(10)->setNext(20);
		yaojings.at(10)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(10));

	}


	if (tmp < 2600 && tmp > 1400) {


		for (int i = 5; i < 11; i++) {
			yaojings.at(i)->setPositionX(yaojings.at(i)->getPositionX() + 2);
			if (yaojings.at(i)->getPositionX() > visibleSize.width) {
				yaojings.at(i)->removeFromParent();
			}
		}

	}

	if (tmp == 1800) {

		yaojings.at(11)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(11)->getPhysicsBody()->setTag(13);
		//yaojings.at(11)->setLife(1);
		yaojings.at(11)->setNext(20);
		yaojings.at(11)->setHaveDiedBomb(true);

		this->addChild(yaojings.at(11));

	}

	if (tmp == 1850) {

		yaojings.at(12)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(12)->getPhysicsBody()->setTag(14);
		//yaojings.at(12)->setLife(1);
		yaojings.at(12)->setNext(20);
		yaojings.at(12)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(12));

	}

	if (tmp == 1900) {

		yaojings.at(13)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(13)->getPhysicsBody()->setTag(15);
		//yaojings.at(13)->setLife(1);
		yaojings.at(13)->setNext(20);
		yaojings.at(13)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(13));

	}
	if (tmp == 1950) {

		yaojings.at(14)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(14)->getPhysicsBody()->setTag(16);
		//yaojings.at(14)->setLife(1);
		yaojings.at(14)->setNext(20);
		yaojings.at(14)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(14));

	}
	if (tmp == 2000) {

		yaojings.at(15)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(15)->getPhysicsBody()->setTag(17);
		//yaojings.at(15)->setLife(1);
		yaojings.at(15)->setNext(20);
		yaojings.at(15)->setHaveDiedBomb(true);
		this->addChild(yaojings.at(15));

	}
	if (tmp == 2050) {

		yaojings.at(16)->init(this, Vec2(visibleSize.width, visibleSize.height*0.7), player, 1, 2);
		yaojings.at(16)->getPhysicsBody()->setTag(18);
		//yaojings.at(16)->setLife(1);
		yaojings.at(16)->setNext(20);
		yaojings.at(16)->setHaveDiedBomb(true);

		this->addChild(yaojings.at(16));

	}


	if (tmp < 3000 && tmp > 1800) {


		for (int i = 11; i < 17; i++) {
			yaojings.at(i)->setPositionX(yaojings.at(i)->getPositionX() - 2);
			if (yaojings.at(i)->getPositionX() < 0) {
				yaojings.at(i)->removeFromParent();
			}
		}

	}

	if (tmp < 5000 && tmp > 3000) {

		auto b = Bullet::create();
		b->setMod(4, Vec2(0, 0), 0);
		addChild(b);
	}

	if (tmp == 5100) {
		boss = Boss::create(this, Vec2(480, 800), player);
		addChild(boss);
	}



}

void MainGameScene::enemyInit() {
	for (int i = 0; i < 5; i++) {
		auto y = yaojing::create(this, Vec2(0, 0), player, 0, 1);
		y->getPhysicsBody()->setTag(i+2);
		yaojings.pushBack(y);
	}
	for (int i = 5; i < 17; i++) {
		auto y = yaojing::create(this, Vec2(0, 0), player, 0, 2);
		y->getPhysicsBody()->setTag(i + 2);
		yaojings.pushBack(y);
	}
}

void MainGameScene::update(float dt) {

	if (dieP) {
		auto b = yaojing::create(this, diePosition, player, 0, enemyMode);
		b->circleShot(100);

		dieP = false;
	}



	bomb = player->getBomb();
	setBomb();

}

void MainGameScene::setLife()
{
	CCTexture2D *HP, *HP4, *HP3, *HP2, *HP1;
	auto hp = Sprite::create("life5.png");
	auto hp4 = Sprite::create("life4.png");
	auto hp3 = Sprite::create("life3.png");
	auto hp2 = Sprite::create("life2.png");
	auto hp1 = Sprite::create("life1.png");

	HP = hp->getTexture();
	HP4 = hp4->getTexture();
	HP3 = hp3->getTexture();
	HP2 = hp2->getTexture();
	HP1 = hp1->getTexture();


	if (playerLife == 5)
	{
		hp->stopAllActions();

		hp->setTexture(HP);
		addChild(hp);
		hp->setPosition(visibleSize.width + 186, visibleSize.height - 316);
		hp->setScaleX(0.31);
		hp->setScaleY(0.31);
	}

	if (playerLife == 4)
	{
		hp->stopAllActions();

		hp->setTexture(HP4);
		addChild(hp);
		hp->setPosition(visibleSize.width + 186, visibleSize.height - 316);
		hp->setScaleX(0.31);
		hp->setScaleY(0.31);
	}

	if (playerLife == 3)
	{
		hp->stopAllActions();

		hp->setTexture(HP3);
		addChild(hp);
		hp->setPosition(visibleSize.width + 186, visibleSize.height - 316);
		hp->setScaleX(0.31);
		hp->setScaleY(0.31);
	}

	if (playerLife == 2)
	{
		hp->stopAllActions();

		hp->setTexture(HP2);
		addChild(hp);
		hp->setPosition(visibleSize.width + 186, visibleSize.height - 316);
		hp->setScaleX(0.31);
		hp->setScaleY(0.31);
	}

	if (playerLife == 1)
	{
		hp->stopAllActions();

		hp->setTexture(HP1);
		addChild(hp);
		hp->setPosition(visibleSize.width + 186, visibleSize.height - 316);
		hp->setScaleX(0.31);
		hp->setScaleY(0.31);
	}

}

void MainGameScene::setBomb()
{

	if (bomb == 2)
	{
		energy2->setOpacity(255);
		energy1->setOpacity(255);
	}

	if (bomb == 1)
	{
		energy2->setOpacity(0);
		energy1->setOpacity(255);

	}

	if (bomb == 0)
	{
		energy2->setOpacity(0);
		energy1->setOpacity(0);
	}
}