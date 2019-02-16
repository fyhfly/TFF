#include "Background.h"

bool Background::init() {

	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{

		return false;
	}


		auto backGround = Sprite::create("background.png");
		backGround->setAnchorPoint(Point(0, 0));

		addChild(backGround);
	return true;



}