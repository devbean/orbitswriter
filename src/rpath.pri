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

macx {
    !isEmpty(TIGER_COMPAT_MODE) {
        QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@executable_path/../PlugIns/
    } else {
        QMAKE_LFLAGS_SONAME  = -Wl,-install_name,@rpath/PlugIns/
        QMAKE_LFLAGS        += -Wl,-rpath,@loader_path/../,-rpath,@executable_path/../
    }
} else:linux-* {
    # do the rpath by hand since it's not possible to use ORIGIN in QMAKE_RPATHDIR
    # this expands to $ORIGIN (after qmake and make), it does NOT read a qmake var
    QMAKE_RPATHDIR          += \$\$ORIGIN
    QMAKE_RPATHDIR          += \$\$ORIGIN/..
    QMAKE_RPATHDIR          += \$\$ORIGIN/../$$LIBRARY_BASENAME/OrbitsWriter
    APPLICATION_PLUGIN_RPATH = $$join(QMAKE_RPATHDIR, ":")

    QMAKE_LFLAGS  += -Wl,-z,origin \'-Wl,-rpath,$${APPLICATION_PLUGIN_RPATH}\'
    QMAKE_RPATHDIR =
}
