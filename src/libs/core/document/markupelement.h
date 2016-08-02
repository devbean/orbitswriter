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

#ifndef MARKUPELEMENT_H
#define MARKUPELEMENT_H

#include <QList>
#include <QSet>

namespace Core
{

/*!
 * Tags that may be open.
 */
enum class MarkupElement {
    None = 0x0,               /// No tags are open.
    SuperScript = 0x01,       /// A superscript tag is open.
    SubScript = 0x02,         /// A subscript tag is open.
    Anchor = 0x04,            /// An anchor tag is open.
    SpanForeground = 0x08,    /// A foreground altering span tag is open.
    SpanBackground = 0x10,    /// A background altering span tag is open.
    SpanFontFamily = 0x20,    /// A font family altering span tag is open.
    SpanFontPointSize = 0x40, /// A font size altering span tag is open.
    Strong = 0x80,            /// A strong tag is open.
    Emph = 0x100,             /// A emphasis tag is open.
    Underline = 0x200,        /// An underline tag is open.
    StrikeOut = 0x400         /// A strikeout tag is open.
};

typedef QList<MarkupElement> ElementList;
typedef QSet<MarkupElement> ElementSet;

} // end of namespace Core

inline uint qHash(const Core::MarkupElement &key)
{
    return qHash(static_cast<int>(key));
}

#endif // MARKUPELEMENT_H
