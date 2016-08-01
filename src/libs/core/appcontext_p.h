/*-------------------------------------------------
 *
 * OrbitsWriter - An Offline Blog Writer
 *
 * Copyright (C) 2016  devbean@galaxyworld.org
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *-------------------------------------------------*/

#ifndef APPCONTEXT_P_H
#define APPCONTEXT_P_H

#include "appcontextlistener.h"

#include <QObject>
#include <QSettings>

namespace Core
{

class AppContext;
class AppContextListener;
class MainWindow;

namespace Internal
{

class AppContextPrivate : public QObject, public AppContextListener
{
    Q_OBJECT
    Q_DISABLE_COPY(AppContextPrivate)
    Q_DECLARE_PUBLIC(Core::AppContext)
    AppContext * const q_ptr;

    AppContextPrivate(AppContext *ctx);

    // AppContextListener
    void onAppContextStarted() Q_DECL_OVERRIDE;
    void onAppContextAboutToExit() Q_DECL_OVERRIDE;

    // settings
    void writeSettings();
    void readSettings();

    MainWindow *mainWindow;
    QSettings *settings;
    QList<AppContextListener *> contextListeners;

public:
    ~AppContextPrivate();
}; // end of class Core::Internal::AppContextPrivate

} // end of namespace Core::Internal

} // end of namespace Core

#endif // APPCONTEXT_P_H
