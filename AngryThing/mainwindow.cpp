#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
    once=0;
    y_once=0;
    b_once=0;
    w_once=0;
    whichbird=0;
    scoretext="score:0";
    displayscore=0;
    redgenerated=0;
    defeat1=0;
    defeat2=0;

    setMouseTracking(true);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world b2vec2=xy方向加速度
    world = new b2World(b2Vec2(0.0f, -9.8f));

    // Setting Size 實際上畫面是幾公尺?
    GameItem::setGlobalSize(QSizeF(32,18),size());

    // Create ground (You can edit here) (x,y,w,h,)
    land = new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene);

    // create enemy and obstacles
    piggy=new enemy(18.2f,12.0f,0.9999f,&timer,QPixmap(":/image/敵人01PNG.png").scaled(height()/6.0,height()/6.0),world,scene);
    piggy->setLinearVelocity(b2Vec2(0.2,0));
    itemList.push_back(piggy);

    piggy2=new enemy(24.75f,3.5f,0.9999f,&timer,QPixmap(":/image/敵人01PNG.png").scaled(height()/6.0,height()/6.0),world,scene);
    piggy2->setLinearVelocity(b2Vec2(0.2,0));
    itemList.push_back(piggy2);

    ob1=new obstacle(18.5f,5.7f,0.3f,2.2f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/4.0),world,scene);
    itemList.push_back(ob1);

    ob2=new obstacle(23.0f,6.0f,0.3f,5.0f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/2.0),world,scene);
    itemList.push_back(ob2);

    ob3=new obstacle(27.5f,6.0f,0.3f,5.0f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/2.0),world,scene);
    itemList.push_back(ob3);
/*
    ob4=new obstacle(25.25f,15.0f,0.3f,3.0f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/3.0),world,scene);
    //ob4->setLinearVelocity(b2Vec2(0,0));
    ob4->g_body->SetTransform(b2Vec2(25.25f,15.0f),90);
    itemList.push_back(ob4);

    ob5=new obstacle(20.25f,5.5f,5.1f,0.3f,&timer,QPixmap(":/image/thinwood.png").scaled(height()/2.0,height()/24.0),world,scene);
    ob5->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(ob5);

    ob6=new obstacle(20.25f,8.6f,5.1f,0.3f,&timer,QPixmap(":/image/thinwood.png").scaled(height()/2.0,height()/24.0),world,scene);
    ob6->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(ob6);
*/

    // invisible boundary
    invwall *rightside = new invwall(33.0f,10.0f,1.0f,30.0f,world);
    invwall *leftside = new invwall(0.0f,10.0f,1.0f,30.0f,world);
    launcher = new invwall(1.5f,8.2f,3.0f,0.1f,world);

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick())); //更新畫面的timer
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT())); //關閉遊戲
    timer.start(100/6); //數值越大則更新越慢

    // timer for detecting velocity of every bird then decide whether to generate the next bird
    timer_detect = new QTimer(this);
    connect(timer_detect, SIGNAL(timeout()), this, SLOT(detect()));
    timer_detect->start(2000);

    // constantly detecting whether piggy is defeated and calculate the score
    timer_collide = new QTimer(this);
    connect(timer_collide, SIGNAL(timeout()), this, SLOT(ifcolliding()));


    showScore();
}




// 偵測畫面上滑鼠動作
bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!

    if(event->type() == QEvent::MouseButtonPress)
    {
        // TODO : num=5 滑鼠點擊位置~鳥的位置 vector大小
        //std::cout << "Press !" << std::endl ;
        // delete launcher;

    }
    if(event->type() == QEvent::MouseMove)
    {
        // TODO : 改變鳥鳥發射角度
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        // TODO : num=2 發射鳥鳥
        //std::cout << "Release !" << std::endl ;
        // Setting the Velocity 發射速度(Vx,Vy)
        if (redgenerated==1 && once==1){
            rbird->setLinearVelocity(b2Vec2(10,12)); // 10 12
            rbird->launched=1;
            timer_collide->start();
            ++once;
        }
        switch(whichbird){
        case 2:
            if(bbird->launched==0){
                bbird->setLinearVelocity(b2Vec2(7,12));
                bbird->launched=1;
            }
            break;
        case 3:
            if(ybird->launched==0){
                ybird->setLinearVelocity(b2Vec2(7,7));
                ybird->launched=1;
            }
            break;
        case 4:
            if(wbird->launched==0){
                wbird->setLinearVelocity(b2Vec2(15,10));
                wbird->launched=1;
            }
            break;
        }

    }
    return false;
}

// for detecting clicking buttons and function the birds
void MainWindow::mousePressEvent(QMouseEvent *event){

    // for clicking buttons
    if(event->pos().x()>80 && event->pos().y()>470 && event->pos().x()<140 && event->pos().y()<530) emit quitGame();
    if(event->pos().x()>10 && event->pos().x()<70 && event->pos().y()>470 && event->pos().y()<530){
        restartfunc();
        return;
    }

    // control blue bird generating more when pressing mouse !!!!!!!!NOT QUITE OKAY YET!!!!!!!!!
    if(event->type() == QEvent::MouseButtonPress && b_once==0 && whichbird==2 && bbird->launched==1){
        a=new bluebird(bbird->g_body->GetPosition().x,bbird->g_body->GetPosition().y,0.2f,&timer,QPixmap(":/image/blue.png").scaled(height()/12.0,height()/12.0),world,scene);
        a->setLinearVelocity(b2Vec2(bbird->g_body->GetLinearVelocity().x,bbird->g_body->GetLinearVelocity().y+bbird->g_body->GetLinearVelocity().x));
        b=new bluebird(bbird->g_body->GetPosition().x,bbird->g_body->GetPosition().y,0.2f,&timer,QPixmap(":/image/blue.png").scaled(height()/12.0,height()/12.0),world,scene);
        b->setLinearVelocity(b2Vec2(bbird->g_body->GetLinearVelocity().x,bbird->g_body->GetLinearVelocity().y-bbird->g_body->GetLinearVelocity().x));
        itemList.push_back(a);
        itemList.push_back(b);
        bbird->alreadyclicked=1;
        ++b_once; // only executing once
    }

    // control yellow bird accelerating when pressing mouse
    if(event->type() == QEvent::MouseButtonPress && y_once==0 && whichbird==3 && ybird->launched==1){
        ybird->setLinearVelocity(b2Vec2(ybird->g_body->GetLinearVelocity().x*3,ybird->g_body->GetLinearVelocity().y*3));
        ++y_once; // only executing once
    }

    // control white bird laying an egg
    if(event->type() == QEvent::MouseButtonPress && w_once==0 && whichbird==4 && wbird->launched==1){
        eggy=new egg(wbird->g_body->GetPosition().x,wbird->g_body->GetPosition().y-1,0.2f,&timer,QPixmap(":/image/egg.png").scaled(height()/12.0,height()/12.0),world,scene);
        eggy->setLinearVelocity(b2Vec2(1,-10));
        itemList.push_back(eggy);
        wbird->alreadyclicked=1;
        ++w_once; // only executing once
    }

}

// detect the velocity of the current bird every second, if bird stops, then generate the next bird
void MainWindow::detect(){
    //std::cout << "detecting !" << std::endl ;
    switch (whichbird){
        case 0:
            if(once==0){
                generate_nextbird();
            }
            break;
        case 1:
            if(rbird->g_body->GetLinearVelocity().x==0 && rbird->launched==1){
                itemList.removeAll(rbird);
                delete rbird;
                generate_nextbird();
            }
            break;
        case 2:
            if(bbird->g_body->GetLinearVelocity().x==0 && bbird->launched==1){
                itemList.removeAll(bbird);
                delete bbird;
                if (bbird->alreadyclicked==1){
                    itemList.removeAll(a);
                    itemList.removeAll(b);
                    delete a;
                    delete b;
                }
                generate_nextbird();
            }
            break;
        case 3:
            if(ybird->g_body->GetLinearVelocity().x==0 && ybird->launched==1){
                itemList.removeAll(ybird);
                delete ybird;
                generate_nextbird();
            }
            break;
        case 4:
            if(wbird->g_body->GetLinearVelocity().x==0 && wbird->launched==1){
                itemList.removeAll(wbird);
                delete wbird;
                if(wbird->alreadyclicked==1){
                    itemList.removeAll(eggy);
                    delete eggy;
                }
                generate_nextbird();
            }
            break;
    }

}

// decide what bird to generate next
void MainWindow::generate_nextbird(){
    switch (whichbird){
        case 0:
            rbird = new Bird(1.5f,8.5f,0.2f,&timer,QPixmap(":/bird.png").scaled(height()/12.0,height()/12.0),world,scene);
            itemList.push_back(rbird);
            ++once;
            redgenerated=1;
            break;
        case 1:
            bbird=new bluebird(1.5f,8.5f,0.2f,&timer,QPixmap(":/image/blue.png").scaled(height()/12.0,height()/12.0),world,scene);
            //bbird->setLinearVelocity(b2Vec2(7,12));
            itemList.push_back(bbird);
            break;
        case 2:
            ybird=new yellowbird(1.5f,8.5f,0.2f,&timer,QPixmap(":/image/yellow.png").scaled(height()/11.0,height()/11.0),world,scene);
            //ybird->setLinearVelocity(b2Vec2(7,7));
            itemList.push_back(ybird);
            break;
        case 3:
            wbird=new whitebird(1.5f,8.5f,0.45f,&timer,QPixmap(":/image/white.png").scaled(height()/9.0,height()/9.0),world,scene);
            //wbird->setLinearVelocity(b2Vec2(15,10));
            itemList.push_back(wbird);
            break;
    }
    ++whichbird;
}

// piggy is defeated condition and adding score
void MainWindow::ifcolliding(){
    if(defeat1==0){
        if(piggy->g_body->GetLinearVelocity().x!=0 && abs(static_cast<double>(piggy->g_body->GetPosition().x)-18.2)>0){
            displayscore+=2;
            showScore();
        }
        if(abs(piggy->g_body->GetLinearVelocity().x)>2 || piggy->g_body->GetPosition().y<6){
            displayscore+=35000;
            showScore();
            itemList.removeAll(piggy);
            delete piggy;
            ++defeat1;
        }
    }
    if(defeat2==0){
        if(piggy2->g_body->GetLinearVelocity().x!=0 && abs(static_cast<double>(piggy2->g_body->GetPosition().x)-24.75)>0){
            displayscore+=2;
            showScore();
        }
        if(abs(piggy2->g_body->GetLinearVelocity().x)>0.3){
            displayscore+=35000;
            showScore();
            itemList.removeAll(piggy2);
            delete piggy2;
            ++defeat2;
        }
    }
    if(displayscore>70000 || (defeat1+defeat2)==2){
        timer_collide->stop();
        whichbird=10;
        emit quitGame();
    }
    if (whichbird==4 && displayscore<70000)
    {
        if(wbird->g_body->GetLinearVelocity().x==0){
            timer_collide->stop();
            //emit quitGame();
        }
    }
}

// restart button clicked = delete item in the itemlist/ clear itemlist / new enemy and obstacles and the first bird
void MainWindow::restartfunc(){
    timer_detect->stop();
    timer_collide->stop();
    int allitem = itemList.size();
    for (int i=0;i<allitem;++i){
        delete itemList.at(i);
    }
    itemList.clear();

    once=0;
    y_once=0;
    b_once=0;
    w_once=0;
    whichbird=0;
    scoretext="score:0";
    displayscore=0;
    redgenerated=0;
    defeat1=0;
    defeat2=0;

    piggy=new enemy(18.2f,10.0f,0.9999f,&timer,QPixmap(":/image/敵人01PNG.png").scaled(height()/6.0,height()/6.0),world,scene);
    piggy->setLinearVelocity(b2Vec2(0.2,0));
    itemList.push_back(piggy);

    piggy2=new enemy(24.75f,3.5f,0.9999f,&timer,QPixmap(":/image/敵人01PNG.png").scaled(height()/6.0,height()/6.0),world,scene);
    piggy2->setLinearVelocity(b2Vec2(0.2,0));
    itemList.push_back(piggy2);

    ob1=new obstacle(18.5f,5.5f,0.3f,2.1f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/4.0),world,scene);
    ob1->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(ob1);

    ob2=new obstacle(23.0f,5.5f,0.3f,2.1f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/4.0),world,scene);
    ob2->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(ob2);

    ob3=new obstacle(27.5f,5.5f,0.3f,5.1f,&timer,QPixmap(":/image/thinwood1.png").scaled(height()/24.0,height()/2.0),world,scene);
    ob3->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(ob3);

    showScore();
    timer_detect->start(2000);

}

// display score
void MainWindow::showScore(){
    scoretext="Score:";
    QString transcore;
    transcore.setNum(displayscore);
    scoretext += transcore;
    ui->label_score->setText(scoretext);
}

// 發出quitGame訊號
void MainWindow::closeEvent(QCloseEvent *){
    emit quitGame();
}

// 調整world的時間step&更新畫面
void MainWindow::tick(){
    world->Step(1.0/60.0,6,2);
    scene->update();
}

// 關閉遊戲就cout
void MainWindow::QUITSLOT(){
    std::cout << "Quit Game Signal receive !" << std::endl ;
}



/*
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->type() == QEvent::MouseMove)
    {
            // TODO : 改變鳥鳥發射角度
            std::cout << "Move !" << std::endl ;
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event->type() == QEvent::MouseButtonRelease)
    {
        // TODO : num=2 發射鳥鳥

        std::cout << "Release !" << std::endl ;
    }
}
*/
