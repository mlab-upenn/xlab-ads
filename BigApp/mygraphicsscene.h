#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QWidget *parent = 0);
signals:
    void mouseClickEvent();
protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *e);
    void mousePressEvent( QGraphicsSceneMouseEvent *e);
public slots:

private:
    bool bMouseClick;
    QPointF m_lastPos;
};

#endif // MYGRAPHICSSCENE_H
