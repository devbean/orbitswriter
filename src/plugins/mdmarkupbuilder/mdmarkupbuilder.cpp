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

#include "mdmarkupbuilder.h"

//---------- MDMarkupBuilderPrivate ----------//

MDMarkupBuilderPrivate::MDMarkupBuilderPrivate(MDMarkupBuilder *builder)
    : q_ptr(builder)
{

}

//---------- MDMarkupBuilder ----------//

MDMarkupBuilder::MDMarkupBuilder()
    : d_ptr(new MDMarkupBuilderPrivate(this))
{

}

QString MDMarkupBuilder::markupName() const
{
    return QStringLiteral("Markdown");
}

QString MDMarkupBuilder::name() const
{
    return QStringLiteral("MDMarkupBuilder");
}

QString MDMarkupBuilder::version() const
{
    return QStringLiteral("1.0.0");
}

QString MDMarkupBuilder::vendor() const
{
    return QStringLiteral("galaxyworld.org");
}

void MDMarkupBuilder::beginStrong()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<strong>"));
}

void MDMarkupBuilder::endStrong()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</strong>"));
}

void MDMarkupBuilder::beginEmphasised()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<em>"));
}

void MDMarkupBuilder::endEmphasised()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</em>"));
}

void MDMarkupBuilder::beginUnderline()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<u>"));
}

void MDMarkupBuilder::endUnderline()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</u>"));
}

void MDMarkupBuilder::beginStrikeout()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<s>"));
}

void MDMarkupBuilder::endStrikeout()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</s>"));
}

void MDMarkupBuilder::beginForeground(const QBrush &brush)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"color:%1;\">").arg(brush.color().name()));
}

void MDMarkupBuilder::endForeground()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void MDMarkupBuilder::beginBackground(const QBrush &brush)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"background-color:%1;\">").arg(brush.color().name()));
}

void MDMarkupBuilder::endBackground()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void MDMarkupBuilder::beginAnchor(const QString &href, const QString &name)
{
    Q_D(MDMarkupBuilder);
    if (!href.isEmpty()) {
        if (!name.isEmpty()) {
            d->html.append(QStringLiteral("<a href=\"%1\" name=\"%2\">").arg(href, name));
        } else {
            d->html.append(QStringLiteral("<a href=\"%1\">").arg(href));
        }
    } else {
        if (!name.isEmpty()) {
            d->html.append(QStringLiteral("<a name=\"%1\">").arg(name));
        }
    }
}

void MDMarkupBuilder::endAnchor()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</a>"));
}

void MDMarkupBuilder::beginFontFamily(const QString &family)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"font-family:%1;\">").arg(family));
}

void MDMarkupBuilder::endFontFamily()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void MDMarkupBuilder::beginFontPointSize(int size)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"font-size:%1pt;\">").arg(QString::number(size)));
}

void MDMarkupBuilder::endFontPointSize()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void MDMarkupBuilder::beginParagraph(Qt::Alignment a, qreal top, qreal bottom, qreal left, qreal right)
{
    Q_D(MDMarkupBuilder);
    QString style;
    if (top != 0) {
        style.append(QStringLiteral("margin-top:%1;").arg(top));
    }
    if (bottom != 0) {
        style.append(QStringLiteral("margin-bottom:%1;").arg(bottom));
    }
    if (left != 0) {
        style.append(QStringLiteral("margin-left:%1;").arg(left));
    }
    if (right != 0) {
        style.append(QStringLiteral("margin-right:%1;").arg(right));
    }

    if (a & Qt::AlignRight) {
        d->html.append(QStringLiteral("<p align=\"right\" "));
    } else if (a & Qt::AlignHCenter) {
        d->html.append(QStringLiteral("<p align=\"center\" "));
    } else if (a & Qt::AlignJustify) {
        d->html.append(QStringLiteral("<p align=\"justify\" "));
    } else if (a & Qt::AlignLeft) {
        d->html.append(QStringLiteral("<p"));
    } else {
        d->html.append(QStringLiteral("<p"));
    }

    if (!style.isEmpty()) {
        d->html.append(QStringLiteral(" \"") + style + QLatin1Char('"'));
    }
    d->html.append(QLatin1Char('>'));
}

void MDMarkupBuilder::endParagraph()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</p>"));
}

void MDMarkupBuilder::addNewline()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<br />"));
}

void MDMarkupBuilder::insertHorizontalRule(int width)
{
    Q_D(MDMarkupBuilder);
    if (width != -1) {
        d->html.append(QStringLiteral("<hr width=\"%1\" />").arg(width));
    }
    d->html.append(QStringLiteral("<hr />"));
}

void MDMarkupBuilder::insertImage(const QString &url, qreal width, qreal height)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<img src=\"%1\" ").arg(url));
    if (width != 0) {
        d->html.append(QStringLiteral("width=\"%2\" ").arg(width));
    }
    if (height != 0) {
        d->html.append(QStringLiteral("height=\"%2\" ").arg(height));
    }
    d->html.append(QStringLiteral("/>"));
}

void MDMarkupBuilder::beginList(QTextListFormat::Style style)
{
    Q_D(MDMarkupBuilder);
    d->currentListItemStyles.append(style);
    switch (style) {
    case QTextListFormat::ListDisc:
        d->html.append(QStringLiteral("<ul type=\"disc\">"));
        break;
    case QTextListFormat::ListCircle:
        d->html.append(QStringLiteral("<ul type=\"circle\">"));
        break;
    case QTextListFormat::ListSquare:
        d->html.append(QStringLiteral("<ul type=\"square\">"));
        break;
    case QTextListFormat::ListDecimal:
        d->html.append(QStringLiteral("<ol type=\"1\">"));
        break;
    case QTextListFormat::ListLowerAlpha:
        d->html.append(QStringLiteral("<ol type=\"a\">"));
        break;
    case QTextListFormat::ListUpperAlpha:
        d->html.append(QStringLiteral("<ol type=\"A\">"));
        break;
    case QTextListFormat::ListLowerRoman:
        d->html.append(QStringLiteral("<ol type=\"i\">"));
        break;
    case QTextListFormat::ListUpperRoman:
        d->html.append(QStringLiteral("<ol type=\"I\">"));
        break;
    default:
        break;
    }
}

void MDMarkupBuilder::endList()
{
    Q_D(MDMarkupBuilder);
    switch (d->currentListItemStyles.last()) {
    case QTextListFormat::ListDisc:
    case QTextListFormat::ListCircle:
    case QTextListFormat::ListSquare:
        d->html.append(QStringLiteral("</ul>"));
        break;
    case QTextListFormat::ListDecimal:
    case QTextListFormat::ListLowerAlpha:
    case QTextListFormat::ListUpperAlpha:
    case QTextListFormat::ListLowerRoman:
    case QTextListFormat::ListUpperRoman:
        d->html.append(QStringLiteral("</ol>"));
        break;
    default:
        break;
    }
    d->currentListItemStyles.removeLast();
}

void MDMarkupBuilder::beginListItem()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<li>"));
}

void MDMarkupBuilder::endListItem()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</li>"));
}

void MDMarkupBuilder::beginSuperscript()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<sup>"));
}

void MDMarkupBuilder::endSuperscript()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</sup>"));
}

void MDMarkupBuilder::beginSubscript()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<sub>"));
}

void MDMarkupBuilder::endSubscript()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</sub>"));
}

void MDMarkupBuilder::beginTable(qreal cellpadding, qreal cellspacing, const QString &width)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<table cellpadding=\"%1\" cellspacing=\"%2\" width=\"%3\" border=\"1\">")
                   .arg(cellpadding)
                   .arg(cellspacing)
                   .arg(width));
}

void MDMarkupBuilder::beginTableRow()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<tr>"));
}

void MDMarkupBuilder::beginTableHeaderCell(const QString &width, int colSpan, int rowSpan)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<th width=\"%1\" colspan=\"%2\" rowspan=\"%3\">")
                   .arg(width)
                   .arg(colSpan)
                   .arg(rowSpan));
}

void MDMarkupBuilder::beginTableCell(const QString &width, int colSpan, int rowSpan)
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("<td width=\"%1\" colspan=\"%2\" rowspan=\"%3\">")
                   .arg(width)
                   .arg(colSpan)
                   .arg(rowSpan));
}

void MDMarkupBuilder::endTable()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</table>"));
}

void MDMarkupBuilder::endTableRow()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</tr>"));
}

void MDMarkupBuilder::endTableHeaderCell()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</th>"));
}

void MDMarkupBuilder::endTableCell()
{
    Q_D(MDMarkupBuilder);
    d->html.append(QStringLiteral("</td>"));
}

void MDMarkupBuilder::beginHeader(int level)
{
    Q_D(MDMarkupBuilder);
    switch (level) {
    case 1:
        d->html.append(QStringLiteral("<h1>"));
        break;
    case 2:
        d->html.append(QStringLiteral("<h2>"));
        break;
    case 3:
        d->html.append(QStringLiteral("<h3>"));
        break;
    case 4:
        d->html.append(QStringLiteral("<h4>"));
        break;
    case 5:
        d->html.append(QStringLiteral("<h5>"));
        break;
    case 6:
        d->html.append(QStringLiteral("<h6>"));
        break;
    default:
        break;
    }
}

void MDMarkupBuilder::endHeader(int level)
{
    Q_D(MDMarkupBuilder);
    switch (level) {
    case 1:
        d->html.append(QStringLiteral("</h1>"));
        break;
    case 2:
        d->html.append(QStringLiteral("</h2>"));
        break;
    case 3:
        d->html.append(QStringLiteral("</h3>"));
        break;
    case 4:
        d->html.append(QStringLiteral("</h4>"));
        break;
    case 5:
        d->html.append(QStringLiteral("</h5>"));
        break;
    case 6:
        d->html.append(QStringLiteral("</h6>"));
        break;
    default:
        break;
    }
}

void MDMarkupBuilder::appendLiteralText(const QString &text)
{
    Q_D(MDMarkupBuilder);
    d->html.append(text.toHtmlEscaped());
}

void MDMarkupBuilder::appendRawText(const QString &text)
{
    Q_D(MDMarkupBuilder);
    d->html.append(text);
}

QString MDMarkupBuilder::result()
{
    Q_D(MDMarkupBuilder);
    auto ret = d->html;
    d->html.clear();
    return ret;
}
