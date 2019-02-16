#include "GameOverSecene.h"
#include"SimpleAudioEngine.h"
#include"cocos2d.h"
#include"HelloWorldScene.h"
using namespace CocosDenshion;


USING_NS_CC;


Scene* GameOverSecene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameOverSecene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverSecene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	tmp = 0;
	scheduleUpdate();

//	Director::getInstance()->replaceScene(HelloWorld::createScene());
	Size size = Director::getInstance()->getVisibleSize();
	LabelTTF *title = LabelTTF::create("Game Over", "chiller", 100);
	addChild(title);
	title->setPosition(size.width / 2, size.height/2);

	return true;
}

void GameOverSecene::update(float dt) {

	tmp++;

	if (tmp == 100) {

		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}


}



