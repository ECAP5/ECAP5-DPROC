#           __        _
#  ________/ /  ___ _(_)__  ___
# / __/ __/ _ \/ _ `/ / _ \/ -_)
# \__/\__/_//_/\_,_/_/_//_/\__/
# 
# Copyright (C) Clément Chaine
# This file is part of ECAP5-DPROC <https://github.com/ecap5/ECAP5-DPROC>
# 
# ECAP5-DPROC is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ECAP5-DPROC is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ECAP5-DPROC.  If not, see <http://www.gnu.org/licenses/>.

get_all_sources_recursive(ecap5_dproc EMULATOR_SOURCES)

add_executable(emulator ${CMAKE_CURRENT_LIST_DIR}/emulator.cpp)
target_include_directories(emulator PRIVATE ${TEST_INCLUDE_DIRS})
verilate(emulator
  PREFIX Vecap5_dproc
  SOURCES ${EMULATOR_SOURCES}
  TRACE) 

add_subdirectory(examples)
