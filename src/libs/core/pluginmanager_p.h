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

#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

#include <QList>
#include <QObject>

namespace Core
{

class Plugin;
class PluginManager;

namespace Internal
{

class PluginManagerPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PluginManagerPrivate)
    Q_DECLARE_PUBLIC(Core::PluginManager)
    PluginManager * const q_ptr;

    PluginManagerPrivate(PluginManager *mgr);

    void loadPlugins();

    QList<Plugin *> plugins;

}; // end of class Core::Internal::PluginManagerPrivate

} // end of namespace Core::Internal

} // end of namespace Core

#endif // PLUGINMANAGER_P_H
