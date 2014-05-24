#include "frame.h"

Frame::Frame(QObject *parent) :
    QObject(parent)
{


}

void Frame::InsertItem(QMap <QString, QString> item)
{
    items.push_back(item);
}

vector<QMap<QString, QString> > Frame::GetAll()
{
    return items;
}

void Frame::DisplayContent()
{
    for(uint i = 0; i < items.size(); i++)
    {
        for(QMap<QString,QString>::const_iterator itr = items.at(i).begin(); itr != items.at(i).end(); itr++)
        {
            qDebug() << itr.key()<<"    "<<itr.value();
        }
    }
}
