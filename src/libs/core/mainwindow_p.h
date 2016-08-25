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

#ifndef MAINWINDOW_P_H
#define MAINWINDOW_P_H

#include <QObject>

class QAction;
class QTabWidget;

namespace Core
{

class ActionManager;
class MainWindow;
class MarkupBuilder;
class Previewer;
class SourceEditor;
class VisualEditor;

namespace Internal
{

class AppContextPrivate;

class MainWindowPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindowPrivate)
    Q_DECLARE_PUBLIC(Core::MainWindow)
    MainWindow * const q_ptr;
    friend class AppContextPrivate;

    MainWindowPrivate(MainWindow *win);

    void initActions();
    void installMenuBar();
    void installToolBar();
    void installEditorPane();

    void appendSourceEditor(MarkupBuilder *builder);

    ActionManager *actionManager;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    QAction *settingsAction;

    QAction *helpAction;
    QAction *aboutAction;

    QTabWidget *editorTab;
    Previewer *previewer;
    VisualEditor *visualEditor;
}; // end of class Core::Internal::MainWindowPrivate

} // end of namespace Core::Internal

} // end of namespace Core

#endif // MAINWINDOW_P_H
