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
	void movePipeY();//ˮ�������ƶ�
private:
	float vx;
	float vy;//Y����ٶ�
	int total_y;//y���ƶ��ľ���
};
#endif

