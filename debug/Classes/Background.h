#pragma once
#include"cocos2d.h"
USING_NS_CC;
class Background : public LayerColor
{
public:

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Background);

};

