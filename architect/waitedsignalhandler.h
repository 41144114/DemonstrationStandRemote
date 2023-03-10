#ifndef WAITEDSIGNALHANDLER_H
#define WAITEDSIGNALHANDLER_H

#include "threaddependobject.h"

class WaitedSignalHandler : public ThreadDependObject
{
    Q_OBJECT
public:
    WaitedSignalHandler();

public slots:
    void onHandleSignal(int code);

private:
    virtual int startProcess(QStringList args);
    virtual int quitProcess();
};

#endif // WAITEDSIGNALHANDLER_H
