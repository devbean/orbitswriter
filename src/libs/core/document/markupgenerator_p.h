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

#ifndef MARKUPGENERATOR_P_H
#define MARKUPGENERATOR_P_H

#include <QBrush>
#include <QObject>
#include <QSet>

#include "markupelement.h"

namespace Core
{

class MarkupBuilder;
class MarkupGenerator;

namespace Internal
{

class MarkupGeneratorPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MarkupGeneratorPrivate)
    Q_DECLARE_PUBLIC(Core::MarkupGenerator)
    MarkupGenerator * const q_ptr;

    MarkupGeneratorPrivate(MarkupGenerator *gen);

    MarkupBuilder *builder;

    QString openedAnchorHref;
    QString openedAnchorName;
    QString anchorHrefToOpen;

    QBrush openedForeground;
    QBrush foregroundToOpen;

    QBrush openedBackground;
    QBrush backgroundToOpen;

    int openedFontPointSize;
    int fontPointSizeToOpen;

    QString openedFontFamily;
    QString fontFamilyToOpen;

    // An ordered list containing the order elements were opened in.
    ElementList openedElements;

    // Elements that have yet to be opened.
    // Used while determine the order to open them.
    ElementSet elementsToOpen;

public:
    ~MarkupGeneratorPrivate();
}; // end of class Core::Internal::AppContextPrivate

} // end of namespace Core::Internal

} // end of namespace Core

#endif // MARKUPGENERATOR_P_H
