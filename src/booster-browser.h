#ifndef BOOSTER_SILICA_H
#define BOOSTER_SILICA_H

#include "eventhandler.h"
#include "booster.h"

class BrowserBooster : public Booster
{
public:
    virtual const std::string &boosterType() const;
    virtual bool preload();

protected:
    virtual bool receiveDataFromInvoker(int socketFd);
    virtual void preinit();

private:
    static const std::string m_boosterType;
};

#endif
