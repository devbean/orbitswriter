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

#ifndef HTMLMARKUPBUILDERPLUGIN_H
#define HTMLMARKUPBUILDERPLUGIN_H

#include <Core/MarkupBuilder>
#include <QObject>

class HTMLMarkupBuilderPlugin : public QObject, Core::MarkupBuilder
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MarkupBuilder_iid FILE "htmlmarkupbuilder.json")
    Q_INTERFACES(Core::MarkupBuilder)
public:
    virtual ~HTMLMarkupBuilderPlugin() {}

    virtual QString name() const;
    virtual QString version() const;
    virtual QString vendor() const;

    virtual void beginStrong();
    virtual void endStrong();

    virtual void beginEmphasised();
    virtual void endEmphasised();

    virtual void beginUnderline();
    virtual void endUnderline();

    virtual void beginStrikeout();
    virtual void endStrikeout();

    virtual void beginForeground(const QBrush &brush);
    virtual void endForeground();

    virtual void beginBackground(const QBrush &brush);
    virtual void endBackground();

    virtual void beginAnchor(const QString &href = QString(), const QString &name = QString());
    virtual void endAnchor();

    virtual void beginFontFamily(const QString &family);
    virtual void endFontFamily();

    virtual void beginFontPointSize(int size);
    virtual void endFontPointSize();

    virtual void beginParagraph(Qt::Alignment a = Qt::AlignLeft, qreal top = 0.0, qreal bottom = 0.0, qreal left = 0.0, qreal right = 0.0);
    virtual void endParagraph();

    virtual void addNewline();

    virtual void insertHorizontalRule(int width = -1);

    virtual void insertImage(const QString &url, qreal width, qreal height);

    virtual void beginList(QTextListFormat::Style style);
    virtual void endList();

    virtual void beginListItem();
    virtual void endListItem();

    virtual void beginSuperscript();
    virtual void endSuperscript();

    virtual void beginSubscript();
    virtual void endSubscript();

    virtual void beginTable(qreal cellpadding, qreal cellspacing, const QString &width);
    virtual void beginTableRow();
    virtual void beginTableHeaderCell(const QString &width, int colSpan, int rowSpan);
    virtual void beginTableCell(const QString &width, int colSpan, int rowSpan);
    virtual void endTable();
    virtual void endTableRow();
    virtual void endTableHeaderCell();
    virtual void endTableCell();

    virtual void beginHeader(int level);
    virtual void endHeader(int level);

    virtual void appendLiteralText(const QString &text);

    virtual void appendRawText(const QString &text);

    virtual QString getResult();
};

#endif // HTMLMARKUPBUILDERPLUGIN_H
