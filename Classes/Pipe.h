#ifndef _PIPE_H_
#define _PIPE_H_
#include "cocos2d.h"
class Pipe:public cocos2d::Sprite
{
public:
	Pipe();
	~Pipe();
	virtual bool init();
	CREATE_FUNC(Pipe);
	void movePipe();
	void movePipeY();//水管上下移动
private:
	float vx;
	float vy;//Y轴的速度
	int total_y;//y轴移动的距离
};
#endif

