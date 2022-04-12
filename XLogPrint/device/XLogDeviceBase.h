#ifndef XLOGDEVICEBASE_H
#define XLOGDEVICEBASE_H
#include <string>
#include "../XLogRule.h"

class XLogDeviceBase
{
public:
    XLogDeviceBase()
    {
        mp_rule = nullptr;
    }
    virtual ~XLogDeviceBase(){};
    void setRule(XLogRule *rule){mp_rule = rule;}

    //基类做最基本的数据处理
    virtual bool PrintLog(std::string& log, PriorityLevel level)
    {
        if (mp_rule == nullptr)
        {
            return true;
        }

        if (level >mp_rule->getOutputLevel())
            return false;

        std::string header;
        switch (level)
        {
        case PriorityLevel::DEBUG:
            header = mp_rule->getDebugHeader();
            break;

        case PriorityLevel::INFO:
            header = mp_rule->getInfoHeader();
            break;

        case PriorityLevel::WARN:
            header = mp_rule->getWarnHeader();
            break;

        case PriorityLevel::ERROR:
            header = mp_rule->getErrorHeader();
            break;
        default:
            break;
        }

        std::string pack = mp_rule->onPacket(log);
        log = header + pack;

        mp_rule->savePacket(log);
        return true;
    }

protected:
    XLogRule *mp_rule;
};

#endif // XLOGDEVICEBASE_H
