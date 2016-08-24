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

include(../../global.pri)

# copy the plugin spec
isEmpty(TARGET) {
    error("plugin.pri: You must provide a TARGET")
}

defineReplace(stripOutDir) {
    1 ~= s|^$$re_escape($$OUT_PWD/)||$$i_flag
    return($$1)
}

DESTDIR      = $$APPLICATION_BIN_PATH/plugins
LIBS        += -L$$DESTDIR
INCLUDEPATH += $$OUT_PWD

PLUGINJSON = $$_PRO_FILE_PWD_/$${TARGET}.json
PLUGINJSON_IN = $${PLUGINJSON}.in
exists($$PLUGINJSON_IN) {
    DISTFILES += $$PLUGINJSON_IN
    QMAKE_SUBSTITUTES += $$PLUGINJSON_IN
    PLUGINJSON = $$OUT_PWD/$${TARGET}.json

} else {
    # need to support that for external plugins
    DISTFILES += $$PLUGINJSON
}

osx: QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/PlugIns/
include(../rpath.pri)

contains(QT_CONFIG, reduce_exports):CONFIG += hide_symbols

TEMPLATE = lib
CONFIG += plugin plugin_with_soname
linux*:QMAKE_LFLAGS += $$QMAKE_LFLAGS_NOUNDEF

#!macx {
#    target.path = $$INSTALL_PLUGIN_PATH
#    INSTALLS += target
#}

TARGET = $$libraryTargetName($$TARGET)
