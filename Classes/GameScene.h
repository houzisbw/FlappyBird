#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "cocos2d.h"
#include "Player.h"
#include "Ground.h"
#include "Pipe.h"
#include "GameOver.h"
#include "Bubble.h"
#include "Enemy.h"
USING_NS_CC;
class GameScene:public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	static cocos2d::Scene * createScene();
	virtual void onEnter();//��д�ú���
	static int score;//��Ϸ����
	virtual void onEnterTransitionDidFinish();
	static int invisible_life;//��������
	Size size;
private:
	Player *mPlayer;//�������С��
	Ground *mGround;//��������
	Pipe *mPipe_up;//��Ϸˮ�� ��
	Pipe *mPipe_down;//��Ϸˮ�� ��
	Bubble* bubble;//�޵�����
	Vector<Pipe*> pipeList;//ˮ���������������ˮ��
	Vector<Bubble*> bubblelist;
	void createPipeWithTimer(float dt);
	void createBubbleWithTimer(float dt);
	void createArrowEnemyWithTimer(float dt);
	void gameStart();//��Ϸ��ʼ
	void addEvents();
	void gameStep(float dt);//��Ϸ��������
	void moveAllPipe();//�ƶ�����ˮ��
	void moveAllBubble();//�ƶ���������
	void moveAllArrow();//�ƶ����м�
	void moveAllBossBullet();//�ƶ�����boss�������ӵ�
	void moveBoss();
	void hitTestWithPipe();//��ײ���
	void hitTestWithBubble();//�Ե����ݵļ�⺯��
	void hitTestWithArrow();
	void hitTestWithBossBullet();
	void bubbleOnPlayer(Player * mP);
	void gameOver();//��Ϸ����	
	void progressTimer(float dt);
	void useBubble(Ref* r);//ʹ������ �޵�
	void bossShoot();//����boss�����ӵ�
	void addBoss();//���boss
	GameOver *go;
	LabelTTF *score_label;//��Ϸ����label
	bool isTouch;
	int delta_y;//hardģʽ��ˮ�ܸ߶Ƚ�����ֵ
	bool up;//�����Ϳ���bool����
	
	LabelTTF* life_label;
	bool isBubbleEat;
	int invisible_time;
	ProgressTimer* pt;
	MenuItemImage* life;
	Sprite* l;
	bool bubbleInUse;//����ʹ������
	Bubble* b;
	bool up_or_down;

	void moveLeft(Ref* r);
	void moveRight(Ref* r);

	//������
	Enemy* enemy;
	Enemy* boss;
	Vector<Enemy*> bossBulletList;//����boss�����ӵ�������
	Vector<Enemy*> arrow_list;//�����vector����
	int total_arrow;
	bool load;

	int total_pipe;//��¼�ܹ����ֵĹ�����Ŀ
	bool add;
	bool done;

	
};

#endif