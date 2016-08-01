#-------------------------------------------------
#
# OrbitsWriter - an Offline Blog Writer
#
# Copyright (C) 2013 devbean@galaxyworld.org
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

include(../../global.pri)

# use precompiled header for libraries by default
# !isEmpty(PRECOMPILED_HEADER):PRECOMPILED_HEADER = $$PWD/shared/application_pch.h

win32 {
    DLLDESTDIR = $$DIST_PATH
}

DESTDIR = $$APPLICATION_LIBRARY_PATH

#osx {
#    QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/Frameworks/
#    QMAKE_LFLAGS += -compatibility_version $$QTCREATOR_COMPAT_VERSION
#}
include(../rpath.pri)

TARGET = $$libraryTargetName($$TARGET)

TEMPLATE = lib
CONFIG  += shared dll

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

#win32 {
#    dlltarget.path = $$INSTALL_BIN_PATH
#    INSTALLS += dlltarget
#} else {
#    target.path = $$INSTALL_LIBRARY_PATH
#    INSTALLS += target
#}

!macx {
    win32 {
        target.path = /output
    } else {
        target.path = /$$APPLICATION_LIBRARY_BASENAME/OrbitsWriter
    }
    INSTALLS += target
}
