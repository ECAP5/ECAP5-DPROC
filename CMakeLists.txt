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

cmake_minimum_required(VERSION 3.12)
include(FetchContent)

project(ECAP5_DPROC VERSION 1.0.0)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Create python virtual env
message(STATUS "Creating python venv")
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

message(STATUS "Collecting dependencies")
include(${CMAKE_CURRENT_LIST_DIR}/cmake/dependency.cmake)

add_dependency(ECAP5_TREQ 
  GIT ecap5/ecap5-treq
  TAG tags/v2.3.1
  BINARY ecap5-treq)

add_dependency(ECAP5_DTESTLIB
  GIT ecap5/ecap5-dtestlib
  TAG release/v1.1.0)

add_dependency(riscv-tests
  GIT ecap5/riscv-tests
  TAG master)

add_dependency(sphinx-cmake
  GIT ecap5/sphinx-cmake
  TAG tags/v1.0.1)

add_dependency(verilator-cmake
  GIT ecap5/verilator-cmake
  TAG tags/v1.0.1)

add_dependency(oss-cad-suite-cmake
  GIT ecap5/oss-cad-suite-cmake
  TAG tags/v1.0.0)

# Configure dependencies

include(${verilator_cmake_SOURCE_DIR}/cmake/verilator-config.cmake)
include(${ecap5_treq_SOURCE_DIR}/config.cmake)
list(APPEND CMAKE_MODULE_PATH "${sphinx_cmake_SOURCE_DIR}/cmake")
include(${oss_cad_suite_cmake_SOURCE_DIR}/cmake/oss-cad-suite-config.cmake)
include(${ecap5_dtestlib_SOURCE_DIR}/cmake/lint.cmake)
include(${ecap5_dtestlib_SOURCE_DIR}/cmake/testbench.cmake)

# Include subdirectories

add_subdirectory(docs)
add_subdirectory(tests)

# Synthesis

add_synthesis_target(
  SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/* ${CMAKE_CURRENT_LIST_DIR}/src/include/*
  TOP_MODULE ecap5_dproc
  TARGET_FPGA ecp5
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/synth.json)
add_custom_target(synth DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/synth.json)

