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
	virtual void onEnter();//重写该函数
	static int score;//游戏分数
	virtual void onEnterTransitionDidFinish();
	static int invisible_life;//气泡数量
	Size size;
private:
	Player *mPlayer;//创建玩家小鸟
	Ground *mGround;//创建背景
	Pipe *mPipe_up;//游戏水管 上
	Pipe *mPipe_down;//游戏水管 下
	Bubble* bubble;//无敌气泡
	Vector<Pipe*> pipeList;//水管容器，存放所有水管
	Vector<Bubble*> bubblelist;
	void createPipeWithTimer(float dt);
	void createBubbleWithTimer(float dt);
	void createArrowEnemyWithTimer(float dt);
	void gameStart();//游戏开始
	void addEvents();
	void gameStep(float dt);//游戏步进函数
	void moveAllPipe();//移动所有水管
	void moveAllBubble();//移动所有泡泡
	void moveAllArrow();//移动所有箭
	void moveAllBossBullet();//移动所有boss发出的子弹
	void moveBoss();
	void hitTestWithPipe();//碰撞检测
	void hitTestWithBubble();//吃到泡泡的检测函数
	void hitTestWithArrow();
	void hitTestWithBossBullet();
	void bubbleOnPlayer(Player * mP);
	void gameOver();//游戏结束	
	void progressTimer(float dt);
	void useBubble(Ref* r);//使用气泡 无敌
	void bossShoot();//动漫boss发射子弹
	void addBoss();//添加boss
	GameOver *go;
	LabelTTF *score_label;//游戏分数label
	bool isTouch;
	int delta_y;//hard模式下水管高度渐变数值
	bool up;//阶梯型控制bool参数
	
	LabelTTF* life_label;
	bool isBubbleEat;
	int invisible_time;
	ProgressTimer* pt;
	MenuItemImage* life;
	Sprite* l;
	bool bubbleInUse;//正在使用泡泡
	Bubble* b;
	bool up_or_down;

	void moveLeft(Ref* r);
	void moveRight(Ref* r);

	//敌人类
	Enemy* enemy;
	Enemy* boss;
	Vector<Enemy*> bossBulletList;//动漫boss发射子弹的容器
	Vector<Enemy*> arrow_list;//射箭的vector容器
	int total_arrow;
	bool load;

	int total_pipe;//记录总共出现的管子数目
	bool add;
	bool done;

	
};

#endif