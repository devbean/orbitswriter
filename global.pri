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

!isEmpty(ORBITSWRITER_PRI_INCLUDED): error("orbitswriter.pri already included")
ORBITSWRITER_PRI_INCLUDED = 1

APPLICATION_NAME     = OrbitsWriter
APPLICATION_VERSION  = 1.0.0
APPLICATION_REVISION = $$system(git log -n 1 --pretty="format:%h")
VERSION              = $$APPLICATION_VERSION

# enable c++11
CONFIG += c++11

defineReplace(libraryTargetName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}

defineReplace(libraryName) {
   RET = $$libraryTargetName($$1)
   win32 {
      VERSION_LIST = $$split(APPLICATION_VERSION, .)
      RET = $$RET$$first(VERSION_LIST)
   }
   return($$RET)
}

isEmpty(LIBRARY_BASENAME) {
    LIBRARY_BASENAME = libs
}

SOURCE_TREE = $$PWD
isEmpty(BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    BUILD_TREE = $$clean_path($$OUT_PWD)
    BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

osx {
} else {
    contains(TEMPLATE, vc.*):vcproj = 1
    APPLICATION_TARGET           = OrbitsWriter

    # target output path if not set manually
    isEmpty(DIST_PATH): DIST_PATH = $$BUILD_TREE/dist

    APPLICATION_LIBRARY_PATH     = $$BUILD_TREE/$$LIBRARY_BASENAME
    APPLICATION_PLUGINS_PATH     = $$BUILD_TREE/plugins
    #APP_DATA_PATH               = $$APP_BUILD_TREE/share/OrbitsWriter
    #APP_DOC_PATH                = $$APP_BUILD_TREE/share/doc/OrbitsWriter
    APPLICATION_BIN_PATH         = $$DIST_PATH

    win32: \
        APPLICATION_LIBEXEC_PATH = $$DIST_PATH/bin
    else: \
        APPLICATION_LIBEXEC_PATH = $$DIST_PATH/libexec/orbitswriter
    !isEqual(SOURCE_TREE, $$DIST_PATH):copydata = 1
}

INCLUDEPATH += \
    $$BUILD_TREE/src/app \ # for <version.h>
    $$SOURCE_TREE/src/libs \
    $$SOURCE_TREE/src/plugins \
    $$SOURCE_TREE/src/includes

CONFIG += depend_includepath

LIBS += -L$$APPLICATION_LIBRARY_PATH

!isEmpty(vcproj) {
    DEFINES += LIBRARY_BASENAME=\"$$LIBRARY_BASENAME\"
} else {
    DEFINES += LIBRARY_BASENAME=\\\"$$LIBRARY_BASENAME\\\"
}

DEFINES += QT_NO_CAST_TO_ASCII QT_RESTRICTED_CAST_FROM_ASCII

unix {
    CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
    CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

    CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
    CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

    RCC_DIR = $${OUT_PWD}/.rcc
    UI_DIR = $${OUT_PWD}/.uic
}

msvc {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_WARN_ON *= -w44996
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}
