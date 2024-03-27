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

#ifndef TESTBENCH_H
#define TESTBENCH_H

// This macro is used to allow easier parsing of all the checks
#define CHECK_3(TB, COND, MSG) tb->formal_check(TB, COND, MSG)
#define CHECK_4(TB, COND, MSG, TICK) tb->formal_check(TB, COND, MSG, TICK)
#define CHECK_X(x, TB, COND, MSG, TICK, FUNC, ...) FUNC
#define CHECK(...) CHECK_X(,##__VA_ARGS__,\
                           CHECK_4(__VA_ARGS__),  \
                           CHECK_3(__VA_ARGS__)   \
                          )

template<class Module> class Testbench {
public:
  unsigned long tickcount;

  Module * core;
  VerilatedVcdC * trace;

  bool success;

  const char * testdata_path;

  bool debug_log;

  int num_conditions;
  bool * conditions;
  int * err_cycles;
  int cycle;

  Testbench() {
    this->tickcount = 0;
    this->core = new Module;
    this->success = true;
    this->testdata_path = NULL;
    this->debug_log = false;

    this->conditions = NULL;
    this->err_cycles = NULL;
    this->cycle = 0;
  }

  ~Testbench() {
    this->core->final();
    this->trace->close();
    this->trace = NULL;
    delete this->core;
    this->core = NULL;

    if(this->conditions != NULL) {
      delete this->conditions;
      this->conditions = NULL;
    }
    if(this->err_cycles != NULL) {
      delete this->err_cycles;
      this->err_cycles = NULL;
    }
  }

  void open_trace(const char * path) {
    if(this->trace == NULL) {
      this->trace = new VerilatedVcdC;
      this->core->trace(this->trace, 99);
      this->trace->open(path);
    }
  }

  void set_debug_log(bool debug_log) {
    this->debug_log = debug_log;
  }

  virtual void reset() {
    this->reset_conditions();
  }

  void tick() {
    this->tickcount += 1;
    this->cycle += 1;

    core->clk_i = 0;
    core->eval();
    if(this->trace) {
      this->trace->dump(10 * this->tickcount - 2);
    }

    core->clk_i = 1;
    core->eval();
    if(this->trace) {
      this->trace->dump(10 * this->tickcount);
    }

    core->clk_i = 0;
    core->eval();
    if(this->trace) {
      this->trace->dump(10 * this->tickcount+5);
      this->trace->flush();
    }
  }

  void open_testdata(const char * path) {
    this->testdata_path = path;
    // open the file to clear the content
    FILE * f = fopen(this->testdata_path, "w");
    assert(f);
    fclose(f);
  }

  void formal_check(const char * testbench, bool condition, const char * msg, int tick = -1) {
    if(this->testdata_path != NULL) {
      FILE * f = fopen(this->testdata_path, "a");
      if(condition) {
        fprintf(f, "%s;%d\n", testbench, true);
      } else {
        if(tick != -1) {
          fprintf(f, "[tick(%d)]: ", tick);
        }
        fprintf(f, "%s;%d;%s\n", testbench, false, msg);
      }
      fclose(f);
    }
    if(this->debug_log) {
      printf("[%s]: ", testbench);
      if(condition) {
        printf("OK\n");
      } else {
        if(tick != -1) {
          printf("[tick(%d)]: ", tick);
        }
        printf("%s\n", msg);
      }
    }

    if(!condition) {
        this->success = false;
    }
  }

  void init_conditions(int num_conditions) {
    this->num_conditions = num_conditions;
    this->conditions = new bool[num_conditions];
    this->err_cycles = new int[num_conditions];
  }

  void reset_conditions() {
    if(this->conditions != NULL && this->err_cycles != NULL) {
      for(int i = 0; i < this->num_conditions; i++) {
        this->conditions[i] = true;
        this->err_cycles[i] = -1;
      } 
    }
    this->cycle = 0;
  }

  void check(int cond_id, bool condition) {
    this->conditions[cond_id] &= condition;
    if(!condition && (this->err_cycles[cond_id] == -1)) {
      this->err_cycles[cond_id] = this->cycle;
    }
  }
};

bool parse_verbose(int argc, char ** argv) {
  return (argc == 2) && (strncmp(argv[1], "-v", 2) == 0);
}

#endif
