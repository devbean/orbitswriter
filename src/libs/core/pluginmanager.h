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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "pluginmanager_p.h"

#include <QObject>

namespace Core
{

class PluginManager : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Internal::PluginManager)
    QScopedPointer<Internal::PluginManagerPrivate> const d_ptr;

public:
    explicit PluginManager(QObject *parent = 0);

    void loadPlugins();

    template <typename T> QList<T *> plugins() const
    {
        Q_D(const Internal::PluginManager);

        QList<T *> results;
        for (auto plugin : d->plugins) {
            T *result = qobject_cast<T *>(plugin);
            if (result) {
                results.append(result);
            }
        }
        return results;
    }

}; // end of class PluginManager

} // end of namespace Core

#endif // PLUGINMANAGER_H
