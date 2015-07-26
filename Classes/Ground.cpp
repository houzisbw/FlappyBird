#include "Ground.h"
USING_NS_CC;
bool Ground::init()
{
	Layer::init();

	ground_1 = Sprite::create("back.png");
    ground_2 = Sprite::create("back.png");

	ground_1->setAnchorPoint(Point(0, 0));
	ground_2->setAnchorPoint(Point(0, 0));

	ground_1->setPosition(0,-50);
	ground_2->setPosition(0 + ground_1->getContentSize().width, -50);
	addChild(ground_1);
	addChild(ground_2);

	return true;

}
void Ground::moveGround()
{
	ground_1->setPositionX(ground_1->getPositionX() + vx);
	ground_2->setPositionX(ground_2->getPositionX() + vx);

	if (ground_1->getPositionX() <= -ground_1->getContentSize().width)
	{
		ground_1->setPositionX(ground_2->getPositionX() + ground_2->getContentSize().width);
	}
	if (ground_2->getPositionX() <= -ground_2->getContentSize().width)
	{
		ground_2->setPositionX(ground_1->getPositionX() + ground_2->getContentSize().width);
	}
}

Ground::Ground():
vx(-5)
{
}


Ground::~Ground()
{
}
