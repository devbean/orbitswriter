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

#ifndef SOURCEEDITOR_H
#define SOURCEEDITOR_H

#include "document/markupbuilder.h"

#include <QTextEdit>

namespace Core
{

class SourceEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit SourceEditor(MarkupBuilder *builder, QWidget *parent = 0);

    void updateSource(QTextDocument *document);

private:
    MarkupBuilder *builder;
}; // end of class Core::SourceEditor

} // end of namespace Core

#endif // SOURCEEDITOR_H
