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

cmake_minimum_required(VERSION 3.21)
include(FetchContent)

project(ECAP5_DPROC)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Create python virtual env
set(VENV_DIR ${CMAKE_BINARY_DIR}/venv)
if(NOT EXISTS "${VENV_DIR}")
  find_package(Python3 COMPONENTS Interpreter)
  execute_process(COMMAND "${Python3_EXECUTABLE}" -m venv ${VENV_DIR})
  set(Python3_FIND_VIRTUALENV ONLY)
  unset(Python3_EXECUTABLE)
endif()
set(ENV{VIRTUAL_ENV} "${VENV_DIR}")
find_package(Python3 COMPONENTS Interpreter Development)

# Dependencies

include(${CMAKE_CURRENT_LIST_DIR}/cmake/dependency.cmake)

add_dependency(
  GIT ecap5/sphinx-cmake
  TAG tags/v1.0.1)

add_dependency(
  GIT ecap5/verilator-cmake
  TAG tags/v1.0.1)

add_dependency(
  GIT ecap5/ecap5-treq
  TAG release/v3.0.0
  BINARY ecap5-treq)

add_dependency(
  GIT ecap5/oss-cad-suite-cmake
  TAG release/v2.0.0)

add_dependency(
  GIT ecap5/ecap5-dtestlib
  TAG release/v1.1.0)

add_dependency(
  GIT ecap5/riscv-tests
  TAG master)

# Define an interface library
add_library(ecap5_dproc INTERFACE)
target_sources(ecap5_dproc INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/src/include/ecap5_dproc_pkg.svh
  ${CMAKE_CURRENT_LIST_DIR}/src/include/riscv_pkg.svh
  ${CMAKE_CURRENT_LIST_DIR}/src/ecap5_dproc.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/decode.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/execute.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/fetch.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/hazard.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/loadstore.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/memory.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/registers.sv
  ${CMAKE_CURRENT_LIST_DIR}/src/writeback.sv
)

if(PROJECT_IS_TOP_LEVEL)
  # Configure dependencies

  include(${ecap5_verilator_cmake_SOURCE_DIR}/cmake/verilator-config.cmake)
  include(${ecap5_ecap5_treq_SOURCE_DIR}/config.cmake)
  list(APPEND CMAKE_MODULE_PATH "${ecap5_sphinx_cmake_SOURCE_DIR}/cmake")
  include(${ecap5_oss_cad_suite_cmake_SOURCE_DIR}/cmake/oss-cad-suite-config.cmake)
  include(${ecap5_ecap5_dtestlib_SOURCE_DIR}/cmake/testbench.cmake)
  include(${ecap5_ecap5_dtestlib_SOURCE_DIR}/cmake/lint.cmake)

  # Include subdirectories

  add_subdirectory(docs)
  add_subdirectory(tests)

  # Synthesis

  add_synthesis_target(
    LIB        ecap5_dproc
    TOP_MODULE ecap5_dproc
    TARGET_FPGA ecp5
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/synth.json)
  add_custom_target(synth DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/synth.json)
endif()
