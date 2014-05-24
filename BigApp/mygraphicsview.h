#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDebug>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <utility>
#include "socketcomm.h"
#include "mygraphicsscene.h"
#include <QMediaPlaylist>
#include "xmldataparser.h"
#include "frame.h"
using namespace std;
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

signals:
    void mouseClickEvent();

public slots:
    void clickHandler();
    void ShowNextFrame();
    void DrawRect();
    void DrawEllipse();
    void DrawAll();
    void UpdateResolution(QMediaContent);
    void ToggleDrawRect();

public:
    explicit MyGraphicsView(QWidget *parent = 0);
    vector< pair<QRect, QString> > getRects();
    vector< pair<QRect, QString> > getEllipses();
    void setRect(bool);
    void setEllipse(bool);
    void setParser(XMLDataParser* );
    XMLDataParser* getParser();
    void sendToServerViaView(QString msg);

protected:
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *event);

private:
    QRect toRect(QMap<QString,QString>);
    bool bMousePress;
    bool bGroupRect;
    bool bGroupEllipse;
    bool bDrawRect;
//    QPixmap *background;
    Frame* curFrame;
    QPoint m_lastPos;
    vector< pair<QRect, QString> > rects;
    vector< pair<QRect, QString> > ellipses;
    vector<QMap < QString,QString> > items;
    QTcpSocket * socket;
    SocketComm* client;
    float xRatio,yRatio;
    int videoWidth, videoHeight;
    QMap<int, Frame*> framedata;
    QMap<int, Frame*>::iterator itrFramedata;
    XMLDataParser* parser;


};

#endif // MYGRAPHICSVIEW_H
