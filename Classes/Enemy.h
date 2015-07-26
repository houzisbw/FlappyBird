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
	void initEnemy(int type);//根据type来决定初始化敌人的类型
	void enemyMove(int type);
	void setSpeedX(float v);//设置x轴速度
	void setSpeedY(float v);
	void setSpeedBvx(float v);//设置boss子弹速度
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

