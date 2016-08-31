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

#ifndef WORDPRESSPUBLISHER_H
#define WORDPRESSPUBLISHER_H

#include <Core/Publisher>
#include <Core/Plugin>
#include <QObject>

class WordPressPublisher : public Core::Plugin, public Core::Publisher
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Publisher_iid FILE "wordpresspublisher.json")
    Q_INTERFACES(Core::Publisher)
public:
    explicit WordPressPublisher();
    virtual ~WordPressPublisher() {}

    virtual QString name() const Q_DECL_OVERRIDE;
    virtual QString version() const Q_DECL_OVERRIDE;
    virtual QString vendor() const Q_DECL_OVERRIDE;

    virtual QString targetName() const Q_DECL_OVERRIDE;
    virtual QString targetVersion() const Q_DECL_OVERRIDE;
};

#endif // WORDPRESSPUBLISHER_H
