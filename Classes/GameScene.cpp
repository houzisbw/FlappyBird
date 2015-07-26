#include "GameScene.h"
#include "Pipe.h"
#include "SimpleAudioEngine.h"
#include "GameSelect.h"
#include "math.h"

using namespace CocosDenshion;
USING_NS_CC;

bool GameScene::init()
{
	size = Director::getInstance()->getVisibleSize();
			
	
	


	auto left_arrow = MenuItemImage::create("left_arrow.png", "left_arrow.png", CC_CALLBACK_1(GameScene::moveLeft,this));
	auto right_arrow = MenuItemImage::create("right_arrow.png", "right_arrow.png", CC_CALLBACK_1(GameScene::moveRight, this));
	left_arrow->setScale(0.7);//改变menu大小，从这儿改变
	right_arrow->setScale(0.7);
	auto MenuL = Menu::create(left_arrow, NULL);
	auto MenuR = Menu::create(right_arrow, NULL);
	addChild(MenuL, 5);
	addChild(MenuR, 5);
	MenuL->setAnchorPoint(Point(0, 0));
	MenuR->setAnchorPoint(Point(0, 0));
	MenuL->setPosition(30, 25);
	MenuR->setPosition(90, 25);

	
	invisible_life=1;
	score = 0;
	isTouch = true;
	Layer::init();
	auto bg = Sprite::create("bg.jpg"); 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(bg);

	char s[20];
	sprintf(s, "%d", score);
	score_label = LabelTTF::create(s, "Courier", 50);
	score_label->setVisible(true);//和后面的false相对应
	score_label->setColor(Color3B(255, 255, 255));
	score_label->setPosition(visibleSize.width/2,visibleSize.height-150);
	addChild(score_label, 4);

	
	mPlayer = Player::create();
	mPlayer->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
	mPlayer->setAnchorPoint(Point(0, 0));
	mPlayer->setPhysicsBody(PhysicsBody::createBox(mPlayer->getContentSize()));//创建物理实体,不能做动画了，旋转动画
	//mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 200));//设置速度，先要getphysicebody 才行，速度要乘以10倍
	addChild(mPlayer);
	b = Bubble::create();
	b->setPosition(20, 15);
	mPlayer->addChild(b);//在sprite上add sprite
	b->setVisible(false);//可以这样写,控制一个sprite显示与否
	

	//创建地面
	mGround = Ground::create();
	mGround->setAnchorPoint(Point(0, 0));
	mGround->setPosition(0, -50);	
	addChild(mGround,4);//让地面覆盖水管的下部分

	//生命数目
	life = MenuItemImage::create("bubble.png", "bubble.png", CC_CALLBACK_1(GameScene::useBubble, this));
	life->setScale(0.5);//menu不能设置大小,而menuitemimage可以,还可以设置动画,从而创建动画menu
	auto sm = ScaleBy::create(0.3, 1.3);
	auto sq = Sequence::create(sm, sm->reverse(), NULL);
	life->runAction(RepeatForever::create(sq));
	auto life_menu = Menu::create(life, NULL);
	addChild(life_menu,6);	
	life_menu->setPosition(40,visibleSize.height-25);
	
	char s1[20];
	sprintf(s1, " X%d", invisible_life);
	life_label = LabelTTF::create(s1, "Courier", 30);
	addChild(life_label,4);
	life_label->setAnchorPoint(Point(0, 0));
	life_label->setPosition(50, visibleSize.height - 40);
	//时间条 progresstimer类
	pt = ProgressTimer::create(Sprite::create("timebar.jpg"));
	pt->setAnchorPoint(Point(0, 0));
	pt->setPosition(20, 100);
	addChild(pt,5);
	pt->setPercentage(100);//从上往下衰减
	pt->setType(ProgressTimerType::BAR);
	pt->setMidpoint(ccp(0.5, 0)); //从上到下
	pt->setBarChangeRate(ccp(0, 1));//沿着y轴变化


	//音效
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.wav"); //mp3要卡一下，不知道为啥
	SimpleAudioEngine::getInstance()->setEffectsVolume(1);
	
	
	return true;
}
void  GameScene::moveLeft(Ref* r)
{
	if (mPlayer->getPositionX() >= mPlayer->getContentSize().width)
	{
		mPlayer->SetPosition_X(mPlayer->getPositionX() - 20);
	}
}
void  GameScene::moveRight(Ref* r)
{
	if (mPlayer->getPositionX() <= size.width-mPlayer->getContentSize().width)
	{
		mPlayer->SetPosition_X(mPlayer->getPositionX() + 20);
	}
}
void  GameScene::useBubble(Ref* r)
{
	if (invisible_life > 0)
	{
		bubbleInUse = true;
		pt->setPercentage(100);
		invisible_life--;
		
		b->setScale(0.1);
		auto st = ScaleBy::create(0.5f, 10.0f);
		b->runAction(st);
	}
}
void GameScene::progressTimer(float dt)
{
	pt->setPercentage(pt->getPercentage() - 1);
	if (pt->getPercentage() == 0)
	{
		bubbleInUse = false;
		ActionInterval * delaytime = CCDelayTime::create(0.4f);
		auto action2 = CallFunc::create([=](){

			b->setVisible(false);

		});
		auto st = ScaleTo::create(0.1f, 0.1f);
		auto sq = Sequence::create(st, delaytime, action2,NULL);
		b->runAction(sq);//泡泡有大变小
	}
}
void  GameScene::onEnterTransitionDidFinish()
{
	
	
	gameStart();
	addEvents();
	
}

void GameScene::gameStart()
{
	
	srand(time(NULL));
	this->schedule(SEL_SCHEDULE(&GameScene::gameStep), 0.02f);
	if (GameSelect::lv_state == 1 || GameSelect::lv_state == 2)
	{
		this->schedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer), 1.5f);
	    this->schedule(SEL_SCHEDULE(&GameScene::createBubbleWithTimer), 3.0f);//气泡出现
		this->schedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer), 1.0f);//arrow出现
	}
	else if (GameSelect::lv_state == 3)
	{
		this->schedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer), 0.4f);  //管子紧密出现
		this->schedule(SEL_SCHEDULE(&GameScene::createBubbleWithTimer), 3.2f);//气泡出现
	}
	

	
	
	

}
void GameScene::gameStep(float dt)
{
	mGround->moveGround();
	moveAllPipe();
	moveAllBubble();
	moveAllArrow();
	if (total_pipe >= 5&&add==true)
	{
		moveBoss();
		moveAllBossBullet();
	    //hitTestWithBossBullet();
	}
	hitTestWithPipe();
	hitTestWithBubble();
	hitTestWithArrow();
	
	score_label->setString(StringUtils::format("%d", score/2));
	life_label->setString(StringUtils::format(" X%d", invisible_life));
	bubbleOnPlayer(mPlayer);
	if (bubbleInUse == true)//如果正在使用泡泡 ,只调用一次
	{
	
		this->schedule(SEL_SCHEDULE(&GameScene::progressTimer), 0.02f);  //嵌套调用，还没想到更好的方法
	}
	if (total_arrow >= 1000)//设置arrow出现次数
	{
		this->unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));
		total_arrow = 0;
	}
	if (total_pipe == 4&&add==false)//设置boss出现时间，通过管子数目来确定
	{
		addBoss();
		add = true;
	}
	if (total_pipe == 10 && add == true)
	{
		boss->removeFromParent();
		Enemy* getEnemy;
		for (int i = 0; i < bossBulletList.size(); i++) 
		{
			getEnemy = bossBulletList.at(i);
			getEnemy->removeFromParent();
		}

		add = false;
	}
	if (add)//如果已经添加了boss
	{
		if (boss->getPositionX() == size.width - 60&&done==false)
		{
			//boss左右移动
			ActionInterval * delaytime = CCDelayTime::create(2.0f);
			auto mb = MoveBy::create(1.0f, Vec2(-250, 0));
			auto sq1 = Sequence::create(mb, delaytime, mb->reverse(), delaytime, NULL);
			auto rp = RepeatForever::create(sq1);
			boss->runAction(rp);
			done = true; //防止重复runaction
		}
	}

}
void GameScene::bubbleOnPlayer(Player * mP)//此函数重复调用，不能播放动画，因为会一直播放开始的
{
	if (invisible_life >= 0 && bubbleInUse==true)
	{
		b->setVisible(true);				
	}
	
	


}
void GameScene::addEvents()
{
	auto listener = EventListenerTouchOneByOne::create();
	
	listener->onTouchBegan = [this](Touch*t,Event*e){
	
		if (isTouch)
		{
			if (GameSelect::lv_state != 3)
			{
				mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 300));//设置速度，先要getphysicebody 才行，速度要乘以10倍
			}
			else
			{
				mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 200));//设置速度，先要getphysicebody 才行，速度要乘以10倍
			}
			mPlayer->Rotate();//没有用，因为已经设置了物理属性
			
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}
void GameScene::addBoss()
{
	boss = Enemy::create();
	boss->initEnemy(2);
	addChild(boss, 6);
	boss->setAnchorPoint(Point(0, 0));
	boss->setPosition(size.width + 100, 320);
	
	
	//auto sp1 = Spawn::create(rp, mt);
	auto mt = MoveTo::create(0.5, Vec2(size.width - 60, 320));
	auto sq2 = Sequence::create(mt,NULL);//不能忘null
	boss->runAction(sq2);

}
void GameScene::createArrowEnemyWithTimer(float dt)
{
	
	enemy = Enemy::create();//创建enemy对象
	enemy->initEnemy(1);//arrow
	enemy->setAnchorPoint(Point(0, 0));
	addChild(enemy, 6);
	enemy->setPosition(size.width+100, CCRANDOM_0_1()*size.height);
	enemy->setRotation(-90);//设置角度旋转
	enemy->setScale(0.3);

	//加入list
	arrow_list.pushBack(enemy);
	total_arrow++;//记录已经产生的箭的数目
}
void GameScene::createBubbleWithTimer(float dt)//创建bubble
{
	//不能加srand
	Size visibleSize = Director::getInstance()->getVisibleSize();
	bubble = Bubble::create();
	bubble->setAnchorPoint(Point(0, 0));
	if (GameSelect::lv_state != 3)
	{
		bubble->setPosition(visibleSize.width + 130, CCRANDOM_0_1() > 0.5 ? visibleSize.height - 100 : visibleSize.height / 2 - 150);
	    addChild(bubble,3);
	    bubblelist.pushBack(bubble);
	
	}
	
}
void GameScene::createPipeWithTimer(float dt)//创建水管
{
	
	total_pipe++;
	////水管逐渐上升的delta y  要设置bool变量来控制
	if (delta_y <= 360&&up==true)
	{
		delta_y += 30;
		if (delta_y == 360)
		{
			up = false;
		}
	}
	if (delta_y >= 0 && up == false)
	{
		delta_y -= 30;
		if (delta_y == 0)
		{
			up = true;
		}
	}

	
	/*if (delta_y >= 140)
	{
		delta_y -= 20;
	}*/
	float r = CCRANDOM_0_1(); //rand是关键字，我勒个去
	Size visibleSize = Director::getInstance()->getVisibleSize();

	mPipe_up = Pipe::create();
	mPipe_down = Pipe::create();

	if (GameSelect::lv_state != 3)
	{

		mPipe_up->setAnchorPoint(Point(0, 0));
		mPipe_up->setPosition(visibleSize.width + 20, visibleSize.height - 100 - r * 150);

		mPipe_down->setAnchorPoint(Point(0, 0));
		mPipe_down->setPosition(visibleSize.width + 20, visibleSize.height - 150 - r * 150 - 100 - mPipe_down->getContentSize().height);
	}
	else //hard模式
	{
		
		
		mPipe_up->setAnchorPoint(Point(0, 0));
		mPipe_down->setAnchorPoint(Point(0, 0));
		mPipe_up->setPosition(visibleSize.width + 20, visibleSize.height - 350+delta_y);
		mPipe_down->setPosition(visibleSize.width + 20, visibleSize.height - 470 - mPipe_down->getContentSize().height+delta_y);
	}
	
	this->addChild(mPipe_up,3);
	this->addChild(mPipe_down, 3);
	
	pipeList.pushBack(mPipe_up);
	pipeList.pushBack(mPipe_down);
}
void GameScene::hitTestWithBubble()
{
	
	
	Bubble *b;
	for (int i = 0; i < bubblelist.size(); i++)
	{
		b = bubblelist.at(i);
		//3个面都要判断
		if (((b->getPositionX() == mPlayer->getPositionX()) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))) || ((abs(mPlayer->getPositionY() + mPlayer->getContentSize().height - b->getPositionY()) <= 24.0f) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))) || ((abs(mPlayer->getPositionY() - b->getPositionY() - b->getContentSize().height) <= 24.0f) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))))//吃到bubble ,24才行，才能吃到
		{

			
			auto ball = Sprite::create("bubble.png");//创建一张泡泡图，原来的b消失，泡泡来动画
			b->setSpeed(0);//让水平速度变0
			if (b->getIsTouch() == false) //让life只加一次
			{
				invisible_life += 1;
			   
			}
			
			auto action = MoveTo::create(2.0f, Point(25, size.height - 40));
			auto shrink = ScaleTo::create(2.0f, 0.5f);
			auto spawn = Spawn::create(action, shrink, NULL);//同时执行动作
			auto action_end = CallFunc::create([=](){

				bubblelist.erase(i);
			    ball->removeFromParent();

			});
			auto seq = Sequence::create(spawn, action_end, NULL);//不用delaytime也可以
			//注意：如果对类使用runaction，则会出错，还是对spirte用runaction好				
			ball->setAnchorPoint(Point(0, 0));
			ball->setPosition(b->getPosition());
			if (b->getIsTouch() == false)
			{
				addChild(ball);
			}

			ball->runAction(seq);
			b->setIsTouch(true);
            b->removeFromParent();
														
		}
	}
}
void GameScene::hitTestWithPipe()
{
	Pipe* p;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < pipeList.size(); i++)
	{
		p = pipeList.at(i);  
		
		if (p->getBoundingBox().intersectsRect(mPlayer->getBoundingBox())&bubbleInUse==false)//矩形碰撞检测,十分精确,检测life
		{
			
			    

				score_label->setVisible(false);
				//终止运动物体
				isTouch = false;
				unschedule(SEL_SCHEDULE(&GameScene::gameStep));
				unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
				unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));


				go = GameOver::create();//创建gameover层
				addChild(go, 7);
				go->setAnchorPoint(Point(0.5, 0.5));
				go->setPosition(0, 0);

				//Director::getInstance()->replaceScene(GameScene::createScene());
		     	break;
			
		}
	   
	}
	if ((mPlayer->getBoundingBox().intersectsRect(Rect(0, 0, 320, 47)))||(mPlayer->getPositionY()+mPlayer->getContentSize().height>=visibleSize.height))
	{
		    score_label->setVisible(false);
		    //终止运动物体		
			isTouch = false;
			unschedule(SEL_SCHEDULE(&GameScene::gameStep));
			unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
			unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));
			go = GameOver::create();
			addChild(go, 7);
			go->setAnchorPoint(Point(0.5, 0.5));
			go->setPosition(0, 0);
		
	}
}
void GameScene::hitTestWithBossBullet()
{
	Enemy* getEnemy;
	for (int i = 0; i < bossBulletList.size(); i++)
	{
		getEnemy = bossBulletList.at(i);
		if (getEnemy->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()) && bubbleInUse == false)
		{
			score_label->setVisible(false);
			//终止运动物体
			//isTouch = false;
			unschedule(SEL_SCHEDULE(&GameScene::gameStep));
			unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
			unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));



			go = GameOver::create();//创建gameover层
			addChild(go, 7);
			go->setAnchorPoint(Point(0.5, 0.5));
			go->setPosition(0, 0);

			//Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		}
	}
	if (boss->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()) && bubbleInUse == false)
	{
		score_label->setVisible(false);
		//终止运动物体
		//isTouch = false;
		unschedule(SEL_SCHEDULE(&GameScene::gameStep));
		unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
		unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));

		go = GameOver::create();//创建gameover层
		addChild(go, 7);
		go->setAnchorPoint(Point(0.5, 0.5));
		go->setPosition(0, 0);
	}
}
void GameScene::hitTestWithArrow()
{
	Enemy* getArrow;
	for (int i = 0; i < arrow_list.size(); i++)
	{
		getArrow = arrow_list.at(i);
		if (mPlayer->getBoundingBox().intersectsRect(getArrow->getBoundingBox()) && bubbleInUse == false)
		{
			score_label->setVisible(false);
			//终止运动物体
			//isTouch = false;
			unschedule(SEL_SCHEDULE(&GameScene::gameStep));
			unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
			unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));


			go = GameOver::create();//创建gameover层
			addChild(go, 7);
			go->setAnchorPoint(Point(0.5, 0.5));
			go->setPosition(0, 0);

			//Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		}
		if (mPlayer->getBoundingBox().intersectsRect(getArrow->getBoundingBox()) && bubbleInUse == true)//箭往下落
		{
			getArrow->setSpeedY(10);
			getArrow->setSpeedX(0);
			//getArrow->setPhysicsBody(PhysicsBody::createBox(getArrow->getContentSize()));
		}
	}
}
void GameScene::gameOver()
{

}
Scene* GameScene::createScene()
{
	
	auto scene = Scene::createWithPhysics();
	auto layer = GameScene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-600));//设置重力加速度，第二个参数是y轴的，要乘以10倍
	scene->addChild(layer);
	


	return scene;
}
void GameScene::onEnter()//这个函数是进入该node就调用，用来初始化把，猜测的
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);//创建边界框,3的红线宽度，为了调试

	auto edge = Node::create();

	edge->setPhysicsBody(body);
	edge->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edge);//必须在onenter里面用
}
void GameScene::moveAllBubble()
{
	Bubble* b;
	for (int i = 0; i < bubblelist.size(); i++)
	{
		b = bubblelist.at(i);
		if (b->getIsTouch() == false)
		{
			b->moveBubble();
		}
		if (b->getPositionX() <= -80)
		{
			bubblelist.eraseObject(b);
		}
	}
}
void GameScene::moveAllPipe()
{
	Pipe* p;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	
	for (int i = 0; i < pipeList.size(); i++)
	{
							
		p = pipeList.at(i);
		p->movePipe();
		if (GameSelect::lv_state == 2)//正常难度
		{
			p->movePipeY();
		}
	    if (mPlayer->getPositionX() == p->getPositionX()) //必须放在erase前面，否则p被删除了无法获得其位置
		{
			score++;			
			//SimpleAudioEngine::getInstance()->playEffect("sfx_point.wav");
			
		}	
		if (p->getPositionX() <= -80)
		{
			pipeList.eraseObject(p);
		}
	
		
	}

	

}
void GameScene::moveAllArrow()
{
	Enemy* getEnemy;
	for (int i = 0; i < arrow_list.size(); i++)
	{
		getEnemy = arrow_list.at(i);
		getEnemy->enemyMove(1);//arrow移动的函数
		if (getEnemy->getPositionX() <= -getEnemy->getContentSize().width)
		{
			arrow_list.eraseObject(getEnemy);
			getEnemy->removeFromParent();
		}
	}
}
void GameScene::moveAllBossBullet()
{	
    Enemy* getEnemy;	
	for (int i = 0; i < bossBulletList.size(); i++)
	{
		getEnemy = bossBulletList.at(i);
		getEnemy->enemyMove(3);
		if (getEnemy->getPositionY() <= -50 || getEnemy->getPositionY() >= size.height || getEnemy->getPositionX() <= 0 || getEnemy->getPositionX() >= size.width)
		{
			bossBulletList.eraseObject(getEnemy);
		}

	}

}
void GameScene::moveBoss()
{
	boss->enemyMove(2);
	if (boss->getPositionX() > 10 && boss->getPositionX()<260)
	{
		load = false;		
	}		
	if (boss->getPositionX() == 10||boss->getPositionX()==260)
	{
		//load = false;
		if (load == false)//必须设置这个bool，防止下面的list容量不断扩大
		{
			bossShoot();//发射子弹
		}
		load = true;
	}
	
}
void GameScene::bossShoot()
{
	
	//创建子弹
	Enemy* bullet_1 = Enemy::create();
	bullet_1->initEnemy(3);
	bullet_1->setSpeedBvx(0);
	bullet_1->setSpeedBvy(6);
	bossBulletList.pushBack(bullet_1);

	Enemy* bullet_2 = Enemy::create();
	bullet_2->initEnemy(4);
	bossBulletList.pushBack(bullet_2);
	bullet_2->setSpeedBvx(4.2);
	bullet_2->setSpeedBvy(4.2);

	Enemy* bullet_3 = Enemy::create();
	bullet_3->initEnemy(5);
	bossBulletList.pushBack(bullet_3);
	bullet_3->setSpeedBvx(6);
	bullet_3->setSpeedBvy(0);

	Enemy* bullet_4 = Enemy::create();
	bullet_4->initEnemy(6);
	bossBulletList.pushBack(bullet_4);
	bullet_4->setSpeedBvy(-4.2);
	bullet_4->setSpeedBvx(4.2);

	Enemy* bullet_5 = Enemy::create();
	bullet_5->initEnemy(7);
	bossBulletList.pushBack(bullet_5);
	bullet_5->setSpeedBvy(-6);
	bullet_5->setSpeedBvx(0);

	Enemy* bullet_6 = Enemy::create();
	bullet_6->initEnemy(8);
	bossBulletList.pushBack(bullet_6);
	bullet_6->setSpeedBvy(-4.2);
	bullet_6->setSpeedBvx(-4.2);

	Enemy* bullet_7 = Enemy::create();
	bullet_7->initEnemy(9);
	bossBulletList.pushBack(bullet_7);
	bullet_7->setSpeedBvy(0);
	bullet_7->setSpeedBvx(-6);

	Enemy* bullet_8 = Enemy::create();
	bullet_8->initEnemy(3);
	bossBulletList.pushBack(bullet_8);
	bullet_8->setSpeedBvy(4.2);
	bullet_8->setSpeedBvx(-4.2);

	Enemy* getEnemy;	
    for (int i = 0; i < bossBulletList.size(); i++) //初始化,
	{
		   
		    getEnemy = bossBulletList.at(i);
			getEnemy->setScale(0.5);
			if (boss->getPositionX() == 10)
			{
				getEnemy->setPosition(40, 360);
			}
			else if (boss->getPositionX() == 260)
			{
				getEnemy->setPosition(280, 360);
			}
			addChild(getEnemy,7);
			auto rb = RotateBy::create(0.2, 90);
			getEnemy->runAction(RepeatForever::create(rb));
	}


	
}
int GameScene::score = 0;
int GameScene::invisible_life = 1;
GameScene::GameScene()
:delta_y(0),
up(true),
isBubbleEat(false),
invisible_time(0),
bubbleInUse(false),
up_or_down(false),
total_arrow(0),
load(false),
total_pipe(0),
add(false),
done(false)


{
}


GameScene::~GameScene()
{
}
