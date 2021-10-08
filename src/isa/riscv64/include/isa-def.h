#ifndef __ISA_RISCV64_H__
#define __ISA_RISCV64_H__

#include <common.h>
#ifdef CONFIG_RVV_010
#include "../instr/rvv/vreg.h"
#endif // CONFIG_RVV_010

#define FORCE_RAISE_PF
// #define XIANGSHAN_DEBUG

// Execution Guide generated by DUT
struct ExecutionGuide {
  uint64_t exceptionNo;
  uint64_t mtval;
  uint64_t stval;
};

typedef struct {
  union {
    uint64_t _64;
  } gpr[32];

  union {
    uint64_t _64;
  } fpr[32];

  // shadow CSRs for difftest
  uint64_t pc;
  uint64_t mstatus, mcause, mepc;
  uint64_t sstatus, scause, sepc;

  uint64_t satp, mip, mie, mscratch, sscratch, mideleg, medeleg;
#ifdef CONFIG_RVV_010
  //vector
  union {
    uint64_t _64[VENUM64];
    uint32_t _32[VENUM32];
    uint16_t _16[VENUM16];
    uint8_t  _8[VENUM8];
  } vr[32];

  uint64_t vstart;
  uint64_t vxsat, vxrm, vl, vtype;
#endif // CONFIG_RVV_010

  uint64_t mtval, stval, mtvec, stvec;
  uint64_t mode;

  // exec state
  bool amo;
  int mem_exception;

  // for LR/SC
  uint64_t lr_addr;
  uint64_t lr_valid;

  bool INTR;

  // Guided exec
  bool guided_exec;
  struct ExecutionGuide execution_guide;
} riscv64_CPU_state;

// decode
typedef struct {
  union {
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t rd        : 5;
      uint32_t funct3    : 3;
      uint32_t rs1       : 5;
      uint32_t rs2       : 5;
      uint32_t funct7    : 7;
    } r;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t rd        : 5;
      uint32_t funct3    : 3;
      uint32_t rs1       : 5;
      int32_t  simm11_0  :12;
    } i;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t imm4_0    : 5;
      uint32_t funct3    : 3;
      uint32_t rs1       : 5;
      uint32_t rs2       : 5;
      int32_t  simm11_5  : 7;
    } s;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t imm11     : 1;
      uint32_t imm4_1    : 4;
      uint32_t funct3    : 3;
      uint32_t rs1       : 5;
      uint32_t rs2       : 5;
      uint32_t imm10_5   : 6;
      int32_t  simm12    : 1;
    } b;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t rd        : 5;
      int32_t  simm31_12 :20;
    } u;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t rd        : 5;
      uint32_t imm19_12  : 8;
      uint32_t imm11     : 1;
      uint32_t imm10_1   :10;
      int32_t  simm20    : 1;
    } j;
    struct {
      uint32_t pad7      :20;
      uint32_t csr       :12;
    } csr;
    struct {
      uint32_t opcode1_0 : 2;
      uint32_t opcode6_2 : 5;
      uint32_t rd        : 5;
      uint32_t rm        : 3;
      uint32_t rs1       : 5;
      uint32_t rs2       : 5;
      uint32_t fmt       : 2;
      uint32_t funct5    : 5;
    } fp;
    #ifdef CONFIG_RVV_010
    //vector-OP-V
    struct {
      uint32_t pad16     : 7;
      uint32_t v_vd      : 5;
      uint32_t pad17     : 3;
      uint32_t v_vs1     : 5;
      uint32_t v_vs2     : 5;
      uint32_t v_vm      : 1;
      uint32_t v_funct6  : 6;
    } v_opv1;
    struct {
      uint32_t pad18     :15;
      int32_t  v_simm5   : 5;
      uint32_t v_zimm    :11;
      uint32_t v_bigbit  : 1;
    } v_opv2;
    struct {
      uint32_t pad19     :15;
      uint32_t v_imm5    : 5;
    } v_opv3;
    //vector-LOAD-FP
    struct {
      uint32_t pad20     :12;
      uint32_t v_width   : 3;
      uint32_t pad21     : 5;
      uint32_t v_lumop   : 5;
      uint32_t pad22     : 1;
      uint32_t v_mop     : 3;
      uint32_t v_nf      : 3;
    } vldfp;
    //vector-STORE-FP
    struct {
      uint32_t pad23     : 7;
      uint32_t v_vs3     : 5;
      uint32_t pad24     : 8;
      uint32_t v_sumop   : 5;
    } vstfp;
    //vector-AMO
    struct {
      uint32_t pad25     :26;
      uint32_t v_wd      : 1;
      uint32_t v_amoop   : 5;
    } vamo;
    #endif // CONFIG_RVV_010

    uint32_t val;
  } instr;
} riscv64_ISADecodeInfo;

enum { MODE_U = 0, MODE_S, MODE_H, MODE_M };

int get_data_mmu_state();
#define isa_mmu_state() get_data_mmu_state()



#endif
