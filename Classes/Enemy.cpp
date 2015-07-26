#include "Enemy.h"
USING_NS_CC;
bool Enemy::init()
{
	Sprite::init();
	return true;
}
void Enemy::initEnemy(int type)    //type==1 射箭
{
	char name[20];
	sprintf(name, "enemy_%d.png", type);
	initWithFile(name);
}
void Enemy::enemyMove(int type)
{
	Size size = Director::getInstance()->getVisibleSize();
	
	if (type == 1) //arrow
	{
		this->setPositionX(this->getPositionX() - vx);//左移动箭
		this->setPositionY(this->getPositionY() - vy);//向下移动箭
	}
	else if (type == 2)//动漫人物
	{
		
		//y轴移动
		if (this->getPositionY() >= 300&&up_down==false)
		{
			this->setPositionY(this->getPositionY() - 1);
			if (this->getPositionY() == 300)
			{
				up_down = true;
				

			}
		}
		if (this->getPositionY() <= 320 && up_down == true)
		{
			this->setPositionY(this->getPositionY() + 1);
			if (this->getPositionY() == 320)
			{
				up_down = false;
				
			}
		}		
	}
	else if (type==3)//boss 子弹
	{
		this->setPositionX(this->getPositionX() + bvx);//左移动箭
		this->setPositionY(this->getPositionY() + bvy);//向下移动箭
		if (this->getPositionY() <= -50 || this->getPositionY() >= size.height || this->getPositionX() <= 0 || this->getPositionX() >= size.width)
		{
			//bossBulletList.eraseObject(getEnemy);
			this->removeFromParent();//必要的
		}
	}
}
void Enemy::setSpeedX(float v)
{
	vx = v;
}
void Enemy::setSpeedY(float v)
{
	vy = v;
}
void Enemy::setSpeedBvx(float v)
{
	bvx = v;
}
void Enemy::setSpeedBvy(float v)
{
	bvy = v;
}
Enemy::Enemy() :
vx(10),
vy(0),
bvx(0),
bvy(0),
up_down(false)
{
}


Enemy::~Enemy()
{
}
