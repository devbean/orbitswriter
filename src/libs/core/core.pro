#-------------------------------------------------
#
# OrbitsWriter - an Offline Blog Writer
#
# Copyright (C) 2016 devbean@galaxyworld.org
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#-------------------------------------------------

TARGET   = core
DEFINES += CORE_LIBRARY

include(../library.pri)

SOURCES += \
    mainwindow.cpp \
    appcontext.cpp \
    visualeditor.cpp \
    sourceeditor.cpp \
    previewer.cpp \
    document/markupbuilder.cpp \
    document/markupgenerator.cpp \
    pluginmanager.cpp \
    plugin.cpp

HEADERS  += \
    mainwindow.h \
    mainwindow_p.h \
    appcontext.h \
    appcontext_p.h \
    core_global.h \
    appcontextlistener.h \
    visualeditor.h \
    sourceeditor.h \
    previewer.h \
    document/markupbuilder.h \
    document/markupgenerator.h \
    document/markupgenerator_p.h \
    document/markupelement.h \
    pluginmanager.h \
    pluginmanager_p.h \
    plugin.h \
    publisher.h

RESOURCES += \
    core.qrc
