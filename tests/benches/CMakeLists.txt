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

add_testbench(
  MODULE       registers
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       fetch
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       decode
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       execute
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       loadstore
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       loadstore 
  BENCH        loadstore_w_slave 
  LIBS         instr_wb_slave
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       writeback
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       memory
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       hazard
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_testbench(
  MODULE       ecap5_dproc
  BENCH_DIR    ${BENCH_DIR}
  LIBS_DIR     ${LIBS_DIR}
  TESTDATA_DIR ${TESTDATA_DIR}
  SRC_DIRS     ${SRC_DIRS} 
  INCLUDE_DIRS ${INCLUDE_DIRS}
)

add_custom_target(benches-build DEPENDS ${TEST_BINARIES})
add_custom_target(benches DEPENDS ${TEST_TARGETS})
