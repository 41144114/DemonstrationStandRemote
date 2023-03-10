#ifndef BLUETOOTHADAPTER_H
#define BLUETOOTHADAPTER_H

#include "abstractadapter.h"
#include <QBluetoothSocket>

class BluetoothAdapter : public AbstractAdapter
{
    Q_OBJECT
public:
    explicit BluetoothAdapter(QObject* parent = nullptr);
private slots:
    void onSocketErrorOccurred(QBluetoothSocket::SocketError error);

signals:
    void socketConnected(int code);

private:
    virtual void init();
    virtual bool open(const QVariant portParams);
    virtual void read();
};

#endif // BLUETOOTHADAPTER_H
