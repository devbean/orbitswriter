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

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "core/plugin.h"

namespace Core
{

class CORE_EXPORT Publisher : public Plugin
{
    Q_OBJECT
public:
    virtual ~Publisher() {}

    virtual QString targetName() const = 0;
    virtual QString targetVersion() const = 0;
}; // end of class Core::Publisher

} // end of namespace Core

#define Publisher_iid "org.galaxyworld.orbitswriter.Publisher"

Q_DECLARE_INTERFACE(Core::Publisher, Publisher_iid)

#endif // PUBLISHER_H
