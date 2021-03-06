/***************************************************************************
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
** Copyright (c) 2014 - 2022 Jolla Ltd.
** All rights reserved.
** Contact: Nokia Corporation (directui@nokia.com)
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

#include <QFileInfo>
#include <QtGlobal>
#include <QQuickView>
#include <QtQml>

#include "booster-browser.h"
#include "mdeclarativecache.h"
#include "connection.h"
#include "logger.h"
#include "daemon.h"

const string BrowserBooster::m_boosterType = "browser";

const string & BrowserBooster::boosterType() const
{
    return m_boosterType;
}

bool BrowserBooster::preload()
{
    // for performance reasons, and transparent covers
    QQuickWindow::setDefaultAlphaBuffer(true);

    QQuickView *view = MDeclarativeCache::populate();

    // Load a QML file that references common elements, which will compile and cache them all
    QString file = "/usr/share/booster-";
    file += boosterType().c_str();
    file += "/preload.qml";

    QQmlComponent component(view->engine(), QUrl::fromLocalFile(file));
    if (!component.isReady()) {
        Logger::logError("BrowserBooster: Preload component failed to load:");
        foreach (const QQmlError &e, component.errors())
            Logger::logError("BrowserBooster:    %s", e.toString().toLatin1().constData());
        return true;
    }

    // Create an instance of that object, which will initialize everything else
    QQmlContext context(view->engine());
    QObject *obj = component.create(&context);
    if (!obj)
        Logger::logError("BrowserBooster: Preload object creation failed");
    delete obj;

    return true;
}

bool BrowserBooster::receiveDataFromInvoker(int socketFd)
{
    // Use the default implementation if in boot mode
    // (it won't require QApplication running).

    if (bootMode()) {
        return Booster::receiveDataFromInvoker(socketFd);
    } else {
        // Setup the conversation channel with the invoker.
        setConnection(new Connection(socketFd));

        EventHandler handler(this);
        handler.runEventLoop();

        if (!connection()->connected()) {
            return false;
        }

        // Receive application data from the invoker
        if (!connection()->receiveApplicationData(appData())) {
            connection()->close();
            return false;
        }

        // Close the connection if exit status doesn't need
        // to be sent back to invoker
        if (!connection()->isReportAppExitStatusNeeded()) {
            connection()->close();
        }

        return true;
    }
}


void BrowserBooster::preinit()
{
    QString appName = QFileInfo(m_appData->argv()[0]).fileName();

    QString appClass = appName.left(1).toUpper();
    if (appName.length() > 1)
        appClass += appName.right(appName.length() - 1);

    // char* app_name = qstrdup(appName.toLatin1().data());
    // QApplication::setAppName(app_name);

    // char* app_class = qstrdup(appClass.toLatin1().data());
    // QApplication::setAppClass(app_class);
}

int main(int argc, char **argv)
{
    BrowserBooster *booster = new BrowserBooster;
    Daemon d(argc, argv);
    d.run(booster);
    return 0;
}

