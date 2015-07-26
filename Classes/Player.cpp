#include "Player.h"
#include "GameScene.h"
USING_NS_CC;
bool Player::init()
{
	bool bl = Sprite::init();

	initWithFile("bird_blue_0.png");
	flyAction();
	
	
	return bl;
}
void Player::flyAction()
{
	Texture2D *bird1 = TextureCache::getInstance()->addImage("bird_blue_0.png");  //����plist��������
	auto frame1 = SpriteFrame::createWithTexture(bird1, Rect(0, 0, 45, 32));
	Texture2D *bird2 = TextureCache::getInstance()->addImage("bird_blue_1.png");
	auto frame2 = SpriteFrame::createWithTexture(bird2, Rect(0, 0, 45, 32));
	Texture2D *bird3 = TextureCache::getInstance()->addImage("bird_blue_2.png");
	auto frame3 = SpriteFrame::createWithTexture(bird3, Rect(0, 0, 45, 32));

	Vector<SpriteFrame*> birdFly;
	birdFly.pushBack(frame1);
	birdFly.pushBack(frame2);
	birdFly.pushBack(frame3);
	Animation * mAnimation = Animation::createWithSpriteFrames(birdFly, 0.3f);//����֡����
	Animate *mAnimate = Animate::create(mAnimation);//��������
	RepeatForever* loop = RepeatForever::create(mAnimate);

	runAction(loop);

}
void Player::SetPosition_X(float x)
{
	this->setPositionX(x);
}
void Player::Rotate()
{
	auto ro = RotateBy::create(1.0f, -45);
	auto s = Sequence::create(ro, ro->reverse(),NULL);
	this->runAction(RepeatForever::create(s));

}
Player::Player()
{
}


Player::~Player()
{
}
