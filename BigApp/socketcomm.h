#ifndef SOCKETCOMM_H
#define SOCKETCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <sstream>
#include <QDataStream>
#include <QByteArray>
using namespace std;
class SocketComm : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* socket;
    QDataStream in;
    QByteArray inData;
    qint64 packetByteCount;
public:
    explicit SocketComm(QObject *parent = 0);
    void connectToServer(QString host, qint16 port);
    void disconnectFromServer();
    void sendToServer(QString &data);

signals:

public slots:
    void onConnect();
    void onDisconnect();
    void getData();

};

#endif // SOCKETCOMM_H
