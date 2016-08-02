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

#ifndef MARKUPGENERATOR_H
#define MARKUPGENERATOR_H

#include "markupgenerator_p.h"
#include "markupelement.h"

#include <QObject>
#include <QTextFrame>
#include <QTextTableCell>

class QTextDocument;

namespace Core
{

class MarkupBuilder;

class MarkupGenerator : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(Internal::MarkupGenerator)
    QScopedPointer<Internal::MarkupGeneratorPrivate> const d_ptr;

public:
    typedef QPair<QTextFrame::iterator, QTextBlock> IteratorAndBlock;

    /*!
     * \brief Constructs a markup generator.
     *
     * \param builder Markup builder to be used to generate the markup text.
     * This builder will be deleted by the generator.
     * \param parent Object parent of this generator.
     */
    MarkupGenerator(MarkupBuilder *builder, QObject *parent = 0);

    /*!
     * Process the document to generate the markup.
     *
     * \param doc The text document to be processed.
     */
    virtual void processDocument(QTextDocument *doc);

    /*!
     * Process a text \a frame.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     */
    virtual QTextFrame::iterator processFrame(QTextFrame::iterator it,
                                              QTextFrame *frame);

    /*!
     * Process a text \a block.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     *
     * This method does not process the contents of the \a block, but uses the
     * processBlockContents method to do so.
     */
    virtual QTextFrame::iterator processBlock(QTextFrame::iterator it,
                                              const QTextBlock &block);

    /*!
     * Process a text \a object.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     *
     * The block \a block is the container of the \p textObject.
     */
    virtual QTextFrame::iterator processObject(QTextFrame::iterator it,
                                               const QTextBlock &block,
                                               QTextObject *textObject);

    /*!
     * Process a block group \a textBlockGroup.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     *
     * The block \a block is the first block in the \a textBlockGroup.
     */
    virtual IteratorAndBlock processBlockGroup(QTextFrame::iterator it,
                                               const QTextBlock &block,
                                               QTextBlockGroup *textBlockGroup);

    /*!
     * Process a list \a textList.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     *
     * The block \a block is the first block in the \a textList.
     */
    virtual IteratorAndBlock processList(QTextFrame::iterator it,
                                         const QTextBlock &block,
                                         QTextList *textList);

    /*!
     * Process the contents of a block \a block.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     */
    virtual QTextFrame::iterator processBlockContents(QTextFrame::iterator it,
                                                      const QTextBlock &block);

    /*!
     * Process a \a fragemnt with custom type.
     *
     * \a doc is the document the fragment is in.
     */
    virtual void processCustomFragment(const QTextFragment &fragment,
                                       QTextDocument const *doc);

    /*!
     * Process the contents of a fragment \a fragment.
     *
     * If calling this method directly, an invalid QTextBlock::iterator may be used.
     * \a doc is the document the fragment is in.
     */
    virtual QTextBlock::iterator processFragment(QTextBlock::iterator it,
                                                 const QTextFragment &fragment,
                                                 QTextDocument const *doc);

    /*!
     * Process the contents of a text object \a textObject.
     *
     * The \a textObject is represented in the QTextDocument with the \a fragment.
     *
     * If calling this method directly, an invalid QTextBlock::iterator may be used.
     */
    virtual QTextBlock::iterator processCharTextObject(QTextBlock::iterator it,
                                                       const QTextFragment &fragment,
                                                       QTextObject *textObject);

    /*!
     * Process an image represented by the \a imageFormat.
     *
     * If calling this method directly, an invalid QTextBlock::iterator may be used.
     * \a doc is the document the fragment is in.
     */
    virtual QTextBlock::iterator processImage(QTextBlock::iterator it,
                                              const QTextImageFormat &imageFormat,
                                              QTextDocument *doc);

    /*!
     * Process the contents of a \a table.
     *
     * If calling this method directly, an invalid QTextFrame::iterator may be used.
     */
    virtual QTextFrame::iterator processTable(QTextFrame::iterator it,
                                              QTextTable *table);

    /*!
     * Process the contents of a table cell \a tableCell.
     *
     * The \a tableCell is in the \a table.
     */
    virtual void processTableCell(const QTextTableCell &tableCell,
                                  QTextTable *table);

protected:
    /*!
     * Process the document between \a begin and \a end.
     */
    void processDocumentContents(QTextFrame::iterator begin,
                                 QTextFrame::iterator end);

    /*!
     * Iterates the iterator \a it to the first block after \a blockGroup.
     *
     * \a block is any block in the \a blockGroup.
     *
     * \return The iterator pointing after the end of \a blockGroup
     * and the first block after \a blockGroup.
     */
    IteratorAndBlock skipBlockGroup(QTextFrame::iterator it,
                                    const QTextBlock &block,
                                    QTextBlockGroup *blockGroup);

    /*!
     * Returns a list of tags contained in \a openingTags sorted so they can be
     * opened in order and will be closed in the correct order.
     *
     * \a openingTags should be a set of tags opened at the fragment pointed to
     * by \a it.
     */
    ElementList sortOpeningOrder(ElementSet openingTags,
                                 QTextBlock::iterator it) const;

    /*!
     * Process to close the appropriate tags at the position of \a it.
     */
    virtual void processClosingElements(QTextBlock::iterator it);

    /*!
     * Process to open the appropriate tags at the position of \a it.
     */
    virtual void processOpeningElements(QTextBlock::iterator it);

    /*!
     * Returns the tags that should be closed at the position of \a it.
     */
    virtual ElementSet getElementsToClose(QTextBlock::iterator it) const;

    /*!
     * Returns the tags that should be opened at the position of \a it.
     */
    virtual ElementList getElementsToOpen(QTextBlock::iterator it);
}; // end of class Core::MarkupGenerator

} // end of namespace Core

#endif // MARKUPGENERATOR_H
