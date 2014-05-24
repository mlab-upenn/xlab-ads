#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "start";

    ui->setupUi(this);
    bTimer = false;
    bPlayer = false;
    //ShowTag = new QPushButton("ShowTag", this);
    pauseresume = new QPushButton("Pause", this);
    ToggleFullScreen = new QPushButton("Full Screen", this);

    prev = new QPushButton("Prev",this);
    next = new QPushButton("Next", this);

    ui->bottom_Hlayout->addWidget(prev);
    ui->bottom_Hlayout->addWidget(next);
    //ui->bottom_Hlayout->addWidget(ShowTag);
    ui->bottom_Hlayout->addWidget(pauseresume);
    ui->bottom_Hlayout->addWidget(ToggleFullScreen);

    player = new QMediaPlayer();
    videoItem = new QGraphicsVideoItem();
    canvas = new QGraphicsView();
    scene = new MyGraphicsScene();
    cover = new MyGraphicsView();
    cover_scene = new MyGraphicsScene();

    xmlparser = new XMLDataParser();
    xmlparser->loadXML(":/xml/RachaelRay.xml");
    xmlparser->parseXML();
    cover->setParser(xmlparser);
    cover->sendToServerViaView("video:RachaelRay");
    timer = new QTimer(this);
    timer->setInterval(5000);
    timer->start();
    bTimer = true;
    connect(timer, SIGNAL(timeout()), cover, SLOT(ShowNextFrame()));

    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("http://158.130.12.47:3000/uploads/fullsize/RachaelRay.mp4"));
    playlist->addMedia(QUrl("http://158.130.12.47:3000/uploads/fullsize/macys.mp4"));
    //videoItem->showMaximized();
    player->setPlaylist(playlist);

//    qDebug() <<"b4 play";
//    qDebug()<<"resolution"<<playlist->currentMedia().canonicalResource().resolution().height()<<" "<<playlist->currentMedia().canonicalResource().resolution().width();
    player->setVideoOutput(videoItem);
    videoItem->setSize(QSize(this->width(),this->height()));
    scene->addItem(videoItem);
    connect(playlist,SIGNAL(currentMediaChanged(QMediaContent)),cover,SLOT(UpdateResolution(QMediaContent)));
 //   cover_scene->addRect(this->x(),this->y(),this->width(),this->height(),QPen(QColor(255,0,0),6));
 //  canvas->setGeometry(videoWidget->geometry());
    canvas->setScene(scene);
    canvas->setFrameStyle( QFrame::NoFrame );
    canvas->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    canvas->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    cover->setScene(cover_scene);
    cover->setFrameStyle( QFrame::NoFrame );
    cover->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    cover->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    cover->setSceneRect(scene->sceneRect());

    player->play();
    if(player->isSeekable()){
        qDebug()<<"seekable";
    }else{
        qDebug() << "not seekable";
    }
    bPlayer = true;
//    qDebug() <<"after play";
//    qDebug()<<"resolution"<<playlist->currentMedia().canonicalResource().resolution().height()<<" "<<playlist->currentMedia().canonicalResource().resolution().width();

    cover->setBackgroundRole( QPalette::Window );
    cover->setStyleSheet("background:transparent");
    cover->setAttribute(Qt::WA_TranslucentBackground);
  //  item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg").scaled(this->width(),this->height()));
  //  cover_scene->addPixmap(QPixmap("/home/tao/TestGUI/background.png").scaled(this->width(),this->height()));
  //  canvas->showFullScreen();
   // connect(ShowTag,SIGNAL(clicked()),cover, SLOT(ToggleDrawRect()));
    connect(next,SIGNAL(clicked()),playlist,SLOT(next()));
    connect(prev,SIGNAL(clicked()),playlist,SLOT(previous()));
    connect(playlist,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(LoadNewXML(QMediaContent)));
    connect(pauseresume, SIGNAL(clicked()),this, SLOT(TogglePlay()));
    connect(ToggleFullScreen, SIGNAL(clicked()),this,SLOT(ToggleFull()));

  //  connect(GroupTwo,SIGNAL(clicked()),cover, SLOT(DrawEllipse()));
  //  connect(GroupThree,SIGNAL(clicked()),canvas, SLOT(DrawAll()));
    connect(cover, SIGNAL(mouseClickEvent()), cover, SLOT(clickHandler()));
    ui->top_Hlayout->addWidget(canvas,0,0);
    ui->top_Hlayout->addWidget(cover,0,0);

//    ui->horizontalLayout->addWidget(canvas);




}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    canvas->setSceneRect(this->rect());
    videoItem->setSize(QSize(this->width(),this->height()));
    cover->setSceneRect(this->rect());

}

void MainWindow::TogglePlay()
{
    if(bPlayer)
    {
        player->pause();
        pauseresume->setText("Resume");
    }
    else
    {
        player->play();
        pauseresume->setText("Pause");
    }
    bPlayer = !bPlayer;
    if(bTimer)
    {timer->stop();}
    else
    {timer->start();}
    bTimer = !bTimer;

}
void MainWindow::ToggleFull()
{
    if(this->isFullScreen())
    {
        this->showNormal();
        ToggleFullScreen->setText("Full Screen");
    }
    else
    {
        this->showFullScreen();
        ToggleFullScreen->setText("Exit Full Screen");
    }
}

void MainWindow::LoadNewXML(QMediaContent video)
{
    xmlparser->loadXML(":/xml/" + video.canonicalUrl().fileName().section(".",0,0) + QString(".xml"));
    xmlparser->parseXML();
    cover->setParser(xmlparser);
    cover->sendToServerViaView("video:" + video.canonicalUrl().fileName().section(".",0,0));

}
/*
void MainWindow::drawRect()
{
    canvas->setRect(true);
    canvas->setEllipse(false);
    vector<QRect> channelRect = canvas->getRects();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addRect(channelRect[0],QPen(QColor(255,0,0),6));
    scene->addRect(channelRect[1],QPen(QColor(255,0,0),6));

}

void MainWindow::drawEllipse()
{
    canvas->setEllipse(true);
    canvas->setRect(false);
    vector<QRect> channelRect = canvas->getEllipses();
    scene->clear();
    item = new QGraphicsPixmapItem(QPixmap("/home/tao/Desktop/panda_AP.jpg"));
    scene->addItem(item);
    scene->addEllipse(channelRect[0],QPen(QColor(255,200,0),6));
    scene->addEllipse(channelRect[1],QPen(QColor(255,200,0),6));
}*/
MainWindow::~MainWindow()
{
    delete ui;
}
