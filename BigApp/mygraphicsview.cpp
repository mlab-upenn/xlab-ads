#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

    videoWidth = 854;
    videoHeight = 480;
    bGroupEllipse = false;
    bGroupRect = false;
    bDrawRect = false;
    QWidget::setMouseTracking(true);
    client = new SocketComm(); 
    client->connectToServer("127.0.0.1", 2000);

}
void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "pressed at  X: "<<e->pos().x()/xRatio <<"    Y:" << e->pos().y()/yRatio;
    qDebug()<< xRatio <<" "<<yRatio <<videoHeight<< " "<<videoWidth;
    QRect curRect;
    QGraphicsScene *scene;
    m_lastPos = e->pos();
    bMousePress = true;
    scene = this->scene();
 /*   if(bGroupRect)
    {
        for(uint i = 0; i < rects.size(); i++)
        {
            curRect = rects[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addRect(rects[i].first,QPen(QColor(0,255,0),6));
            }
        }
    }
    if(bGroupEllipse)
    {
        for(uint i = 0; i < ellipses.size(); i++)
        {
            curRect = ellipses[i].first;
            if(curRect.contains(m_lastPos))
            {
                scene->addEllipse(ellipses[i].first,QPen(QColor(0,255,0),6));
            }
        }
    }
*/
    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        if(curRect.contains(m_lastPos) && bDrawRect)
        {
             scene->addRect(curRect,QPen(QColor(0,255,0),6));
        }

    }

}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
    QRect curRect;
    QGraphicsScene *scene;
    if(bMousePress)
    {
        bMousePress = false;
        for(uint i = 0; i < items.size(); i++)
        {
            curRect = toRect(items[i]);
            scene = this->scene();
            if(curRect.contains((e->pos())) && bDrawRect)
            {
                scene->addRect(curRect,QPen(QColor(255,255,0),6));
            }

        }
    }
    if(m_lastPos == e->pos())
        emit mouseClickEvent();
}

void MyGraphicsView::clickHandler()
{

    QRect curRect;
    QString curStr;

    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        curStr =items[i]["name"];

        if(curRect.contains(m_lastPos) && bDrawRect)
        {
            client->sendToServer(curStr);
            qDebug() <<"click in ROI";
        }
    }

}


void MyGraphicsView::ToggleDrawRect()
{
    bDrawRect = !bDrawRect;

    DrawRect();

}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
  //  qDebug() << "mouse pos"<<e->pos().x()<<"    "<<e->pos().y();
    QRect curRect;
    QGraphicsScene *scene;
    if(!bMousePress)
        DrawRect();
    for(uint i = 0; i < items.size(); i++)
    {
        curRect = toRect(items[i]);
        scene = this->scene();
        if(curRect.contains(e->pos()) && bDrawRect)
        {
            scene->addRect(curRect,QPen(QColor(255,255,0),6));
        }
    }
}
void MyGraphicsView::setRect(bool val)
{
    bGroupRect = val;
}
void MyGraphicsView::setEllipse(bool val)
{
    bGroupEllipse = val;
}

void MyGraphicsView::UpdateResolution(QMediaContent video)
{
    videoWidth = video.canonicalResource().resolution().width();
    videoHeight = video.canonicalResource().resolution().height();
}

void MyGraphicsView::resizeEvent(QResizeEvent *e)
{
    xRatio = (float)this->size().width() / videoWidth;
    yRatio = (float)this->size().height() / videoHeight;
    DrawRect();
}
void MyGraphicsView::ShowNextFrame()
{

    if(itrFramedata == framedata.end())
        return ;

    curFrame = *itrFramedata;
    items = curFrame->GetAll();
    if(items.size() > 0){
        QMap<QString,QString> item = items[0];
        QString info = QString("msg:")+item["name"];
        client->sendToServer(info);
            DrawRect();
    }
//    QMap<QString,QString> item = items[0];
//    qDebug() << items.size()<<""<<item["name"];
//    QString curStr =  QString::number(itrFramedata.key());
//    client->sendToServer( curStr);
    DrawRect();
    itrFramedata++;

}
void MyGraphicsView::DrawRect()
{
    QGraphicsScene *scene;

    this->setRect(true);
    this->setEllipse(false);
    scene = this->scene();

    scene->clear();
    if(bDrawRect)
    {
        QGraphicsScene *scene;

        this->setRect(true);
        this->setEllipse(false);
        scene = this->scene();

        scene->clear();

        for(uint i = 0; i < items.size(); i++)
        {
            scene->addRect(toRect(items[i]),QPen(QColor(255,0,0),4));
        }
    }


}

QRect MyGraphicsView::toRect(QMap<QString, QString> item)
{
    QString x,y,width,height;
    x = item["x"];
    y = item["y"];
    width = item["width"];
    height = item["height"];
    return QRect(x.toInt()* xRatio, y.toInt()* yRatio,width.toInt()* xRatio,height.toInt() * yRatio);
}

void MyGraphicsView::setParser(XMLDataParser *a)
{
    parser = a;
    framedata = parser->GetData();

    itrFramedata = framedata.begin();

    curFrame = *itrFramedata;
    items = curFrame->GetAll();

}

XMLDataParser* MyGraphicsView::getParser()
{
    return parser;
}

vector< pair<QRect, QString> > MyGraphicsView::getRects()
{
    return rects;
}

vector< pair<QRect, QString> > MyGraphicsView::getEllipses()
{
    return ellipses;
}

void MyGraphicsView::sendToServerViaView(QString msg)
{
    client->sendToServer(msg);
}
void MyGraphicsView::DrawEllipse()
{
    QGraphicsScene *scene;

    this->setRect(false);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
 //   scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0; i < ellipses.size(); i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}

void MyGraphicsView::DrawAll()
{
    QGraphicsScene *scene;
    this->setRect(true);
    this->setEllipse(true);
    scene = this->scene();

    scene->clear();
 //   scene->addPixmap(background->scaled(this->width(),this->height()));
    for(uint i = 0 ; i < rects.size();i++)
    {
        scene->addRect(rects[i].first,QPen(QColor(255,0,0),6));
    }
    for(uint i = 0 ; i < ellipses.size();i++)
    {
        scene->addEllipse(ellipses[i].first,QPen(QColor(255,0,0),6));
    }
}
