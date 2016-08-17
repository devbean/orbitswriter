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

#include "htmlmarkupbuilderplugin.h"

QString HTMLMarkupBuilderPlugin::name() const
{
    return QStringLiteral("HtmlMarkupBuilder");
}

QString HTMLMarkupBuilderPlugin::version() const
{
    return QStringLiteral("1.0.0");
}

QString HTMLMarkupBuilderPlugin::vendor() const
{
    return QStringLiteral("galaxyworld.org");
}

void HTMLMarkupBuilderPlugin::beginStrong()
{

}

void HTMLMarkupBuilderPlugin::endStrong()
{

}

void HTMLMarkupBuilderPlugin::beginEmphasised()
{

}

void HTMLMarkupBuilderPlugin::endEmphasised()
{

}

void HTMLMarkupBuilderPlugin::beginUnderline()
{

}

void HTMLMarkupBuilderPlugin::endUnderline()
{

}

void HTMLMarkupBuilderPlugin::beginStrikeout()
{

}

void HTMLMarkupBuilderPlugin::endStrikeout()
{

}

void HTMLMarkupBuilderPlugin::beginForeground(const QBrush &brush)
{

}

void HTMLMarkupBuilderPlugin::endForeground()
{

}

void HTMLMarkupBuilderPlugin::beginBackground(const QBrush &brush)
{

}

void HTMLMarkupBuilderPlugin::endBackground()
{

}

void HTMLMarkupBuilderPlugin::beginAnchor(const QString &href, const QString &name)
{

}

void HTMLMarkupBuilderPlugin::endAnchor()
{

}

void HTMLMarkupBuilderPlugin::beginFontFamily(const QString &family)
{

}

void HTMLMarkupBuilderPlugin::endFontFamily()
{

}

void HTMLMarkupBuilderPlugin::beginFontPointSize(int size)
{

}

void HTMLMarkupBuilderPlugin::endFontPointSize()
{

}

void HTMLMarkupBuilderPlugin::beginParagraph(Qt::Alignment a, qreal top, qreal bottom, qreal left, qreal right)
{

}

void HTMLMarkupBuilderPlugin::endParagraph()
{

}

void HTMLMarkupBuilderPlugin::addNewline()
{

}

void HTMLMarkupBuilderPlugin::insertHorizontalRule(int width)
{

}

void HTMLMarkupBuilderPlugin::insertImage(const QString &url, qreal width, qreal height)
{

}

void HTMLMarkupBuilderPlugin::beginList(QTextListFormat::Style style)
{

}

void HTMLMarkupBuilderPlugin::endList()
{

}

void HTMLMarkupBuilderPlugin::beginListItem()
{

}

void HTMLMarkupBuilderPlugin::endListItem()
{

}

void HTMLMarkupBuilderPlugin::beginSuperscript()
{

}

void HTMLMarkupBuilderPlugin::endSuperscript()
{

}

void HTMLMarkupBuilderPlugin::beginSubscript()
{

}

void HTMLMarkupBuilderPlugin::endSubscript()
{

}

void HTMLMarkupBuilderPlugin::beginTable(qreal cellpadding, qreal cellspacing, const QString &width)
{

}

void HTMLMarkupBuilderPlugin::beginTableRow()
{

}

void HTMLMarkupBuilderPlugin::beginTableHeaderCell(const QString &width, int colSpan, int rowSpan)
{

}

void HTMLMarkupBuilderPlugin::beginTableCell(const QString &width, int colSpan, int rowSpan)
{

}

void HTMLMarkupBuilderPlugin::endTable()
{

}

void HTMLMarkupBuilderPlugin::endTableRow()
{

}

void HTMLMarkupBuilderPlugin::endTableHeaderCell()
{

}

void HTMLMarkupBuilderPlugin::endTableCell()
{

}

void HTMLMarkupBuilderPlugin::beginHeader(int level)
{

}

void HTMLMarkupBuilderPlugin::endHeader(int level)
{

}

void HTMLMarkupBuilderPlugin::appendLiteralText(const QString &text)
{

}

void HTMLMarkupBuilderPlugin::appendRawText(const QString &text)
{

}

QString HTMLMarkupBuilderPlugin::getResult()
{
    return "HTML";
}
