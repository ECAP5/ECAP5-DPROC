/*           __        _
 *  ________/ /  ___ _(_)__  ___
 * / __/ __/ _ \/ _ `/ / _ \/ -_)
 * \__/\__/_//_/\_,_/_/_//_/\__/
 * 
 * Copyright (C) Clément Chaine
 * This file is part of ECAP5-DPROC <https://github.com/cchaine/ECAP5-DPROC>
 *
 * ECAP5-DPROC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ECAP5-DPROC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ECAP5-DPROC.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <svdpi.h>

#include "Vtb_exm.h"
#include "testbench.h"
#include "Vtb_exm_ecap5_dproc_pkg.h"

class TB_Exm : public Testbench<Vtb_exm> {
public:
  void reset() {
    Testbench<Vtb_exm>::reset();

    this->_nop();
    this->core->rst_i = 1;
    for(int i = 0; i < 5; i++) {
      this->tick();
    }
    this->core->rst_i = 0;
  }
  
  void _nop() {
    this->core->alu_operand1_i = 0;
    this->core->alu_operand2_i = 0;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_ADD;
    this->core->alu_sub_i = 0;
    this->core->alu_shift_left_i = 0;
    this->core->alu_signed_shift_i = 0;
    this->core->result_write_i = 0;
    this->core->result_addr_i = 0;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::NO_BRANCH;
    this->core->branch_offset_i = 0;
  }

  void _add(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_ADD;
    this->core->alu_sub_i = 0;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _sub(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_ADD;
    this->core->alu_sub_i = 1;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _xor(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_XOR;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _or(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_OR;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _and(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_AND;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _slt(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_SLT;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _sltu(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_SLTU;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _sll(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_SHIFT;
    this->core->alu_shift_left_i = 1;
    this->core->alu_signed_shift_i = 0;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _srl(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_SHIFT;
    this->core->alu_shift_left_i = 0;
    this->core->alu_signed_shift_i = 0;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _sra(uint32_t operand1, uint32_t operand2, uint32_t result_addr) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_SHIFT;
    this->core->alu_shift_left_i = 0;
    this->core->alu_signed_shift_i = 1;
    this->core->branch_cond_i = 0;
    this->core->result_write_i = 1;
    this->core->result_addr_i = result_addr;
  }

  void _beq(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BEQ;
    this->core->branch_offset_i = branch_offset;
  }

  void _bne(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BNE;
    this->core->branch_offset_i = branch_offset;
  }

  void _blt(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BLT;
    this->core->branch_offset_i = branch_offset;
  }

  void _bltu(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BLTU;
    this->core->branch_offset_i = branch_offset;
  }

  void _bge(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BGE;
    this->core->branch_offset_i = branch_offset;
  }

  void _bgeu(uint32_t operand1, uint32_t operand2, uint32_t branch_offset) {
    this->_nop();
    this->core->alu_operand1_i = operand1;
    this->core->alu_operand2_i = operand2;
    this->core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BGEU;
    this->core->branch_offset_i = branch_offset;
  }
};

enum CondId {
  COND_result,
  COND_branch,
  COND_output_valid,
  __CondIdEnd
};

void tb_exm_alu_add(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 1;

  // The following actions are performed in this test :
  //    tick 0. Set inputs for ADD
  //    tick 1. Set inputs for nop (core outputs result of ADD)

  //=================================
  //      Tick (0)
  
  tb->reset();
  
  //`````````````````````````````````
  //      Set inputs
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_add(operand1, operand2, result_addr);

  //=================================
  //      Tick (1)
  
  tb->tick();

  //`````````````````````````````````
  //      Set inputs
  
  tb->_nop();

  //`````````````````````````````````
  //      Checks 
  
  uint32_t result = ((int32_t)operand1 + (int32_t)operand2);
  tb->check(COND_result,       (core->result_o        ==  result)  &&
                               (core->result_write_o  ==  1)       &&
                               (core->result_addr_o   ==  result_addr));
  tb->check(COND_branch,       (core->branch_o        ==  0));
  tb->check(COND_output_valid, (core->output_valid_o  ==  1));

  //`````````````````````````````````
  //      Formal Checks 
  
  CHECK("tb_exm.alu.ADD_01",
      tb->conditions[COND_result],
      "Failed to implement the result protocol", tb->err_cycles[COND_result]);

  CHECK("tb_exm.alu.ADD_02",
      tb->conditions[COND_branch],
      "Failed to implement the branch protocol", tb->err_cycles[COND_branch]);

  CHECK("tb_exm.alu.ADD_03",
      tb->conditions[COND_output_valid],
      "Failed to implement the output_valid_o", tb->err_cycles[COND_output_valid]);
}

void tb_exm_alu_sub(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 2;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint32_t result_addr = rand() % 32;
  tb->_sub(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.SUB_01",
      (core->result_o == ((int32_t)operand1 - (int32_t)operand2)),
      "Failed to execute ALU_ADD operation with sub");
  CHECK("tb_exm.alu.SUB_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SUB_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SUB_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SUB_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_xor(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 3;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_xor(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.XOR_01",
      (core->result_o == (operand1 ^ operand2)),
      "Failed to execute ALU_XOR operation");
  CHECK("tb_exm.alu.XOR_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.XOR_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.XOR_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.XOR_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_or(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 4;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_or(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.OR_01",
      (core->result_o == (operand1 | operand2)),
      "Failed to execute ALU_OR operation");
  CHECK("tb_exm.alu.OR_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.OR_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.OR_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.OR_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_and(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 5;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_and(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.AND_01",
      (core->result_o == (operand1 & operand2)),
      "Failed to execute ALU_OR operation");
  CHECK("tb_exm.alu.AND_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.AND_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.AND_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.AND_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_slt(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 6;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  // Test values from operand2 - 8 to operand2 + 2
  uint8_t result_addr = rand() % 32;
  uint32_t operand2 = 2 + rand() % 5;
  bool SLT_01_cond = 1;
  bool SLT_02_cond = 1;
  bool SLT_03_cond = 1;
  bool SLT_04_cond = 1;
  bool SLT_05_cond = 1;
  for(int i = 0; i < 10; i++) {
    tb->_slt((int32_t)operand2 - 8 + i, operand2, result_addr);
    tb->tick();

    SLT_01_cond &= (core->result_o == (((int32_t)operand2 - 8 + i) < (int32_t)operand2));
    SLT_02_cond &= (core->result_write_o == 1);
    SLT_03_cond &= (core->result_addr_o == result_addr);
    SLT_04_cond &= (core->branch_o == 0);
    SLT_05_cond &= (core->output_valid_o == 1);
  }

  CHECK("tb_exm.alu.SLT_01",
      SLT_01_cond,
      "Failed to execute ALU_SLT operation");
  CHECK("tb_exm.alu.SLT_02",
      SLT_02_cond,
      "Failed to output the result write");
  CHECK("tb_exm.alu.SLT_03",
      SLT_03_cond,
      "Failed to output the result address");
  CHECK("tb_exm.alu.SLT_04",
      SLT_04_cond,
      "Failed to output branch");
  CHECK("tb_exm.alu.SLT_05",
      SLT_05_cond,
      "Failed to validate the output");
}

void tb_exm_alu_sltu(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 7;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  // Test values from operand2 - 8 to operand2 + 2 with operand2 - 8 being greater when unsigned
  uint8_t result_addr = rand() % 32;
  uint32_t operand2 = 2 + rand() % 5;
  bool SLTU_01_cond = 1;
  bool SLTU_02_cond = 1;
  bool SLTU_03_cond = 1;
  bool SLTU_04_cond = 1;
  bool SLTU_05_cond = 1;
  for(int i = 0; i < 10; i++) {
    tb->_sltu((int32_t)operand2 - 8 + i, operand2, result_addr);
    tb->tick();

    SLTU_01_cond &= (core->result_o == ((uint32_t)((int32_t)operand2 - 8 + i) < (uint32_t)(int32_t)operand2));
    SLTU_02_cond &= (core->result_write_o == 1);
    SLTU_03_cond &= (core->result_addr_o == result_addr);
    SLTU_04_cond &= (core->branch_o == 0);
    SLTU_05_cond &= (core->output_valid_o == 1);
  }

  CHECK("tb_exm.alu.SLTU_01",
      SLTU_01_cond,
      "Failed to execute ALU_SLTU operation");
  CHECK("tb_exm.alu.SLTU_02",
      SLTU_02_cond,
      "Failed to output the result write");
  CHECK("tb_exm.alu.SLTU_03",
      SLTU_03_cond,
      "Failed to output the result address");
  CHECK("tb_exm.alu.SLTU_04",
      SLTU_04_cond,
      "Failed to output branch");
  CHECK("tb_exm.alu.SLTU_05",
      SLTU_05_cond,
      "Failed to validate the output");
}

void tb_exm_alu_sll(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 8;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  uint32_t operand1 = rand();
  uint32_t operand2 = 3 + rand() % 29;
  uint32_t result_addr = rand() % 32;
  tb->_sll(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.SLL_01",
      (core->result_o == (operand1 << (operand2 & 0x1F))),
      "Failed to execute ALU_SLL operation");
  CHECK("tb_exm.alu.SLL_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SLL_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SLL_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SLL_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_srl(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 9;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a negative number
  
  uint32_t operand1 = rand() | 0x80000000; // enable the sign bit
  uint32_t operand2 = 3 + rand() % 29;
  uint32_t result_addr = rand() % 32;
  tb->_srl(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.SRL_01",
      (core->result_o == (operand1 >> (operand2 & 0x1F))),
      "Failed to execute ALU_SRL operation");
  CHECK("tb_exm.alu.SRL_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SRL_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SRL_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SRL_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a positive number

  operand1 = rand() & ~(0x80000000); // disable the sign bit
  operand2 = 3 + rand() % 29;
  result_addr = rand() % 32;
  tb->_srl(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.alu.SRL_06",
      (core->result_o == (operand1 >> (operand2 & 0x1F))),
      "Failed to execute ALU_SRL operation");
  CHECK("tb_exm.alu.SRL_07",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SRL_08",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SRL_09",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SRL_10",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_alu_sra(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 10;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a negative number
  
  uint32_t operand1 = rand() | 0x80000000; // enable the sign bit
  uint32_t operand2 = 3 + rand() % 29;
  uint32_t result_addr = rand() % 32;
  tb->_sra(operand1, operand2, result_addr);
  tb->tick();

  uint32_t expected  = (operand1 >> (operand2 & 0x1F));
           expected |= ((1 << (operand2 & 0x1F)) - 1) << (32 - (operand2 & 0x1F));

  CHECK("tb_exm.alu.SRA_01",
      (core->result_o == expected),
      "Failed to execute ALU_SRA operation");
  CHECK("tb_exm.alu.SRA_02",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SRA_03",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SRA_04",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SRA_05",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a positive number

  operand1 = rand() & ~(0x80000000); // disable the sign bit
  operand2 = 3 + rand() % 29;
  result_addr = rand() % 32;
  tb->_sra(operand1, operand2, result_addr);
  tb->tick();

  expected  = (operand1 >> (operand2 & 0x1F));

  CHECK("tb_exm.alu.SRA_06",
      (core->result_o == (operand1 >> (operand2 & 0x1F))),
      "Failed to execute ALU_SRA operation");
  CHECK("tb_exm.alu.SRA_07",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.alu.SRA_08",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.alu.SRA_09",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.alu.SRA_10",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_beq(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 11;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with different values
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_beq(operand1, operand2, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BEQ_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BEQ_02",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BEQ_03",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with equal values
  
  tb->_beq(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BEQ_04",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BEQ_05",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BEQ_06",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BEQ_07",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_bne(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 12;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with equal values
  
  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_bne(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BNE_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BNE_02",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BNE_03",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with different values

  tb->_bne(operand1, operand2, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BNE_04",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BNE_05",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BNE_06",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BNE_07",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_blt(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 13;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a lower value
  
  uint32_t operand1 = 2 + rand() % 6;
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_blt((int32_t)operand1 + 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLT_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLT_02",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLT_03",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a value equal

  tb->_blt(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLT_04",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLT_05",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLT_06",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a greater value 

  tb->_blt((int32_t)operand1 - 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLT_07",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLT_08",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLT_09",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BLT_10",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_bltu(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 14;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a greater value
  
  uint32_t operand1 = 2 % rand() % 6;
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_bltu((int32_t)operand1 + 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLTU_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLTU_02",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLTU_03",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with an equal value

  tb->_bltu(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLTU_04",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLTU_05",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLTU_06",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a lower negative value (greater when unsigned)

  tb->_bltu((int32_t)operand1 - 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLTU_07",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLTU_08",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLTU_09",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a lower positive value

  tb->_bltu((int32_t)operand1 - 2, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BLTU_10",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BLTU_11",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BLTU_12",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BLTU_13",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_bge(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 15;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a lower value
  
  uint32_t operand1 = 2 + rand() % 6;
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_bge((int32_t)operand1 - 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGE_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGE_02",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGE_03",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with an equal value

  tb->_bge(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGE_04",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGE_05",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGE_06",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BGE_07",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a positive value

  tb->_bge((int32_t)operand1 + 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGE_08",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGE_09",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGE_10",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BGE_11",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_branch_bgeu(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 16;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  // Test with a lower negative value (greater when unsigned)
  
  uint32_t operand1 = 2 + rand() % 6;
  uint32_t branch_offset = rand() % 0xFFFFF;
  tb->_bgeu((int32_t)operand1 - 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGEU_01",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGEU_02",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGEU_03",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BGEU_04",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with an equal value

  tb->_bgeu(operand1, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGEU_05",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGEU_06",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGEU_07",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BGEU_08",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a greater positive value

  tb->_bgeu((int32_t)operand1 + 10, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGEU_09",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGEU_10",
      (core->branch_o == 1),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGEU_11",
      (core->branch_offset_o == branch_offset),
      "Failed to output branch offset");
  CHECK("tb_exm.branch.BGEU_12",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  // Test with a lower positive value
  
  tb->_bgeu((int32_t)operand1 - 2, operand1, branch_offset);
  tb->tick();

  CHECK("tb_exm.branch.BGEU_13",
      (core->result_write_o == 0),
      "Failed to output the result write");
  CHECK("tb_exm.branch.BGEU_14",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.branch.BGEU_15",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_back_to_back(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 17;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  CHECK("tb_exm.back_to_back.01",
      (core->output_valid_o == 0),
      "Failed to invalidate the output");

  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_add(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.back_to_back.02",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)),
      "Failed to execute operation back to back");
  CHECK("tb_exm.back_to_back.03",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.back_to_back.04",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.back_to_back.05",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.back_to_back.06",
      (core->output_valid_o == 1),
      "Failed to validate the output");


  operand1 = rand();
  operand2 = rand();
  result_addr = rand() % 32;
  tb->_sub(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.back_to_back.07",
      (core->result_o == ((int32_t)operand1 - (int32_t)operand2)),
      "Failed to execute operation back to back");
  CHECK("tb_exm.back_to_back.08",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.back_to_back.09",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.back_to_back.10",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.back_to_back.11",
      (core->output_valid_o == 1),
      "Failed to validate the output");

  operand1 = rand();
  operand2 = rand();
  result_addr = rand() % 32;
  tb->_add(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.back_to_back.12",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)),
      "Failed to execute operation back to back");
  CHECK("tb_exm.back_to_back.13",
      (core->result_write_o == 1),
      "Failed to output the result write");
  CHECK("tb_exm.back_to_back.14",
      (core->result_addr_o == result_addr),
      "Failed to output the result address");
  CHECK("tb_exm.back_to_back.15",
      (core->branch_o == 0),
      "Failed to output branch");
  CHECK("tb_exm.back_to_back.16",
      (core->output_valid_o == 1),
      "Failed to validate the output");
}

void tb_exm_bubble(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 18;
  tb->reset();
  tb->_nop();

  core->output_ready_i = 1;
  
  core->input_valid_i = 0;
  core->alu_operand1_i = rand();
  core->alu_operand2_i = rand();
  core->alu_op_i = rand() % 7;
  core->alu_sub_i = rand() % 2;
  core->alu_shift_left_i = rand() % 2;
  core->alu_signed_shift_i = rand() % 2;
  core->result_write_i = 1;
  core->result_addr_i = rand() % 32;
  core->branch_cond_i = 1 + rand() % 6;
  core->branch_offset_i = rand() % 0xFFFFF;

  tb->tick();

  CHECK("tb_exm.bubble.01",
      (core->result_write_o == 0),
      "Failed to deassert result_write_o when bubble");
  CHECK("tb_exm.bubble.02",
      (core->branch_o == Vtb_exm_ecap5_dproc_pkg::NO_BRANCH),
      "Failed to set branch to NO_BRANCH when bubble");
}

void tb_exm_wait_after_reset(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 19;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 0;

  CHECK("tb_exm.wait_after_reset.01",
      (core->input_ready_o == 0),
      "Failed to deassert input_ready_o");

  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_add(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.wait_after_reset.02",
      (core->input_ready_o == 0),
      "Failed to deassert input_ready_o");

  CHECK("tb_exm.wait_after_reset.03",
      (core->result_o == 0) && (core->result_write_o == 0) && (core->result_addr_o == 0) && (core->branch_o == 0) && (core->output_valid_o == 0),
      "Failed to handle input handshake");

  tb->tick();

  CHECK("tb_exm.wait_after_reset.04",
      (core->input_ready_o == 0),
      "Failed to deassert input_ready_o");

  CHECK("tb_exm.wait_after_reset.05",
      (core->result_o == 0) && (core->result_write_o == 0) && (core->result_addr_o == 0) && (core->branch_o == 0) && (core->output_valid_o == 0),
      "Failed to handle input handshake");

  tb->tick();

  CHECK("tb_exm.wait_after_reset.06",
      (core->input_ready_o == 0),
      "Failed to deassert input_ready_o");

  CHECK("tb_exm.wait_after_reset.07",
      (core->result_o == 0) && (core->result_write_o == 0) && (core->result_addr_o == 0) && (core->branch_o == 0) && (core->output_valid_o == 0),
      "Failed to handle input handshake");

  tb->tick();

  CHECK("tb_exm.wait_after_reset.08",
      (core->input_ready_o == 0),
      "Failed to reassert input_ready_o");

  CHECK("tb_exm.wait_after_reset.09",
      (core->result_o == 0) && (core->result_write_o == 0) && (core->result_addr_o == 0) && (core->branch_o == 0) && (core->output_valid_o == 0),
      "Failed to handle input handshake");

  core->output_ready_i = 1;
  tb->tick();

  CHECK("tb_exm.wait_after_reset.10",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to handle input handshake");

  tb->_sub(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.wait_after_reset.11",
      (core->result_o == ((int32_t)operand1 - (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to handle input handshake");
}

void tb_exm_wait(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 20;
  tb->reset();
  tb->_nop();
  
  core->input_valid_i = 1;
  core->output_ready_i = 1;

  uint32_t operand1 = rand();
  uint32_t operand2 = rand();
  uint8_t result_addr = rand() % 32;
  tb->_xor(operand1, operand2, result_addr);
  
  tb->tick();

  tb->_add(operand1, operand2, result_addr);
  tb->tick();

  CHECK("tb_exm.wait.01",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to hold the output values");
  
  tb->_sub(operand1, operand2, result_addr + 10);
  core->output_ready_i = 0;
  tb->tick();

  CHECK("tb_exm.wait.02",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to hold the output values");

  tb->tick();

  CHECK("tb_exm.wait.03",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to hold the output values");

  tb->tick();

  CHECK("tb_exm.wait.04",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to hold the output values");

  tb->tick();

  CHECK("tb_exm.wait.05",
      (core->result_o == ((int32_t)operand1 + (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to hold the output values");

  core->output_ready_i = 1;
  
  tb->tick();

  CHECK("tb_exm.wait.06",
      (core->result_o == ((int32_t)operand1 - (int32_t)operand2)) && (core->result_write_o == 1) && (core->result_addr_o == result_addr + 10) && (core->branch_o == 0) && (core->output_valid_o == 1),
      "Failed to output values");

  tb->_nop();
  tb->tick();
}

void tb_exm_reset(TB_Exm * tb) {
  Vtb_exm * core = tb->core;
  core->testcase = 21;
  tb->reset();
  tb->_nop();

  core->input_valid_i = 1;
  core->output_ready_i = 1;
  
  core->input_valid_i = 0;
  core->alu_operand1_i = rand();
  core->alu_operand2_i = core->alu_operand1_i;
  core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_ADD;
  core->alu_shift_left_i = rand() % 2;
  core->alu_signed_shift_i = rand() % 2;
  core->result_write_i = 1;
  core->result_addr_i = rand() % 32;
  core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BEQ;
  core->branch_offset_i = rand() % 0xFFFFF;

  core->rst_i = 1;
  tb->tick();
  core->rst_i = 0;

  CHECK("tb_exm.reset.01",
      (core->result_write_o == 0),
      "Failed to deassert result_write_o when reset");
  CHECK("tb_exm.reset.02",
      (core->branch_o == Vtb_exm_ecap5_dproc_pkg::NO_BRANCH),
      "Failed to set branch to NO_BRANCH when reset");

  tb->tick();

  core->input_valid_i = 0;
  core->alu_operand1_i = rand();
  core->alu_operand2_i = core->alu_operand1_i;
  core->alu_op_i = Vtb_exm_ecap5_dproc_pkg::ALU_ADD;
  core->alu_shift_left_i = rand() % 2;
  core->alu_signed_shift_i = rand() % 2;
  core->result_write_i = rand() % 2;
  core->result_addr_i = rand() % 32;
  core->branch_cond_i = Vtb_exm_ecap5_dproc_pkg::BRANCH_BEQ;
  core->branch_offset_i = rand() % 0xFFFFF;

  tb->tick();

  core->rst_i = 1;
  tb->tick();
  core->rst_i = 0;

  CHECK("tb_exm.reset.03",
      (core->result_write_o == 0),
      "Failed to deassert result_write_o when reset");
  CHECK("tb_exm.reset.04",
      (core->branch_o == Vtb_exm_ecap5_dproc_pkg::NO_BRANCH),
      "Failed to set branch to NO_BRANCH when reset");
}

int main(int argc, char ** argv, char ** env) {
  srand(time(NULL));
  Verilated::traceEverOn(true);

  bool verbose = parse_verbose(argc, argv);

  TB_Exm * tb = new TB_Exm;
  tb->open_trace("waves/exm.vcd");
  tb->open_testdata("testdata/exm.csv");
  tb->set_debug_log(verbose);
  tb->init_conditions(__CondIdEnd);

  /************************************************************/

  tb_exm_alu_add(tb);
  tb_exm_alu_sub(tb);
  tb_exm_alu_xor(tb);
  tb_exm_alu_or(tb);
  tb_exm_alu_and(tb);
  tb_exm_alu_slt(tb);
  tb_exm_alu_sltu(tb);
  tb_exm_alu_sll(tb);
  tb_exm_alu_srl(tb);
  tb_exm_alu_sra(tb);

  tb_exm_branch_beq(tb);
  tb_exm_branch_bne(tb);
  tb_exm_branch_blt(tb);
  tb_exm_branch_bltu(tb);
  tb_exm_branch_bge(tb);
  tb_exm_branch_bgeu(tb);

  tb_exm_back_to_back(tb);
  tb_exm_bubble(tb);
  tb_exm_reset(tb);
  tb_exm_wait_after_reset(tb);
  tb_exm_wait(tb);

  /************************************************************/

  printf("[EXM]: ");
  if(tb->success) {
    printf("Done\n");
  } else {
    printf("Failed\n");
  }

  delete tb;
  exit(EXIT_SUCCESS);
}
