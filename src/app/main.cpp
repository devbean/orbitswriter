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

#include "version.h"

#include <core/appcontext.h>

#include <QApplication>
#include <QDebug>
#include <QSettings>

#ifdef Q_OS_MAC
#  define CONFIG_PATH "/../Resources"
#else
#  define CONFIG_PATH "/config"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QLatin1String(Application::ORGANIZATION));
    QCoreApplication::setOrganizationDomain(QLatin1String(Application::ORGANIZATION_DOMAIN));
    QCoreApplication::setApplicationName(QLatin1String(Application::APPLICATION_NAME));
    QCoreApplication::setApplicationVersion(QLatin1String(Application::VERSION_LONG));

    QApplication app(argc, argv);

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::applicationDirPath() + QLatin1String(CONFIG_PATH));
    QSettings::setDefaultFormat(QSettings::IniFormat);

    // it will transfer owner to AppContext
    QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                        QLatin1String(Application::SETTINGSVARIANT_STR),
                                        QLatin1String(Application::APPLICATION_NAME));

    Core::AppContext ctx;
    ctx.setSettings(settings);
    ctx.start();

    return app.exec();
}
