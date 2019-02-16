#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HelpScene.h"
#include"MainGameScene.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}

	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("001-Battle01.mid");

	Size size = Director::getInstance()->getVisibleSize();

	//LabelTTF *title = LabelTTF::create("Experimental Project: The First Fantasy", "chiller", 48);
	//addChild(title);

	auto title = Sprite::create("title.png");
	addChild(title);
	title->setPosition(size.width / 2, size.height*0.75);


	LabelTTF *startGame = LabelTTF::create("Start Game", "chiller", 36);
	addChild(startGame);
	startGame->setPosition(size.width / 2, size.height / 2);

	LabelTTF *help = LabelTTF::create("Help", "chiller", 36);
	addChild(help);
	help->setPosition(size.width / 2, size.height*0.4);

	LabelTTF *exitGame = LabelTTF::create("Exit Game", "chiller", 36);
	addChild(exitGame);
	exitGame->setPosition(size.width / 2, size.height*0.3);

	EventListenerTouchOneByOne *listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [startGame/*,exitGame*/](Touch* t, Event *e) {

		if (startGame->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(MainGameScene::createScene());
		}

		//if (exitGame->getBoundingBox().containsPoint(t->getLocation()))
		//{
		//	exit(0);
		//}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, startGame);

	EventListenerTouchOneByOne *listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [exitGame](Touch* t, Event *e) {

		if (exitGame->getBoundingBox().containsPoint(t->getLocation()))
		{
			exit(0);
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, exitGame);

	EventListenerTouchOneByOne *listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [help](Touch* t, Event *e) {

		if (help->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(HelpScene::createScene());
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, help);

	return true;
}
