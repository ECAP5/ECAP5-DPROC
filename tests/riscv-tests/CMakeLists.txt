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

add_subdirectory(tests)

get_all_sources_recursive(ecap5_dproc RISCV_TESTS_SOURCES)

# riscv-tests
add_executable(riscv-tests-executable ${CMAKE_CURRENT_SOURCE_DIR}/riscv-tests.cpp)
target_include_directories(riscv-tests-executable PRIVATE ${TEST_INCLUDE_DIRS})
verilate(riscv-tests-executable
  PREFIX Vecap5_dproc
  SOURCES ${RISCV_TESTS_SOURCES}
  TRACE) 
get_target_property(RISCV_TESTS_EXECUTABLE riscv-tests-executable BINARY_DIR)
if(${DEBUGLOG})
  set(RUN_TARGET_ARGUMENT "-v")  
endif()
add_custom_command(
  COMMAND ${RISCV_TESTS_EXECUTABLE}/riscv-tests-executable ${RUN_TARGET_ARGUMENT}
  OUTPUT ${TESTDATA_DIR}/riscv-tests.csv
  DEPENDS riscv-tests-executable
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests/)
add_custom_target(riscv-tests DEPENDS riscv-tests-binaries ${TESTDATA_DIR}/riscv-tests.csv)
