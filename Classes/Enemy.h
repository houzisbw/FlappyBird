#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "cocos2d.h"
class Enemy:public cocos2d::Sprite
{
public:
	Enemy();
	~Enemy();
	virtual bool init();
	CREATE_FUNC(Enemy);
public:
	void initEnemy(int type);//����type��������ʼ�����˵�����
	void enemyMove(int type);
	void setSpeedX(float v);//����x���ٶ�
	void setSpeedY(float v);
	void setSpeedBvx(float v);//����boss�ӵ��ٶ�
	void setSpeedBvy(float v);
private:
	float vx;
	float vy;
	//boss bullet velocity
	float bvx;
	float bvy;
	bool up_down;
};
#endif

