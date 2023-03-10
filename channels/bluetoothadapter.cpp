#include "bluetoothadapter.h"
#include "architect/waitedsignalhandler.h"
#include "helpers/nonlockwaiter.h"
#include <QByteArray>
#include <QElapsedTimer>
#include <QtBluetooth/QBluetoothSocket>

const int kConnectWaitingTime = 60000;

BluetoothAdapter::BluetoothAdapter(QObject* parent) : AbstractAdapter(parent) {}

void BluetoothAdapter::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    qDebug() << "errorOccured" << error;
}

void BluetoothAdapter::init() { _pPort = new QBluetoothSocket(); }

bool BluetoothAdapter::open(const QVariant portParams)
{
    QBluetoothServiceInfo service = qvariant_cast<QBluetoothServiceInfo>(portParams);
    connect(dynamic_cast<QBluetoothSocket*>(_pPort),
            QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error), this,
            &BluetoothAdapter::onSocketErrorOccurred);
    connect(dynamic_cast<QBluetoothSocket*>(_pPort), &QBluetoothSocket::connected, [&]() {
        qDebug() << "connected!!" << dynamic_cast<QBluetoothSocket*>(_pPort)->peerName();
        emit socketConnected(kStandardSuccessCode);
    });

    bool isReady;

    WaitedSignalHandler waitingObject;
    connect(this, &BluetoothAdapter::socketConnected, &waitingObject, &WaitedSignalHandler::onHandleSignal);
    NonLockWaiter::waitReadyObject(
        &waitingObject, [&]() { dynamic_cast<QBluetoothSocket*>(_pPort)->connectToService(service); },
        kConnectWaitingTime, isReady, 10);

    return dynamic_cast<QBluetoothSocket*>(_pPort)->state() == QBluetoothSocket::ConnectedState;
}

void BluetoothAdapter::read()
{
    if (_pPort != nullptr)
        emit sendIncomingData(_pPort->readAll());
}
