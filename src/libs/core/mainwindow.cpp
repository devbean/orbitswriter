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

#include "appcontext.h"
#include "document/markupbuilder.h"
#include "mainwindow.h"
#include "previewer.h"
#include "sourceeditor.h"
#include "visualeditor.h"

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QLineEdit>
#include <QMenuBar>
#include <QTabWidget>
#include <QToolBar>
#include <QVBoxLayout>

namespace Core
{

namespace Internal
{

//---------- MainWindowPrivate ----------//

MainWindowPrivate::MainWindowPrivate(MainWindow *win)
    : q_ptr(win)
{
    initActions();
    installMenuBar();
    installToolBar();
    installEditorPane();
}

void MainWindowPrivate::initActions()
{
    Q_Q(MainWindow);

    newAction = new QAction(q);
    newAction->setText(tr("New"));
    newAction->setIcon(QIcon(":/icon/new"));
    newAction->setShortcut(QKeySequence::New);

    openAction = new QAction(q);
    openAction->setText(tr("Open"));
    openAction->setIcon(QIcon(":/icon/open"));
    openAction->setShortcut(QKeySequence::Open);

    saveAction = new QAction(q);
    saveAction->setText(tr("Save"));
    saveAction->setIcon(QIcon(":/icon/save"));
    saveAction->setShortcut(QKeySequence::Save);

    exitAction = new QAction(q);
    exitAction->setText(tr("Exit"));
    exitAction->setShortcut(QKeySequence::Quit);

    cutAction = new QAction(q);
    cutAction->setText(tr("Cut"));
    cutAction->setIcon(QIcon(":/icon/cut"));
    cutAction->setShortcut(QKeySequence::Cut);

    copyAction = new QAction(q);
    copyAction->setText(tr("Copy"));
    copyAction->setIcon(QIcon(":/icon/copy"));
    copyAction->setShortcut(QKeySequence::Copy);

    pasteAction = new QAction(q);
    pasteAction->setText(tr("Paste"));
    pasteAction->setIcon(QIcon(":/icon/paste"));
    pasteAction->setShortcut(QKeySequence::Paste);

    settingsAction = new QAction(q);
    settingsAction->setText(tr("Settings"));
    settingsAction->setIcon(QIcon(":/icon/settings"));

    helpAction = new QAction(q);
    helpAction->setText(tr("Help"));
    helpAction->setIcon(QIcon(":/icon/help"));
    helpAction->setShortcut(QKeySequence::HelpContents);

    aboutAction = new QAction(q);
    aboutAction->setText(tr("About"));

    alignJustifyAction = new QAction(q);
    alignJustifyAction->setText(tr("Align Justify"));
    alignJustifyAction->setIcon(QIcon(":/icon/align_justify"));

    alignCenterAction = new QAction(q);
    alignCenterAction->setText(tr("Align Center"));
    alignCenterAction->setIcon(QIcon(":/icon/align_center"));

    alignLeftAction = new QAction(q);
    alignLeftAction->setText(tr("Align Left"));
    alignLeftAction->setIcon(QIcon(":/icon/align_left"));

    alignRightAction = new QAction(q);
    alignRightAction->setText(tr("Align Right"));
    alignRightAction->setIcon(QIcon(":/icon/align_right"));

    fontBoldAction = new QAction(q);
    fontBoldAction->setText(tr("Bold"));
    fontBoldAction->setIcon(QIcon(":/icon/font_bold"));
    fontBoldAction->setShortcut(QKeySequence::Bold);

    fontItalicAction = new QAction(q);
    fontItalicAction->setText(tr("Italic"));
    fontItalicAction->setIcon(QIcon(":/icon/font_italic"));
    fontItalicAction->setShortcut(QKeySequence::Italic);

    fontUnderlineAction = new QAction(q);
    fontUnderlineAction->setText(tr("Underline"));
    fontUnderlineAction->setIcon(QIcon(":/icon/font_underline"));
    fontUnderlineAction->setShortcut(QKeySequence::Underline);

    fontStrikeoutAction = new QAction(q);
    fontStrikeoutAction->setText(tr("Strike Out"));
    fontStrikeoutAction->setIcon(QIcon(":/icon/font_strikeout"));

    fontColorAction = new QAction(q);
    fontColorAction->setText(tr("Text Color"));
    fontColorAction->setIcon(QIcon(":/icon/font_color"));

    fontBackgroundColorAction = new QAction(q);
    fontBackgroundColorAction->setText(tr("Text Background Color"));
    fontBackgroundColorAction->setIcon(QIcon(":/icon/font_background_color"));

    bulletListAction = new QAction(q);
    bulletListAction->setText(tr("Bullet List"));
    bulletListAction->setIcon(QIcon(":/icon/ul"));

    numberingListAction = new QAction(q);
    numberingListAction->setText(tr("Numbering List"));
    numberingListAction->setIcon(QIcon(":/icon/ol"));
}

void MainWindowPrivate::installMenuBar()
{
    Q_Q(MainWindow);

    QMenuBar *menuBar = new QMenuBar;
    q->setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    QMenu *editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    QMenu *toolsMenu = menuBar->addMenu(tr("&Tools"));
    toolsMenu->addAction(settingsAction);

    QMenu *helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
}

void MainWindowPrivate::installToolBar()
{
    Q_Q(MainWindow);

    QToolBar *mainToolBar = new QToolBar(q);
    mainToolBar->setWindowTitle(tr("Main Tool Bar"));
    q->addToolBar(Qt::TopToolBarArea, mainToolBar);

    mainToolBar->addAction(newAction);
    mainToolBar->addAction(openAction);
    mainToolBar->addAction(saveAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(cutAction);
    mainToolBar->addAction(copyAction);
    mainToolBar->addAction(pasteAction);
    mainToolBar->addSeparator();
    mainToolBar->addAction(settingsAction);

    QToolBar *editToolBar = new QToolBar(q);
    editToolBar->setWindowTitle(tr("Edit Tool Bar"));
    q->addToolBar(Qt::TopToolBarArea, editToolBar);

    editToolBar->addAction(fontBoldAction);
    editToolBar->addAction(fontItalicAction);
    editToolBar->addAction(fontStrikeoutAction);
    editToolBar->addAction(fontUnderlineAction);
    editToolBar->addSeparator();
    editToolBar->addAction(fontColorAction);
    editToolBar->addAction(fontBackgroundColorAction);
    editToolBar->addSeparator();
    editToolBar->addAction(alignJustifyAction);
    if (QApplication::isRightToLeft()) {
        editToolBar->addAction(alignRightAction);
        editToolBar->addAction(alignCenterAction);
        editToolBar->addAction(alignLeftAction);
    } else {
        editToolBar->addAction(alignLeftAction);
        editToolBar->addAction(alignCenterAction);
        editToolBar->addAction(alignRightAction);
    }
    editToolBar->addSeparator();
    editToolBar->addAction(bulletListAction);
    editToolBar->addAction(numberingListAction);
}

void MainWindowPrivate::installEditorPane()
{
    Q_Q(MainWindow);

    QWidget *editorPane = new QWidget(q);
    q->setCentralWidget(editorPane);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLineEdit *titleEdit = new QLineEdit(editorPane);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleEdit->setFont(titleFont);
    titleEdit->setStyleSheet("border: 1px solid gray; padding:0 8px;");
    mainLayout->addWidget(titleEdit);

    editorTab = new QTabWidget(editorPane);
    visualEditor = new VisualEditor(editorTab);
    editorTab->addTab(visualEditor, tr("Visual"));

    previewer = new Previewer(editorTab);
    editorTab->addTab(previewer, tr("Preview"));

    mainLayout->addWidget(editorTab);

    editorPane->setLayout(mainLayout);

    connect(editorTab, &QTabWidget::currentChanged, [&] (int) {
        SourceEditor *srcEditor = qobject_cast<SourceEditor *>(editorTab->currentWidget());
        if (srcEditor) {
            srcEditor->updateSource(visualEditor->document());
        }
    });
}

void MainWindowPrivate::appendSourceEditor(MarkupBuilder *builder)
{
    SourceEditor *sourceEditor = new SourceEditor(builder, editorTab);
    editorTab->addTab(sourceEditor, builder->markupName());
}

} // end of namespace Core::Internal

//---------- MainWindow ----------//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      d_ptr(new Internal::MainWindowPrivate(this))
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
//    if (maybeSave()) {
        AppContext::instance()->shutdown();
        event->accept();
//    } else {
//        event->ignore();
//    }
}

} // end of namesapce Core

#include "moc_mainwindow.cpp"
