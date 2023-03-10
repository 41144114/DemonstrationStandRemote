#include "waitedsignalhandler.h"

WaitedSignalHandler::WaitedSignalHandler()
{

}

void WaitedSignalHandler::onHandleSignal(int code)
{
    emit ready(code);
}

int WaitedSignalHandler::startProcess(QStringList args)
{
    Q_UNUSED(args);
    return kStandardSuccessCode;
}

int WaitedSignalHandler::quitProcess()
{
    return kStandardSuccessCode;
}
