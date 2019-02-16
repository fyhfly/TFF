#include "Enemy.h"


Enemy * Enemy::create(Layer * layer, Vec2 v, Sprite * s)
{
	auto _ins = new Enemy();
	_ins->init(layer, v,s);
	_ins->autorelease();
	return _ins;
}

bool Enemy::init(Layer * layer, Vec2 v, Sprite * s)
{
	Sprite::init();
	_layer = layer;
	_sprite = s;
	_v = v;

	setPosition(v);


	return true;
}

