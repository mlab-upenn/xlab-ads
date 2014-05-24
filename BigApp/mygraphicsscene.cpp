#include "mygraphicsscene.h"

MyGraphicsScene::MyGraphicsScene(QWidget *parent) :
    QGraphicsScene(parent)
{
}
void MyGraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *e)
{
    qDebug() << "pressed at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();

    m_lastPos = e->pos();
    bMouseClick = true;
}

void MyGraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent *e)
{
    qDebug() << "release at  X: "<<e->pos().x() <<"    Y:" << e->pos().y();
    if(bMouseClick && (m_lastPos == e->pos()))
    {
        qDebug() << "click in scene";

        emit mouseClickEvent();
        bMouseClick = false;
    }
}
