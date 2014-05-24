#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <vector>
#include <QMap>
#include <QDebug>
using namespace std;
class Frame : public QObject
{
    Q_OBJECT

private:
    QMap<QString,QString> item;
    vector<QMap<QString,QString> > items;
public:
    explicit Frame(QObject *parent = 0);
    void InsertItem(QMap<QString,QString> );
    void DisplayContent();
    vector<QMap<QString,QString> > GetAll();
signals:

public slots:

};

#endif // FRAME_H
