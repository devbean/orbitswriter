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

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "appcontext_p.h"
#include "core_global.h"

#include <QObject>

namespace Core
{

class MainWindow;

class CORE_EXPORT AppContext : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Internal::AppContext)
    QScopedPointer<Internal::AppContextPrivate> const d_ptr;

public:
    static AppContext * instance();

    explicit AppContext(QObject *parent = 0);

    void start();
    void shutdown();

    // settings
    void setSettings(QSettings *settings);

    MainWindow *mainWindow() const;
}; // end of class Core::AppContext

} // end of namespace Core

#endif // APPCONTEXT_H
