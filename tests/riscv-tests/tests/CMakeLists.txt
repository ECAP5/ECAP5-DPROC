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

set(CROSS_COMPILE riscv64-unknown-elf-)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)

enable_language(ASM)

set(TVM rv32ui) # Target Virtual Machine
set(TE p)       # Target Environment

# Paths
set(SOURCE_DIR ${ecap5_riscv_tests_SOURCE_DIR}/isa/${TVM}/)
set(ENV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/env/)

# Compile options
set(CC_OPTS "-static \
            -mcmodel=medany \
            -fvisibility=hidden \
            -nostdlib \
            -nostartfiles")
set(CC_INCS ${ecap5_riscv_tests_SOURCE_DIR}/env
            ${ENV_DIR}
            ${ecap5_riscv_tests_SOURCE_DIR}/isa/macros/scalar)

set(TARGETS simple
            add addi 
            and andi
            auipc
            beq bge bgeu blt bltu bne
            fence_i
            jal jalr
            lb lbu lh lhu lw
            lui
            ma_data
            or ori
            sb sh sw
            sll slli
            slt slti
            sltiu sltu
            sra srai
            srl srli
            sub
            xor xori)

set(ALL_TARGETS)
foreach(TARGET IN LISTS TARGETS)
  set(FULL_TARGET ${TVM}-${TE}-${TARGET})
  add_executable(${FULL_TARGET}.elf ${SOURCE_DIR}/${TARGET}.S)
  set_target_properties(${FULL_TARGET}.elf PROPERTIES COMPILE_FLAGS "${CC_OPTS} -march=rv32g -mabi=ilp32"
                                                      LINK_FLAGS    "${CC_OPTS} -march=rv32g -mabi=ilp32 -T${ENV_DIR}/link.ld")
  target_include_directories(${FULL_TARGET}.elf PRIVATE ${CC_INCS})

  add_custom_command(
    OUTPUT ${FULL_TARGET}.dump
    COMMAND ${CROSS_COMPILE}objdump -d ${FULL_TARGET}.elf -Mno-aliases -Mnumeric > ${FULL_TARGET}.dump
    VERBATIM)

  list(APPEND ALL_TARGETS ${FULL_TARGET}.elf ${FULL_TARGET}.dump)
endforeach()

add_custom_target(riscv-tests-binaries DEPENDS ${ALL_TARGETS})
