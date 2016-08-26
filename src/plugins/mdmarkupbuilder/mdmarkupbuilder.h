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

#ifndef MDMARKUPBUILDER_H
#define MDMARKUPBUILDER_H

#include "mdmarkupbuilder_p.h"

#include <Core/MarkupBuilder>
#include <QObject>

class MDMarkupBuilder : public Core::MarkupBuilder
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MarkupBuilder_iid FILE "mdmarkupbuilder.json")
    Q_INTERFACES(Core::MarkupBuilder)
    Q_DECLARE_PRIVATE(MDMarkupBuilder)
    QScopedPointer<MDMarkupBuilderPrivate> const d_ptr;
public:
    MDMarkupBuilder();
    virtual ~MDMarkupBuilder() {}

    virtual QString markupName() const Q_DECL_OVERRIDE;

    virtual QString name() const Q_DECL_OVERRIDE;
    virtual QString version() const Q_DECL_OVERRIDE;
    virtual QString vendor() const Q_DECL_OVERRIDE;

    virtual void beginStrong() Q_DECL_OVERRIDE;
    virtual void endStrong() Q_DECL_OVERRIDE;

    virtual void beginEmphasised() Q_DECL_OVERRIDE;
    virtual void endEmphasised() Q_DECL_OVERRIDE;

    virtual void beginUnderline() Q_DECL_OVERRIDE;
    virtual void endUnderline() Q_DECL_OVERRIDE;

    virtual void beginStrikeout() Q_DECL_OVERRIDE;
    virtual void endStrikeout() Q_DECL_OVERRIDE;

    virtual void beginForeground(const QBrush &brush) Q_DECL_OVERRIDE;
    virtual void endForeground() Q_DECL_OVERRIDE;

    virtual void beginBackground(const QBrush &brush) Q_DECL_OVERRIDE;
    virtual void endBackground() Q_DECL_OVERRIDE;

    virtual void beginAnchor(const QString &href = QString(), const QString &name = QString()) Q_DECL_OVERRIDE;
    virtual void endAnchor() Q_DECL_OVERRIDE;

    virtual void beginFontFamily(const QString &family) Q_DECL_OVERRIDE;
    virtual void endFontFamily() Q_DECL_OVERRIDE;

    virtual void beginFontPointSize(int size) Q_DECL_OVERRIDE;
    virtual void endFontPointSize() Q_DECL_OVERRIDE;

    virtual void beginParagraph(Qt::Alignment a = Qt::AlignLeft, qreal top = 0.0, qreal bottom = 0.0, qreal left = 0.0, qreal right = 0.0) Q_DECL_OVERRIDE;
    virtual void endParagraph() Q_DECL_OVERRIDE;

    virtual void addNewline() Q_DECL_OVERRIDE;

    virtual void insertHorizontalRule(int width = -1) Q_DECL_OVERRIDE;

    virtual void insertImage(const QString &url, qreal width, qreal height) Q_DECL_OVERRIDE;

    virtual void beginList(QTextListFormat::Style style) Q_DECL_OVERRIDE;
    virtual void endList() Q_DECL_OVERRIDE;

    virtual void beginListItem() Q_DECL_OVERRIDE;
    virtual void endListItem() Q_DECL_OVERRIDE;

    virtual void beginSuperscript() Q_DECL_OVERRIDE;
    virtual void endSuperscript() Q_DECL_OVERRIDE;

    virtual void beginSubscript() Q_DECL_OVERRIDE;
    virtual void endSubscript() Q_DECL_OVERRIDE;

    virtual void beginTable(qreal cellpadding, qreal cellspacing, const QString &width) Q_DECL_OVERRIDE;
    virtual void beginTableRow() Q_DECL_OVERRIDE;
    virtual void beginTableHeaderCell(const QString &width, int colSpan, int rowSpan) Q_DECL_OVERRIDE;
    virtual void beginTableCell(const QString &width, int colSpan, int rowSpan) Q_DECL_OVERRIDE;
    virtual void endTable() Q_DECL_OVERRIDE;
    virtual void endTableRow() Q_DECL_OVERRIDE;
    virtual void endTableHeaderCell() Q_DECL_OVERRIDE;
    virtual void endTableCell() Q_DECL_OVERRIDE;

    virtual void beginHeader(int level) Q_DECL_OVERRIDE;
    virtual void endHeader(int level) Q_DECL_OVERRIDE;

    virtual void appendLiteralText(const QString &text) Q_DECL_OVERRIDE;

    virtual void appendRawText(const QString &text) Q_DECL_OVERRIDE;

    virtual QString result() Q_DECL_OVERRIDE;
};

#endif // MDMARKUPBUILDER_H
