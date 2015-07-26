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
	left_arrow->setScale(0.7);//�ı�menu��С��������ı�
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
	score_label->setVisible(true);//�ͺ����false���Ӧ
	score_label->setColor(Color3B(255, 255, 255));
	score_label->setPosition(visibleSize.width/2,visibleSize.height-150);
	addChild(score_label, 4);

	
	mPlayer = Player::create();
	mPlayer->setPosition(visibleSize.width / 2 - 100, visibleSize.height / 2);
	mPlayer->setAnchorPoint(Point(0, 0));
	mPlayer->setPhysicsBody(PhysicsBody::createBox(mPlayer->getContentSize()));//��������ʵ��,�����������ˣ���ת����
	//mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 200));//�����ٶȣ���Ҫgetphysicebody ���У��ٶ�Ҫ����10��
	addChild(mPlayer);
	b = Bubble::create();
	b->setPosition(20, 15);
	mPlayer->addChild(b);//��sprite��add sprite
	b->setVisible(false);//��������д,����һ��sprite��ʾ���
	

	//��������
	mGround = Ground::create();
	mGround->setAnchorPoint(Point(0, 0));
	mGround->setPosition(0, -50);	
	addChild(mGround,4);//�õ��渲��ˮ�ܵ��²���

	//������Ŀ
	life = MenuItemImage::create("bubble.png", "bubble.png", CC_CALLBACK_1(GameScene::useBubble, this));
	life->setScale(0.5);//menu�������ô�С,��menuitemimage����,���������ö���,�Ӷ���������menu
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
	//ʱ���� progresstimer��
	pt = ProgressTimer::create(Sprite::create("timebar.jpg"));
	pt->setAnchorPoint(Point(0, 0));
	pt->setPosition(20, 100);
	addChild(pt,5);
	pt->setPercentage(100);//��������˥��
	pt->setType(ProgressTimerType::BAR);
	pt->setMidpoint(ccp(0.5, 0)); //���ϵ���
	pt->setBarChangeRate(ccp(0, 1));//����y��仯


	//��Ч
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.wav"); //mp3Ҫ��һ�£���֪��Ϊɶ
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
		b->runAction(sq);//�����д��С
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
	    this->schedule(SEL_SCHEDULE(&GameScene::createBubbleWithTimer), 3.0f);//���ݳ���
		this->schedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer), 1.0f);//arrow����
	}
	else if (GameSelect::lv_state == 3)
	{
		this->schedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer), 0.4f);  //���ӽ��ܳ���
		this->schedule(SEL_SCHEDULE(&GameScene::createBubbleWithTimer), 3.2f);//���ݳ���
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
	if (bubbleInUse == true)//�������ʹ������ ,ֻ����һ��
	{
	
		this->schedule(SEL_SCHEDULE(&GameScene::progressTimer), 0.02f);  //Ƕ�׵��ã���û�뵽���õķ���
	}
	if (total_arrow >= 1000)//����arrow���ִ���
	{
		this->unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));
		total_arrow = 0;
	}
	if (total_pipe == 4&&add==false)//����boss����ʱ�䣬ͨ��������Ŀ��ȷ��
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
	if (add)//����Ѿ������boss
	{
		if (boss->getPositionX() == size.width - 60&&done==false)
		{
			//boss�����ƶ�
			ActionInterval * delaytime = CCDelayTime::create(2.0f);
			auto mb = MoveBy::create(1.0f, Vec2(-250, 0));
			auto sq1 = Sequence::create(mb, delaytime, mb->reverse(), delaytime, NULL);
			auto rp = RepeatForever::create(sq1);
			boss->runAction(rp);
			done = true; //��ֹ�ظ�runaction
		}
	}

}
void GameScene::bubbleOnPlayer(Player * mP)//�˺����ظ����ã����ܲ��Ŷ�������Ϊ��һֱ���ſ�ʼ��
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
				mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 300));//�����ٶȣ���Ҫgetphysicebody ���У��ٶ�Ҫ����10��
			}
			else
			{
				mPlayer->getPhysicsBody()->setVelocity(Vec2(0, 200));//�����ٶȣ���Ҫgetphysicebody ���У��ٶ�Ҫ����10��
			}
			mPlayer->Rotate();//û���ã���Ϊ�Ѿ���������������
			
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
	auto sq2 = Sequence::create(mt,NULL);//������null
	boss->runAction(sq2);

}
void GameScene::createArrowEnemyWithTimer(float dt)
{
	
	enemy = Enemy::create();//����enemy����
	enemy->initEnemy(1);//arrow
	enemy->setAnchorPoint(Point(0, 0));
	addChild(enemy, 6);
	enemy->setPosition(size.width+100, CCRANDOM_0_1()*size.height);
	enemy->setRotation(-90);//���ýǶ���ת
	enemy->setScale(0.3);

	//����list
	arrow_list.pushBack(enemy);
	total_arrow++;//��¼�Ѿ������ļ�����Ŀ
}
void GameScene::createBubbleWithTimer(float dt)//����bubble
{
	//���ܼ�srand
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
void GameScene::createPipeWithTimer(float dt)//����ˮ��
{
	
	total_pipe++;
	////ˮ����������delta y  Ҫ����bool����������
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
	float r = CCRANDOM_0_1(); //rand�ǹؼ��֣����ո�ȥ
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
	else //hardģʽ
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
		//3���涼Ҫ�ж�
		if (((b->getPositionX() == mPlayer->getPositionX()) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))) || ((abs(mPlayer->getPositionY() + mPlayer->getContentSize().height - b->getPositionY()) <= 24.0f) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))) || ((abs(mPlayer->getPositionY() - b->getPositionY() - b->getContentSize().height) <= 24.0f) && (b->getBoundingBox().intersectsRect(mPlayer->getBoundingBox()))))//�Ե�bubble ,24���У����ܳԵ�
		{

			
			auto ball = Sprite::create("bubble.png");//����һ������ͼ��ԭ����b��ʧ������������
			b->setSpeed(0);//��ˮƽ�ٶȱ�0
			if (b->getIsTouch() == false) //��lifeֻ��һ��
			{
				invisible_life += 1;
			   
			}
			
			auto action = MoveTo::create(2.0f, Point(25, size.height - 40));
			auto shrink = ScaleTo::create(2.0f, 0.5f);
			auto spawn = Spawn::create(action, shrink, NULL);//ͬʱִ�ж���
			auto action_end = CallFunc::create([=](){

				bubblelist.erase(i);
			    ball->removeFromParent();

			});
			auto seq = Sequence::create(spawn, action_end, NULL);//����delaytimeҲ����
			//ע�⣺�������ʹ��runaction�����������Ƕ�spirte��runaction��				
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
		
		if (p->getBoundingBox().intersectsRect(mPlayer->getBoundingBox())&bubbleInUse==false)//������ײ���,ʮ�־�ȷ,���life
		{
			
			    

				score_label->setVisible(false);
				//��ֹ�˶�����
				isTouch = false;
				unschedule(SEL_SCHEDULE(&GameScene::gameStep));
				unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
				unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));


				go = GameOver::create();//����gameover��
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
		    //��ֹ�˶�����		
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
			//��ֹ�˶�����
			//isTouch = false;
			unschedule(SEL_SCHEDULE(&GameScene::gameStep));
			unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
			unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));



			go = GameOver::create();//����gameover��
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
		//��ֹ�˶�����
		//isTouch = false;
		unschedule(SEL_SCHEDULE(&GameScene::gameStep));
		unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
		unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));

		go = GameOver::create();//����gameover��
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
			//��ֹ�˶�����
			//isTouch = false;
			unschedule(SEL_SCHEDULE(&GameScene::gameStep));
			unschedule(SEL_SCHEDULE(&GameScene::createPipeWithTimer));
			unschedule(SEL_SCHEDULE(&GameScene::createArrowEnemyWithTimer));


			go = GameOver::create();//����gameover��
			addChild(go, 7);
			go->setAnchorPoint(Point(0.5, 0.5));
			go->setPosition(0, 0);

			//Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		}
		if (mPlayer->getBoundingBox().intersectsRect(getArrow->getBoundingBox()) && bubbleInUse == true)//��������
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
	scene->getPhysicsWorld()->setGravity(Vec2(0,-600));//�����������ٶȣ��ڶ���������y��ģ�Ҫ����10��
	scene->addChild(layer);
	


	return scene;
}
void GameScene::onEnter()//��������ǽ����node�͵��ã�������ʼ���ѣ��²��
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);//�����߽��,3�ĺ��߿�ȣ�Ϊ�˵���

	auto edge = Node::create();

	edge->setPhysicsBody(body);
	edge->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edge);//������onenter������
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
		if (GameSelect::lv_state == 2)//�����Ѷ�
		{
			p->movePipeY();
		}
	    if (mPlayer->getPositionX() == p->getPositionX()) //�������eraseǰ�棬����p��ɾ�����޷������λ��
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
		getEnemy->enemyMove(1);//arrow�ƶ��ĺ���
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
		if (load == false)//�����������bool����ֹ�����list������������
		{
			bossShoot();//�����ӵ�
		}
		load = true;
	}
	
}
void GameScene::bossShoot()
{
	
	//�����ӵ�
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
    for (int i = 0; i < bossBulletList.size(); i++) //��ʼ��,
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
