#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "cocos2d.h"
class Player:public cocos2d::Sprite
{
public:
	Player();
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);
    void flyAction();
	void Rotate();
	void SetPosition_X(float x);//����С��ˮƽλ��
private:	
	float vy;
	float positionX;
};

#endif