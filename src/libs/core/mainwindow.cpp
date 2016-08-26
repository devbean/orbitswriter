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
    mainToolBar->setMovable(false);
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
