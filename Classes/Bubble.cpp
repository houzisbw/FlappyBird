#include "Bubble.h"
#include "GameScene.h"
USING_NS_CC;
bool Bubble::init()
{
	Sprite::init();
	initWithFile("bubble.png");
	
	return true;
}
void Bubble::moveBubble()
{
	this->setPositionX(this->getPositionX() + vx);
	if (this->getPositionX() <= -80)
	{
		this->removeFromParent();
	}
}
bool Bubble::getIsTouch()
{
	return isTouch;
}
void Bubble::setIsTouch(bool it)
{
	isTouch = it;
}
void Bubble::setSpeed(float vx)
{
	this->vx = vx;
}
Bubble::Bubble():
vx(-5),
isTouch(false)
{
}


Bubble::~Bubble()
{
}
