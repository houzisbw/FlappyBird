#include "Pipe.h"
USING_NS_CC;
bool Pipe::init()
{
	Sprite::init();
	initWithFile("pipe.png");
	
	return true;
}
void Pipe::movePipe()
{
	this->setPositionX(this->getPositionX() + vx);
	if (this->getPositionX()<= -80)
	{
		this->removeFromParent();
	}
}
void Pipe::movePipeY()
{
	total_y++;
	if (total_y <= 15)
	{
		this->setPositionY(this->getPositionY() + vy);
	}
	if (total_y > 15 && total_y < 30)
	{
		this->setPositionY(this->getPositionY() - vy);
	}
	if (total_y >= 30)
	{
		total_y = 0;
	}

}
Pipe::Pipe() :
vx(-5),
vy(-4),
total_y(0)
{
}


Pipe::~Pipe()
{
}
