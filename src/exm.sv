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

module exm import ecap5_dproc_pkg::*;
(
  input   logic        clk_i,
  // Input logic
  output  logic        input_ready_o,
  input   logic        input_valid_i,
  input   logic[31:0]  pc_i,
  input   instr_t      instr_i,
  input   logic[31:0]  param1_i,
  input   logic[31:0]  param2_i,
  input   logic[31:0]  param3_i,
  input   logic        has_memory_read_i,
  input   logic        has_memory_write_i,
  input   logic        has_result_i,
  // Wishbone master
  output  logic[31:0]  wb_adr_o,
  input   logic[31:0]  wb_dat_i,
  output  logic[31:0]  wb_dat_o,
  output  logic        wb_we_o,
  output  logic[3:0]   wb_sel_o,
  output  logic        wb_stb_o,
  input   logic        wb_ack_i,
  output  logic        wb_cyc_o,
  // Output logic
  input   logic        output_ready_i,
  output  logic        output_valid_o,
  output  logic        result_write_o,
  output  logic[4:0]   result_addr_o,
  output  logic[31:0]  result_o,
  output  logic        branch_o,
  output  logic[19:0]  boffset_o
);

logic[31:0] result_d, result_q;
logic[31:0] load_result = 32'hCAFE0000;
enum {
 INIT, REQUEST_WRITE, REQUEST_READ, RESPONSE
} state_d, state_q;
logic[31:0] shifted_result;

always_comb begin : wishbone_master
  state_d = state_q;
  case(state_q) 
    INIT: begin

    end
    REQUEST_READ: begin
      state_d = RESPONSE; 
    end
    RESPONSE: begin
      state_d = INIT;
    end
    REQUEST_WRITE: begin
      state_d = INIT;
    end
  endcase
end

always_comb begin : result_computation
  result_d = 0;
  case(instr_i) 
    LUI:                  result_d = param1_i;
    AUIPC:                result_d = pc_i + param1_i;
    JAL, JALR:            result_d = pc_i + 4;
    LB, LH, LW, LBU, LHU: result_d = load_result;
    ADD, ADDI:            result_d = param1_i + param2_i;
    SUB:                  result_d = param1_i - param2_i;
    XOR, XORI:            result_d = param1_i ^ param2_i;
    OR, ORI:              result_d = param1_i | param2_i;
    AND, ANDI:            result_d = param1_i & param2_i;
    SLT, SLTI:            result_d = (signed'(param1_i) < signed'(param2_i)) ? 1 : 0;
    SLTU, SLTIU:          result_d = (param1_i < param2_i) ? 1 : 0;
    SLL, SLLI:            result_d = shifted_result;
    SRL, SRLI:            result_d = shifted_result;
//    SRA, SRAI:            result_d = {param2_i[4:0]{param1_i[31]}, param1_i[31 : param2_i[4:0]]};
  endcase
end

always_comb begin : barrel_shifter
  logic[31:0] shift0, shift1, shift2, shift3, shift4;
  logic[31:0] data;

  if((instr_i == SLL) || (instr_i == SLLI)) begin
    data = {<<{param1_i}};
  end else begin
    data = param1_i;
  end

  shift0       =  param2_i[0]  ?  {data[0],   data[31:1]}  :  data;
  shift1       =  param2_i[1]  ?  {shift0[1:0],   shift0[31:2]}    :  shift0;
  shift2       =  param2_i[2]  ?  {shift1[3:0],   shift1[31:4]}    :  shift1;
  shift3       =  param2_i[3]  ?  {shift2[7:0],   shift2[31:8]}    :  shift2;
  shift4       =  param2_i[4]  ?  {shift3[15:0],  shift3[31:16]}   :  shift3;

  if(param2_i > 5'b11111) begin
    shift4 = 0;
  end
  
  if((instr_i == SLL) || (instr_i == SLLI)) begin
    shifted_result = {<<{shift4}};
  end else begin
    shifted_result = shift4;
  end
end

always_ff @(posedge clk_i) begin
  if(has_memory_read_i) begin
    state_q <= REQUEST_READ;
    input_ready_o <= 0;
  end else if(has_memory_write_i) begin
    state_q <= REQUEST_WRITE;
    input_ready_o <= 0;
  end else begin
    result_q <= result_d;
    input_ready_o <= 1;
  end 
end

  assign wb_adr_o = 0;
  assign wb_dat_o = 0;
  assign wb_we_o = 0;
  assign wb_sel_o = 0;
  assign wb_stb_o = 0;
  assign wb_cyc_o = 0;
  assign output_valid_o = 0;
  assign result_write_o = 0;
  assign result_addr_o = 0;
  assign result_o = result_q;
  assign branch_o = 0;
  assign boffset_o = 0;

endmodule // exm