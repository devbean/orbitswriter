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

#include "appcontext.h"
#include "mainwindow.h"
#include "pluginmanager.h"

namespace Core
{

static AppContext *_INSTANCE = nullptr;

namespace Internal
{

//---------- AppContextPrivate ----------//

AppContextPrivate::AppContextPrivate(AppContext *ctx)
    : q_ptr(ctx),
      mainWindow(new MainWindow),
      pluginManager(new PluginManager)
{
    contextListeners.append(this);
}

AppContextPrivate::~AppContextPrivate()
{
    delete mainWindow;
    delete pluginManager;
}

void AppContextPrivate::onAppContextStarted()
{
    readSettings();
}

void AppContextPrivate::onAppContextAboutToExit()
{
    writeSettings();
}

static const char * const GROUP_MAINWINDOW  = "MainWindow";
static const char * const SETTINGS_SIZE     = "size";
static const char * const SETTINGS_POSITION = "pos";

void AppContextPrivate::writeSettings()
{
    settings->beginGroup(QLatin1String(GROUP_MAINWINDOW));
    settings->setValue(QLatin1String(SETTINGS_SIZE), mainWindow->size());
    settings->setValue(QLatin1String(SETTINGS_POSITION), mainWindow->pos());
    settings->endGroup();
}

void AppContextPrivate::readSettings()
{
    settings->beginGroup(QLatin1String(GROUP_MAINWINDOW));
    mainWindow->resize(settings->value(QLatin1String(SETTINGS_SIZE), QSize(1024, 768)).toSize());
    mainWindow->move(settings->value(QLatin1String(SETTINGS_POSITION), QPoint(200, 200)).toPoint());
    settings->endGroup();
}

} // end of namespace Core::Internal

//---------- AppContext ----------//

AppContext *AppContext::instance()
{
    return _INSTANCE;
}

AppContext::AppContext(QObject *parent)
    : QObject(parent),
      d_ptr(new Internal::AppContextPrivate(this))
{
    _INSTANCE = this;
}

void AppContext::start()
{
    Q_D(Internal::AppContext);

    d->pluginManager->loadPlugins();

    for (AppContextListener *listener : d->contextListeners) {
        listener->onAppContextStarted();
    }

    d->mainWindow->show();
}

void AppContext::shutdown()
{
    Q_D(Internal::AppContext);

    for (AppContextListener *listener : d->contextListeners) {
        listener->onAppContextAboutToExit();
    }
}

void AppContext::setSettings(QSettings *settings)
{
    Q_D(Internal::AppContext);

    d->settings = settings;
    if (d->settings) {
        d->settings->setParent(d);
    }
}

MainWindow *AppContext::mainWindow() const
{
    Q_D(const Internal::AppContext);
    return d->mainWindow;
}

} // end of namespace Core

#include "moc_appcontext.cpp"
