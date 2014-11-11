/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** Copyright (C) 2014 Jolla Ltd.
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
** Contact: Raine Makelainen (raine.makelainen@jolla.com)
**
** This file is part of applauncherd
**
** If you have questions regarding the use of this file, please contact
** Nokia at directui@nokia.com.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

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
