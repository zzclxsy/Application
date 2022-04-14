#ifndef XTIMEREVENT_H
#define XTIMEREVENT_H

#include "XEvent.h"
#include <functional>
#include <thread>
#include "../global.h"

class XTimerEventPrivate;
class FRAMEWORK_EXPORT XTimerEvent : public XEvent
{
    typedef struct {

    }S_TimerAttr;
public:
    XTimerEvent();
    virtual void doWork();
    void setTimer(int msec, std::function<void()> callbakc, bool isSingle = false);
    void setTrigger(int msec);
    void setThreadModel(bool isThread);

    void stop();
    void start();

private:
    void runThread();

private:
    XTimerEventPrivate *d_ptr;
};

#endif // XTIMEREVENT_H
