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

#include "htmlmarkupbuilder.h"

//---------- HTMLMarkupBuilderPrivate ----------//

HTMLMarkupBuilderPrivate::HTMLMarkupBuilderPrivate(HTMLMarkupBuilder *builder)
    : q_ptr(builder)
{

}

//---------- HTMLMarkupBuilder ----------//

HTMLMarkupBuilder::HTMLMarkupBuilder(QObject *parent)
    : QObject(parent),
      d_ptr(new HTMLMarkupBuilderPrivate(this))
{

}

QString HTMLMarkupBuilder::name() const
{
    return QStringLiteral("HtmlMarkupBuilder");
}

QString HTMLMarkupBuilder::version() const
{
    return QStringLiteral("1.0.0");
}

QString HTMLMarkupBuilder::vendor() const
{
    return QStringLiteral("galaxyworld.org");
}

void HTMLMarkupBuilder::beginStrong()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<strong>"));
}

void HTMLMarkupBuilder::endStrong()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</strong>"));
}

void HTMLMarkupBuilder::beginEmphasised()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<em>"));
}

void HTMLMarkupBuilder::endEmphasised()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</em>"));
}

void HTMLMarkupBuilder::beginUnderline()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<u>"));
}

void HTMLMarkupBuilder::endUnderline()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</u>"));
}

void HTMLMarkupBuilder::beginStrikeout()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<s>"));
}

void HTMLMarkupBuilder::endStrikeout()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</s>"));
}

void HTMLMarkupBuilder::beginForeground(const QBrush &brush)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"color:%1;\">").arg(brush.color().name()));
}

void HTMLMarkupBuilder::endForeground()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void HTMLMarkupBuilder::beginBackground(const QBrush &brush)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"background-color:%1;\">").arg(brush.color().name()));
}

void HTMLMarkupBuilder::endBackground()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void HTMLMarkupBuilder::beginAnchor(const QString &href, const QString &name)
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::endAnchor()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</a>"));
}

void HTMLMarkupBuilder::beginFontFamily(const QString &family)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"font-family:%1;\">").arg(family));
}

void HTMLMarkupBuilder::endFontFamily()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void HTMLMarkupBuilder::beginFontPointSize(int size)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<span style=\"font-size:%1pt;\">").arg(QString::number(size)));
}

void HTMLMarkupBuilder::endFontPointSize()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</span>"));
}

void HTMLMarkupBuilder::beginParagraph(Qt::Alignment a, qreal top, qreal bottom, qreal left, qreal right)
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::endParagraph()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</p>"));
}

void HTMLMarkupBuilder::addNewline()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<br />"));
}

void HTMLMarkupBuilder::insertHorizontalRule(int width)
{
    Q_D(HTMLMarkupBuilder);
    if (width != -1) {
        d->html.append(QStringLiteral("<hr width=\"%1\" />").arg(width));
    }
    d->html.append(QStringLiteral("<hr />"));
}

void HTMLMarkupBuilder::insertImage(const QString &url, qreal width, qreal height)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<img src=\"%1\" ").arg(url));
    if (width != 0) {
        d->html.append(QStringLiteral("width=\"%2\" ").arg(width));
    }
    if (height != 0) {
        d->html.append(QStringLiteral("height=\"%2\" ").arg(height));
    }
    d->html.append(QStringLiteral("/>"));
}

void HTMLMarkupBuilder::beginList(QTextListFormat::Style style)
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::endList()
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::beginListItem()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<li>"));
}

void HTMLMarkupBuilder::endListItem()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</li>"));
}

void HTMLMarkupBuilder::beginSuperscript()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<sup>"));
}

void HTMLMarkupBuilder::endSuperscript()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</sup>"));
}

void HTMLMarkupBuilder::beginSubscript()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<sub>"));
}

void HTMLMarkupBuilder::endSubscript()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</sub>"));
}

void HTMLMarkupBuilder::beginTable(qreal cellpadding, qreal cellspacing, const QString &width)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<table cellpadding=\"%1\" cellspacing=\"%2\" width=\"%3\" border=\"1\">")
                   .arg(cellpadding)
                   .arg(cellspacing)
                   .arg(width));
}

void HTMLMarkupBuilder::beginTableRow()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<tr>"));
}

void HTMLMarkupBuilder::beginTableHeaderCell(const QString &width, int colSpan, int rowSpan)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<th width=\"%1\" colspan=\"%2\" rowspan=\"%3\">")
                   .arg(width)
                   .arg(colSpan)
                   .arg(rowSpan));
}

void HTMLMarkupBuilder::beginTableCell(const QString &width, int colSpan, int rowSpan)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("<td width=\"%1\" colspan=\"%2\" rowspan=\"%3\">")
                   .arg(width)
                   .arg(colSpan)
                   .arg(rowSpan));
}

void HTMLMarkupBuilder::endTable()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</table>"));
}

void HTMLMarkupBuilder::endTableRow()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</tr>"));
}

void HTMLMarkupBuilder::endTableHeaderCell()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</th>"));
}

void HTMLMarkupBuilder::endTableCell()
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(QStringLiteral("</td>"));
}

void HTMLMarkupBuilder::beginHeader(int level)
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::endHeader(int level)
{
    Q_D(HTMLMarkupBuilder);
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

void HTMLMarkupBuilder::appendLiteralText(const QString &text)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(text.toHtmlEscaped());
}

void HTMLMarkupBuilder::appendRawText(const QString &text)
{
    Q_D(HTMLMarkupBuilder);
    d->html.append(text);
}

QString HTMLMarkupBuilder::getResult()
{
    Q_D(HTMLMarkupBuilder);
    auto ret = d->html;
    d->html.clear();
    return ret;
}
