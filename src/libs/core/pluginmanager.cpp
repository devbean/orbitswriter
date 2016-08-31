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

#include "plugin.h"
#include "pluginmanager.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QPluginLoader>

namespace Core
{

namespace Internal
{

PluginManagerPrivate::PluginManagerPrivate(PluginManager *mgr)
    : q_ptr(mgr)
{

}

void PluginManagerPrivate::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *obj = pluginLoader.instance();
        if (obj) {
            Plugin *plugin = qobject_cast<Plugin *>(obj);
            if (plugin) {
                plugins.append(plugin);
                qDebug() << plugin->metaObject()->className() << "has loaded.";
            } else {
                qDebug() << "Plugins should inherits Core::Plugin.";
            }
        } else {
            qDebug() << pluginLoader.errorString();
        }
    }
}

//---------- PluginManagerPrivate ----------//



} // end of namespace Core::Internal

//---------- PluginManager ----------//

PluginManager::PluginManager(QObject *parent)
    : QObject(parent),
      d_ptr(new Internal::PluginManagerPrivate(this))
{

}

void PluginManager::loadPlugins()
{
    Q_D(Internal::PluginManager);
    d->loadPlugins();
}

}
