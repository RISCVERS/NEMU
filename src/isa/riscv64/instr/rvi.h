def_EHelper(add) { rtl_add(s, ddest, dsrc1, dsrc2); }
def_EHelper(sub) { rtl_sub(s, ddest, dsrc1, dsrc2); }
def_EHelper(sll) { rtl_sll(s, ddest, dsrc1, dsrc2); }
def_EHelper(sra) { rtl_sra(s, ddest, dsrc1, dsrc2); }
def_EHelper(srl) { rtl_srl(s, ddest, dsrc1, dsrc2); }
def_EHelper(slt) { rtl_setrelop(s, RELOP_LT, ddest, dsrc1, dsrc2); }
def_EHelper(sltu) { rtl_setrelop(s, RELOP_LTU, ddest, dsrc1, dsrc2); }
def_EHelper(xor) { rtl_xor(s, ddest, dsrc1, dsrc2); }
def_EHelper(or) { rtl_or(s, ddest, dsrc1, dsrc2); }
def_EHelper(and) { rtl_and(s, ddest, dsrc1, dsrc2); }
def_EHelper(addi) { rtl_addi(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(slli) { rtl_slli(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(srai) { rtl_srai(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(srli) { rtl_srli(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(slti) { rtl_setrelopi(s, RELOP_LT, ddest, dsrc1, id_src2->imm); }
def_EHelper(sltiu) { rtl_setrelopi(s, RELOP_LTU, ddest, dsrc1, id_src2->imm); }
def_EHelper(xori) { rtl_xori(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(ori) { rtl_ori(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(andi) { rtl_andi(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(auipc) { rtl_li(s, ddest, id_src2->imm); }
def_EHelper(lui) { rtl_li(s, ddest, id_src1->imm); }
def_EHelper(addw) { rtl_addw(s, ddest, dsrc1, dsrc2); }
def_EHelper(subw) { rtl_subw(s, ddest, dsrc1, dsrc2); }
def_EHelper(sllw) { rtl_sllw(s, ddest, dsrc1, dsrc2); }
def_EHelper(srlw) { rtl_srlw(s, ddest, dsrc1, dsrc2); }
def_EHelper(sraw) { rtl_sraw(s, ddest, dsrc1, dsrc2); }
def_EHelper(addiw) { rtl_addiw(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(slliw) { rtl_slliw(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(srliw) { rtl_srliw(s, ddest, dsrc1, id_src2->imm); }
def_EHelper(sraiw) { rtl_sraiw(s, ddest, dsrc1, id_src2->imm); }

def_EHelper(jal) {
  rtl_li(s, ddest, id_src2->imm);
  if (ddest == &gpr(1)) {
    ftrace_call(s->pc, id_src1->imm);
  }
  rtl_j(s, id_src1->imm);
}

def_EHelper(jalr) {
  rtl_addi(s, s0, dsrc1, id_src2->imm);
//  IFDEF(CONFIG_ENGINE_INTERPRETER, rtl_andi(s, s0, s0, ~0x1lu));
  rtl_li(s, ddest, s->snpc);
  if (ddest == &gpr(1)) {
    ftrace_call(s->pc, *s0);
  } else if (dsrc1 == &gpr(1)) {
    ftrace_ret(s->pc);
  }
  rtl_jr(s, s0);
}

def_EHelper(beq) { rtl_jrelop(s, RELOP_EQ, dsrc1, dsrc2, id_dest->imm); }
def_EHelper(bne) { rtl_jrelop(s, RELOP_NE, dsrc1, dsrc2, id_dest->imm); }
def_EHelper(blt) { rtl_jrelop(s, RELOP_LT, dsrc1, dsrc2, id_dest->imm); }
def_EHelper(bge) { rtl_jrelop(s, RELOP_GE, dsrc1, dsrc2, id_dest->imm); }
def_EHelper(bltu) { rtl_jrelop(s, RELOP_LTU, dsrc1, dsrc2, id_dest->imm); }
def_EHelper(bgeu) { rtl_jrelop(s, RELOP_GEU, dsrc1, dsrc2, id_dest->imm); }

#define def_ld_template(name, rtl_instr, width, mmu_mode) \
  def_EHelper(name) { concat(rtl_, rtl_instr) (s, ddest, dsrc1, id_src2->imm, width, mmu_mode); }
#define def_st_template(name, rtl_instr, width, mmu_mode) \
  def_EHelper(name) { concat(rtl_, rtl_instr) (s, dsrc2, dsrc1, id_dest->imm, width, mmu_mode); }

#define def_all_ldst(suffix, mmu_mode) \
  def_ld_template(concat(ld , suffix), lm , 8, mmu_mode) \
  def_ld_template(concat(lw , suffix), lms, 4, mmu_mode) \
  def_ld_template(concat(lh , suffix), lms, 2, mmu_mode) \
  def_ld_template(concat(lb , suffix), lms, 1, mmu_mode) \
  def_ld_template(concat(lwu, suffix), lm , 4, mmu_mode) \
  def_ld_template(concat(lhu, suffix), lm , 2, mmu_mode) \
  def_ld_template(concat(lbu, suffix), lm , 1, mmu_mode) \
  def_st_template(concat(sd , suffix), sm , 8, mmu_mode) \
  def_st_template(concat(sw , suffix), sm , 4, mmu_mode) \
  def_st_template(concat(sh , suffix), sm , 2, mmu_mode) \
  def_st_template(concat(sb , suffix), sm , 1, mmu_mode)

def_all_ldst(, MMU_DIRECT)
def_all_ldst(_mmu, MMU_TRANSLATE)

def_EHelper(fence_i) {
  IFNDEF(CONFIG_DIFFTEST_REF_NEMU, difftest_skip_dut(1, 2));
  rtl_hostcall(s, HOSTCALL_PRIV, NULL, NULL, NULL, -1);
  rtl_priv_next(s);
}

def_EHelper(fence) {
  IFNDEF(CONFIG_DIFFTEST_REF_NEMU, difftest_skip_dut(1, 2));
}