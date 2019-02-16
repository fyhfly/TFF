#include "HelpScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();


	// 'layer' is an autorelease object
	auto layer = HelpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelpScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	Sprite *help = Sprite::create("help.png");
	addChild(help);
	help->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	LabelTTF *back = LabelTTF::create("Back", "DotumChe", 42);
	addChild(back);
	back->setPosition(200, visibleSize.height - 45);

	EventListenerTouchOneByOne *listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [back](Touch* t, Event *e) {

		if (back->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(HelloWorld::createScene());
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, back);
	
	return true;
}