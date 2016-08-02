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

#include "markupbuilder.h"
#include "markupgenerator.h"

#include <QTextDocument>
#include <QTextList>

namespace Core
{

namespace Internal
{

MarkupGeneratorPrivate::MarkupGeneratorPrivate(MarkupGenerator *gen)
    : q_ptr(gen)
{

}

MarkupGeneratorPrivate::~MarkupGeneratorPrivate()
{
    delete this->builder;
}

} // end of namespace Internal

//---------- MarkupGenerator ----------//

MarkupGenerator::MarkupGenerator(MarkupBuilder *builder, QObject *parent)
    : QObject(parent),
      d_ptr(new Internal::MarkupGeneratorPrivate(this))
{
    Q_D(Internal::MarkupGenerator);

    d->builder = builder;
}

void MarkupGenerator::processDocument(QTextDocument *doc)
{
    processFrame(QTextFrame::iterator(), doc->rootFrame());
}

QTextFrame::iterator MarkupGenerator::processFrame(QTextFrame::iterator it, QTextFrame *frame)
{
    if (frame) {
        processDocumentContents(frame->begin(), frame->end());
    }

    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

QTextFrame::iterator MarkupGenerator::processBlock(QTextFrame::iterator it, const QTextBlock &block)
{
    if (block.isValid()) {
        auto fmt = block.blockFormat();
        auto object = block.document()->objectForFormat(fmt);
        if (object) {
            return processObject(it, block, object);
        } else {
            return processBlockContents(it, block);
        }
    }

    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

QTextFrame::iterator MarkupGenerator::processObject(QTextFrame::iterator it, const QTextBlock &block, QTextObject *textObject)
{
    auto group = qobject_cast<QTextBlockGroup *>(textObject);
    if (group) {
        return processBlockGroup(it, block, group).first;
    }
    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

MarkupGenerator::IteratorAndBlock MarkupGenerator::processBlockGroup(QTextFrame::iterator it, const QTextBlock &block, QTextBlockGroup *textBlockGroup)
{
    auto list = qobject_cast<QTextList *>(textBlockGroup);
    if (list) {
        return processList(it, block, list);
    }
    return skipBlockGroup(it, block, textBlockGroup);
}

MarkupGenerator::IteratorAndBlock MarkupGenerator::processList(QTextFrame::iterator it, const QTextBlock &block, QTextList *textList)
{
    Q_D(Internal::MarkupGenerator);

    auto style = textList->format().style();
    d->builder->beginList(style);
    auto thisBlock = block;
    while (thisBlock.isValid() && thisBlock.textList()) {
        d->builder->beginListItem();
        processBlockContents(it, thisBlock);
        d->builder->endListItem();

        if (!it.atEnd()) {
            ++it;
        }
        thisBlock = thisBlock.next();
        if (thisBlock.isValid()) {
            auto obj = thisBlock.document()->objectForFormat(thisBlock.blockFormat());
            auto group = qobject_cast<QTextBlockGroup *>(obj);
            if (group && group != textList) {
                auto pair = processBlockGroup(it, thisBlock, group);
                it = pair.first;
                thisBlock = pair.second;
            }
        }
    }
    d->builder->endList();
    return qMakePair(it, thisBlock);
}

QTextFrame::iterator MarkupGenerator::processBlockContents(QTextFrame::iterator it, const QTextBlock &block)
{
    Q_D(Internal::MarkupGenerator);

    auto blockFormat = block.blockFormat();
    auto blockAlignment = blockFormat.alignment();

    // TODO: decide when to use <h1> etc.

    if (blockFormat.hasProperty(QTextFormat::BlockTrailingHorizontalRulerWidth)) {
        d->builder->insertHorizontalRule();
        if (!it.atEnd()) {
            return ++it;
        }
        return it;
    }

    auto thisIt = block.begin();

    // The beginning is the end. This is an empty block. Insert a newline and move on.
    if (thisIt.atEnd()) {
        d->builder->addNewline();
        if (!it.atEnd()) {
            return ++it;
        }
        return it;
    }

    // Don't have p tags inside li tags.
    if (!block.textList()) {
        // Don't instruct builders to use margins. The rich text widget doesn't
        // have an action for them yet, so users can't edit them.
        // See bug http://bugs.kde.org/show_bug.cgi?id=160600
        d->builder->beginParagraph(
                    blockAlignment //,
                    // blockFormat.topMargin(),
                    // blockFormat.bottomMargin(),
                    // blockFormat.leftMargin(),
                    // blockFormat.rightMargin()
                    );
    }

    while (!thisIt.atEnd()) {
        thisIt = processFragment(thisIt, thisIt.fragment(), block.document());
    }

    // Don't have p tags inside li tags.
    if (!block.textList()) {
       d->builder->endParagraph();
    }

    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

void MarkupGenerator::processCustomFragment(const QTextFragment &fragment, const QTextDocument *doc)
{
    Q_UNUSED(fragment)
    Q_UNUSED(doc)
}

QTextBlock::iterator MarkupGenerator::processFragment(QTextBlock::iterator it, const QTextFragment &fragment, const QTextDocument *doc)
{
    Q_D(Internal::MarkupGenerator);

    auto charFormat = fragment.charFormat();
    if (charFormat.objectType() >= QTextFormat::UserObject) {
        processCustomFragment(fragment, doc);
        if (!it.atEnd()) {
            return ++it;
        }
        return it;
    }

    auto textObject = doc->objectForFormat(charFormat);
    if (textObject) {
        return processCharTextObject(it, fragment, textObject);
    }

    if (fragment.text().at(0).category() == QChar::Separator_Line) {
        d->builder->addNewline();

        if (!it.atEnd()) {
            return ++it;
        }
        return it;
    }

    // The order of closing and opening tags can determine whether generated
    // html is valid or not.
    // When processing a document with formatting which appears as
    // '<b><i>Some</i> formatted<b> text',
    // the correct generated output will contain
    // '<strong><em>Some</em> formatted<strong> text'.
    // However, processing text which appears as
    // '<i><b>Some</b> formatted<i> text' might be incorrectly rendered
    // as '<strong><em>Some</strong> formatted</em> text' if tags which start at
    // the same fragment are opened out of order.
    // Here, tags are not nested properly, and the html would
    // not be valid or render correctly by unforgiving parsers (like QTextEdit).
    // One solution is to make the order of opening tags dynamic. In the above
    // case, the em tag would be opened before the strong tag
    // '<em><strong>Some</strong> formatted</em> text'.
    // That would require knowledge of which tag is going to close first.
    // That might be possible by examining the 'next' QTextFragment while processing one.
    //
    // The other option is to do pessimistic closing of tags.
    // In the above case, this means that if a fragment has two or more formats
    // applied (bold and italic here),
    // and one of them is closed, then all tags should be closed first. They
    // will of course be reopened if necessary while processing the next fragment.
    // The above case would be rendered as
    // '<strong><em>Some</em></strong><em> formatted</em> text'.
    //
    // The first option is taken here, as the redundant opening and closing tags
    // in the second option didn't appeal.
    // See testDoubleStartDifferentFinish, testDoubleStartDifferentFinishReverseOrder

    processOpeningElements(it);

    // If a sequence such as '<br /><br />' is imported into a document with
    // setHtml, LineSeparator characters are inserted. Here I make sure to put them back.
    auto sl = fragment.text().split(QChar(QChar::LineSeparator));
    QStringListIterator i(sl);
    auto paraClosed = false;
    while (i.hasNext()) {
        d->builder->appendLiteralText(i.next());
        if (i.hasNext()) {
            if (i.peekNext().isEmpty()) {
                if (!paraClosed) {
                    d->builder->endParagraph();
                    paraClosed = true;
                }
                d->builder->addNewline();
            } else if (paraClosed) {
                d->builder->beginParagraph(/* blockAlignment */);
                paraClosed = false;
            }
        }
    }
    if (!it.atEnd()) {
        ++it;
    }

    processClosingElements(it);

    return it;
}

QTextBlock::iterator MarkupGenerator::processCharTextObject(QTextBlock::iterator it, const QTextFragment &fragment, QTextObject *textObject)
{
    auto fragmentFormat = fragment.charFormat();
    if (fragmentFormat.isImageFormat()) {
        auto imageFormat = fragmentFormat.toImageFormat();
        return processImage(it, imageFormat, textObject->document());
    }
    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

QTextBlock::iterator MarkupGenerator::processImage(QTextBlock::iterator it, const QTextImageFormat &imageFormat, QTextDocument *doc)
{
    Q_D(Internal::MarkupGenerator);
    Q_UNUSED(doc)

    // TODO: Close any open format elements?
    d->builder->insertImage(imageFormat.name(), imageFormat.width(), imageFormat.height());
    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

QTextFrame::iterator MarkupGenerator::processTable(QTextFrame::iterator it, QTextTable *table)
{
    Q_D(Internal::MarkupGenerator);

    auto format = table->format();

    auto colLengths = format.columnWidthConstraints();

    auto tableWidth = format.width();
    QString widthString;

    if (tableWidth.type() == QTextLength::PercentageLength) {
        widthString = QString("%1%").arg(tableWidth.rawValue());
    } else if (tableWidth.type() == QTextLength::FixedLength) {
        widthString = QString::number(tableWidth.rawValue());
    }

    d->builder->beginTable(format.cellPadding(), format.cellSpacing(), widthString);

    auto headerRowCount = format.headerRowCount();

    QList<QTextTableCell> alreadyProcessedCells;

    for (auto row = 0; row < table->rows(); ++row) {
      // Put a thead element around here somewhere?
      // if (row < headerRowCount)
      // {
      // beginTableHeader();
      // }

      d->builder->beginTableRow();

      // Header attribute should really be on cells, not determined by number
      // of
      // rows.
      // http://www.webdesignfromscratch.com/html-tables.cfm

      for (auto column = 0; column < table->columns(); ++column) {
          auto tableCell = table->cellAt(row, column);
          auto columnSpan = tableCell.columnSpan();
          auto rowSpan = tableCell.rowSpan();
          if ((rowSpan > 1) || (columnSpan > 1)) {
              if (alreadyProcessedCells.contains(tableCell)) {
                  // Already processed this cell. Move on.
                  continue;
              } else {
                  alreadyProcessedCells.append(tableCell);
              }
          }

          auto cellWidth = colLengths.at(column);
          QString cellWidthString;
          if (cellWidth.type() == QTextLength::PercentageLength) {
              cellWidthString = QString("%1%").arg(cellWidth.rawValue());
          } else if (cellWidth.type() == QTextLength::FixedLength) {
              cellWidthString = QString::number(cellWidth.rawValue());
          }

          // TODO: Use THEAD instead
          if (row < headerRowCount) {
              d->builder->beginTableHeaderCell(cellWidthString, columnSpan, rowSpan);
          } else {
              d->builder->beginTableCell(cellWidthString, columnSpan, rowSpan);
          }

          processTableCell(tableCell, table);

          if (row < headerRowCount) {
              d->builder->endTableHeaderCell();
          } else {
              d->builder->endTableCell();
          }
      }
      d->builder->endTableRow();
    }
    d->builder->endTable();

    if (!it.atEnd()) {
        return ++it;
    }
    return it;
}

void MarkupGenerator::processTableCell(const QTextTableCell &tableCell, QTextTable *table)
{
    Q_UNUSED(table)
    processDocumentContents(tableCell.begin(), tableCell.end());
}

void MarkupGenerator::processDocumentContents(QTextFrame::iterator begin, QTextFrame::iterator end)
{
    while (!begin.atEnd() && begin != end) {
        QTextFrame *frame = begin.currentFrame();
        if (frame) {
            QTextTable *table = qobject_cast<QTextTable *>(frame);
            if (table) {
                begin = processTable(begin, table);
            } else {
                begin = processFrame(begin, frame);
            }
        } else {
            QTextBlock &block = begin.currentBlock();
            Q_ASSERT(block.isValid());
            begin = processBlock(begin, block);
        }
    }
}

MarkupGenerator::IteratorAndBlock MarkupGenerator::skipBlockGroup(QTextFrame::iterator it, const QTextBlock &block, QTextBlockGroup *blockGroup)
{
    auto thisBlock = block;
    auto lastBlock = block;
    auto lastIt = it;
    auto obj = thisBlock.document()->objectForFormat(thisBlock.blockFormat());
    QTextBlockGroup *nextGroup;

    if (!obj) {
        return qMakePair(lastIt, lastBlock);
    }

    auto group = qobject_cast<QTextBlockGroup *>(obj);
    if (!group) {
        return qMakePair(lastIt, lastBlock);
    }

    while (thisBlock.isValid()) {
      if (!group) {
          break;
      }

      thisBlock = thisBlock.next();
      if (!it.atEnd()) {
          ++it;
      }

      obj = thisBlock.document()->objectForFormat(thisBlock.blockFormat());
      if (obj) {
          continue;
      }

      nextGroup = qobject_cast<QTextBlockGroup *>(obj);

      if (group == blockGroup || !nextGroup) {
          lastBlock = thisBlock;
          lastIt = it;
      }
      group = nextGroup;
    }
    return qMakePair(lastIt, lastBlock);
}

ElementList MarkupGenerator::sortOpeningOrder(ElementSet openingTags, QTextBlock::iterator it) const
{
    ElementList sortedOpenedElements;

    // This is an insertion sort in a way. elements in openingOrder are assumed
    // to be out of order.
    // The rest of the block is traversed until there are no more elements to
    // sort, or the end is reached.
    while (openingTags.size() != 0) {
        if (!it.atEnd()) {
            it++;

            if (!it.atEnd()) {
                // Because I've iterated, this returns the elements that will
                // be closed by the next fragment.
                auto elementsToClose = getElementsToClose(it);

                // The exact order these are opened in is irrelevant, as all
                // will be closed on the same block.
                for (MarkupElement tag : elementsToClose) {
                    if (openingTags.remove(tag)) {
                        sortedOpenedElements.prepend(tag);
                    }
                }
            }
        } else {
            // End of block. Need to close all open elements.
            // Order irrelevant in this case.
            for (MarkupElement tag : openingTags) {
                sortedOpenedElements.prepend(tag);
            }
            break;
        }
    }
    return sortedOpenedElements;
}

void MarkupGenerator::processClosingElements(QTextBlock::iterator it)
{
    Q_D(Internal::MarkupGenerator);

    // The order of closing elements is determined by the order they were opened in.
    // The order of opened elements is in the openElements member list.

    if (d->openedElements.isEmpty()) {
        return;
    }

    auto elementsToClose = getElementsToClose(it);

    int previousSize;
    auto remainingSize = elementsToClose.size();
    while (!elementsToClose.isEmpty()) {
        auto tag = d->openedElements.last();
        if (elementsToClose.contains(tag)) {
            switch (tag) {
            case MarkupElement::Strong:
                d->builder->endStrong();
                break;
            case MarkupElement::Emph:
                d->builder->endEmphasised();
                break;
            case MarkupElement::Underline:
                d->builder->endUnderline();
                break;
            case MarkupElement::StrikeOut:
                d->builder->endStrikeout();
                break;
            case MarkupElement::SpanFontPointSize:
                d->builder->endFontPointSize();
                break;
            case MarkupElement::SpanFontFamily:
                d->builder->endFontFamily();
                break;
            case MarkupElement::SpanBackground:
                d->builder->endBackground();
                break;
            case MarkupElement::SpanForeground:
                d->builder->endForeground();
                break;
            case MarkupElement::Anchor:
                d->builder->endAnchor();
                break;
            case MarkupElement::SubScript:
                d->builder->endSubscript();
                break;
            case MarkupElement::SuperScript:
                d->builder->endSuperscript();
                break;
            default:
              break;
            }
            d->openedElements.removeLast();
            elementsToClose.remove(tag);
        }
        previousSize = remainingSize;
        remainingSize = elementsToClose.size();

        if (previousSize == remainingSize) {
            // Iterated once through without closing any tags.
            // This means that there's overlap in the tags, such as
            // 'text with <b>some <i>formatting</i></b><i> tags</i>'
            // The top element in openElements must be a blocker, so close it on
            // next iteration.
            elementsToClose.insert(d->openedElements.last());
        }
    }
}

void MarkupGenerator::processOpeningElements(QTextBlock::iterator it)
{
    Q_D(Internal::MarkupGenerator);
    auto fragment = it.fragment();

    if (!fragment.isValid()) {
        return;
    }

    auto fragmentFormat = fragment.charFormat();
    auto elementsToOpenList = getElementsToOpen(it);

    for (MarkupElement tag : elementsToOpenList) {
        switch (tag) {
        case MarkupElement::Strong:
            d->builder->beginStrong();
            break;
        case MarkupElement::Emph:
            d->builder->beginEmphasised();
            break;
        case MarkupElement::Underline:
            d->builder->beginUnderline();
            break;
        case MarkupElement::StrikeOut:
            d->builder->beginStrikeout();
            break;
        case MarkupElement::SpanFontPointSize:
            d->builder->beginFontPointSize(fragmentFormat.font().pointSize());
            d->openedFontPointSize = fragmentFormat.font().pointSize();
            break;
        case MarkupElement::SpanFontFamily:
            d->builder->beginFontFamily(fragmentFormat.fontFamily());
            d->openedFontFamily = fragmentFormat.fontFamily();
            break;
        case MarkupElement::SpanBackground:
            d->builder->beginBackground(fragmentFormat.background());
            d->openedBackground = fragmentFormat.background();
            break;
        case MarkupElement::SpanForeground:
            d->builder->beginForeground(fragmentFormat.foreground());
            d->openedForeground = fragmentFormat.foreground();
            break;
        case MarkupElement::Anchor: {
            // TODO: Multiple anchor names here.
            auto anchorNames = fragmentFormat.anchorNames();
            if (!anchorNames.isEmpty()) {
                while (!anchorNames.isEmpty()) {
                    auto n = anchorNames.last();
                    anchorNames.removeLast();
                    if (anchorNames.isEmpty()) {
                        // Doesn't matter if anchorHref is empty.
                        d->builder->beginAnchor(fragmentFormat.anchorHref(), n);
                        break;
                    } else {
                        // Empty <a> tags allow multiple names for the same section.
                        d->builder->beginAnchor(QString(), n);
                        d->builder->endAnchor();
                    }
                }
            } else {
                d->builder->beginAnchor(fragmentFormat.anchorHref());
            }
            d->openedAnchorHref = fragmentFormat.anchorHref();
            break;
        }
        case MarkupElement::SuperScript:
            d->builder->beginSuperscript();
            break;
        case MarkupElement::SubScript:
            d->builder->beginSubscript();
            break;
        default:
            break;
        }
        d->openedElements.append(tag);
        d->elementsToOpen.remove(tag);
    }
}

ElementSet MarkupGenerator::getElementsToClose(QTextBlock::iterator it) const
{
    Q_D(const Internal::MarkupGenerator);
    ElementSet closedElements;

    if (it.atEnd()) {
        // End of block?. Close all open tags.
        auto elementsToClose = d->openedElements.toSet();
        return elementsToClose.unite(d->elementsToOpen);
    }

    auto fragment = it.fragment();
    if (!fragment.isValid()) {
        return closedElements;
    }

    auto fragmentFormat = fragment.charFormat();

    auto fontWeight = fragmentFormat.fontWeight();
    auto fontItalic = fragmentFormat.fontItalic();
    auto fontUnderline = fragmentFormat.fontUnderline();
    auto fontStrikeout = fragmentFormat.fontStrikeOut();

    auto fontForeground = fragmentFormat.foreground();
    auto fontBackground = fragmentFormat.background();

    auto fontFamily = fragmentFormat.fontFamily();
    auto fontPointSize = fragmentFormat.font().pointSize();
    auto anchorHref = fragmentFormat.anchorHref();

    auto vAlign = fragmentFormat.verticalAlignment();
    auto superscript = (vAlign == QTextCharFormat::AlignSuperScript);
    auto subscript = (vAlign == QTextCharFormat::AlignSubScript);

    if (!fontStrikeout
            && (d->openedElements.contains(MarkupElement::StrikeOut) || d->elementsToOpen.contains(MarkupElement::StrikeOut))) {
        closedElements.insert(MarkupElement::StrikeOut);
    }

    if (!fontUnderline
            && (d->openedElements.contains(MarkupElement::Underline) || d->elementsToOpen.contains(MarkupElement::Underline))
            && !(d->openedElements.contains(MarkupElement::Anchor) || d->elementsToOpen.contains(MarkupElement::Anchor))) {
        closedElements.insert(MarkupElement::Underline);
    }

    if (!fontItalic
            && (d->openedElements.contains(MarkupElement::Emph) || d->elementsToOpen.contains(MarkupElement::Emph))) {
        closedElements.insert(MarkupElement::Emph);
    }

    if (fontWeight != QFont::Bold
            && (d->openedElements.contains(MarkupElement::Strong) || d->elementsToOpen.contains(MarkupElement::Strong))) {
        closedElements.insert(MarkupElement::Strong);
    }

    if ((d->openedElements.contains(MarkupElement::SpanFontPointSize) || d->elementsToOpen.contains(MarkupElement::SpanFontPointSize))
            && (d->openedFontPointSize != fontPointSize)) {
        closedElements.insert(MarkupElement::SpanFontPointSize);
    }

    if ((d->openedElements.contains(MarkupElement::SpanFontFamily) || d->elementsToOpen.contains(MarkupElement::SpanFontFamily))
            && (d->openedFontFamily != fontFamily)) {
        closedElements.insert(MarkupElement::SpanFontFamily);
    }

    if ((d->openedElements.contains(MarkupElement::SpanBackground) && (d->openedBackground != fontBackground))
            || (d->elementsToOpen.contains(MarkupElement::SpanBackground) && (d->backgroundToOpen != fontBackground))) {
        closedElements.insert(MarkupElement::SpanBackground);
    }

    if ((d->openedElements.contains(MarkupElement::SpanForeground) && (d->openedForeground != fontForeground))
            || (d->elementsToOpen.contains(MarkupElement::SpanForeground) && (d->foregroundToOpen != fontForeground))) {
        closedElements.insert(MarkupElement::SpanForeground);
    }

    if ((d->openedElements.contains(MarkupElement::Anchor) && (d->openedAnchorHref != anchorHref))
            || (d->elementsToOpen.contains(MarkupElement::Anchor) && (d->anchorHrefToOpen != anchorHref))) {
        closedElements.insert(MarkupElement::Anchor);
    }

    if (!subscript
            && (d->openedElements.contains(MarkupElement::SubScript) || d->elementsToOpen.contains(MarkupElement::SubScript))) {
        closedElements.insert(MarkupElement::SubScript);
    }

    if (!superscript
            && (d->openedElements.contains(MarkupElement::SuperScript) || d->elementsToOpen.contains(MarkupElement::SuperScript))) {
        closedElements.insert(MarkupElement::SuperScript);
    }
    return closedElements;
}

ElementList MarkupGenerator::getElementsToOpen(QTextBlock::iterator it)
{
    Q_D(Internal::MarkupGenerator);

    auto fragment = it.fragment();
    if (!fragment.isValid()) {
        return ElementList();
    }
    auto fragmentFormat = fragment.charFormat();

    auto fontWeight = fragmentFormat.fontWeight();
    auto fontItalic = fragmentFormat.fontItalic();
    auto fontUnderline = fragmentFormat.fontUnderline();
    auto fontStrikeout = fragmentFormat.fontStrikeOut();

    auto fontForeground = fragmentFormat.foreground();
    auto fontBackground = fragmentFormat.background();

    auto fontFamily = fragmentFormat.fontFamily();
    auto fontPointSize = fragmentFormat.font().pointSize();
    auto anchorHref = fragmentFormat.anchorHref();

    auto vAlign = fragmentFormat.verticalAlignment();
    auto superscript = (vAlign == QTextCharFormat::AlignSuperScript);
    auto subscript = (vAlign == QTextCharFormat::AlignSubScript);

    if (superscript && !(d->openedElements.contains(MarkupElement::SuperScript))) {
        d->elementsToOpen.insert(MarkupElement::SuperScript);
    }

    if (subscript && !(d->openedElements.contains(MarkupElement::SubScript))) {
        d->elementsToOpen.insert(MarkupElement::SubScript);
    }

    if (!anchorHref.isEmpty()
            && !(d->openedElements.contains(MarkupElement::Anchor))
            && (d->openedAnchorHref != anchorHref)) {
        d->elementsToOpen.insert(MarkupElement::Anchor);
        d->anchorHrefToOpen = anchorHref;
    }

    if (fontForeground != Qt::NoBrush && !(d->openedElements.contains(MarkupElement::SpanForeground)) // Can only open one foreground element at a time.
            && (fontForeground != d->openedForeground)
            && !((d->openedElements.contains(MarkupElement::Anchor) // Links can't have a foreground color.
                    || d->elementsToOpen.contains(MarkupElement::Anchor)))) {
        d->elementsToOpen.insert(MarkupElement::SpanForeground);
        d->foregroundToOpen = fontForeground;
    }

    if (fontBackground != Qt::NoBrush
            && !(d->openedElements.contains(MarkupElement::SpanBackground))
            && (fontBackground != d->openedBackground)) {
        d->elementsToOpen.insert(MarkupElement::SpanBackground);
        d->backgroundToOpen = fontBackground;
    }

    if (!fontFamily.isEmpty() && !(d->openedElements.contains(MarkupElement::SpanFontFamily))
            && (fontFamily != d->openedFontFamily)) {
        d->elementsToOpen.insert(MarkupElement::SpanFontFamily);
        d->fontFamilyToOpen = fontFamily;
    }

    if ((QTextCharFormat().font().pointSize() != fontPointSize) // Different from the default.
            && !(d->openedElements.contains(MarkupElement::SpanFontPointSize))
            && (fontPointSize != d->openedFontPointSize)) {
        d->elementsToOpen.insert(MarkupElement::SpanFontPointSize);
        d->fontPointSizeToOpen = fontPointSize;
    }

    //   Only open a new bold tag if one is not already open.
    //   eg, <b>some <i>mixed</i> format</b> should be as is, rather than
    //   <b>some </b><b><i>mixed</i></b><b> format</b>

    if (fontWeight == QFont::Bold && !(d->openedElements.contains(MarkupElement::Strong))) {
        d->elementsToOpen.insert(MarkupElement::Strong);
    }

    if (fontItalic && !(d->openedElements.contains(MarkupElement::Emph))) {
        d->elementsToOpen.insert(MarkupElement::Emph);
    }

    if (fontUnderline
            && !(d->openedElements.contains(MarkupElement::Underline))
            && !(d->openedElements.contains(MarkupElement::Anchor)
                 || d->elementsToOpen.contains(MarkupElement::Anchor))) { // Can't change the underline state of a link.
        d->elementsToOpen.insert(MarkupElement::Underline);
    }

    if (fontStrikeout && !(d->openedElements.contains(MarkupElement::StrikeOut))) {
        d->elementsToOpen.insert(MarkupElement::StrikeOut);
    }

    if (d->elementsToOpen.size() <= 1) {
      return d->elementsToOpen.toList();
    }
    return sortOpeningOrder(d->elementsToOpen, it);
}

} // end of namespace Core

#include "moc_markupgenerator.cpp"
