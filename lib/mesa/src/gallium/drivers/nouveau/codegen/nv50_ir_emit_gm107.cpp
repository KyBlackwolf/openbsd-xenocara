/*
 * Copyright 2014 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */

#include "codegen/nv50_ir_target_gm107.h"

namespace nv50_ir {

class CodeEmitterGM107 : public CodeEmitter
{
public:
   CodeEmitterGM107(const TargetGM107 *);

   virtual bool emitInstruction(Instruction *);
   virtual uint32_t getMinEncodingSize(const Instruction *) const;

   virtual void prepareEmission(Program *);
   virtual void prepareEmission(Function *);

   inline void setProgramType(Program::Type pType) { progType = pType; }

private:
   const TargetGM107 *targGM107;

   Program::Type progType;

   const Instruction *insn;
   const bool writeIssueDelays;
   uint32_t *data;

private:
   inline void emitField(uint32_t *, int, int, uint32_t);
   inline void emitField(int b, int s, uint32_t v) { emitField(code, b, s, v); }

   inline void emitInsn(uint32_t, bool);
   inline void emitInsn(uint32_t o) { emitInsn(o, true); }
   inline void emitPred();
   inline void emitGPR(int, const Value *);
   inline void emitGPR(int pos) {
      emitGPR(pos, (const Value *)NULL);
   }
   inline void emitGPR(int pos, const ValueRef &ref) {
      emitGPR(pos, ref.get() ? ref.rep() : (const Value *)NULL);
   }
   inline void emitGPR(int pos, const ValueRef *ref) {
      emitGPR(pos, ref ? ref->rep() : (const Value *)NULL);
   }
   inline void emitGPR(int pos, const ValueDef &def) {
      emitGPR(pos, def.get() ? def.rep() : (const Value *)NULL);
   }
   inline void emitSYS(int, const Value *);
   inline void emitSYS(int pos, const ValueRef &ref) {
      emitSYS(pos, ref.get() ? ref.rep() : (const Value *)NULL);
   }
   inline void emitPRED(int, const Value *);
   inline void emitPRED(int pos) {
      emitPRED(pos, (const Value *)NULL);
   }
   inline void emitPRED(int pos, const ValueRef &ref) {
      emitPRED(pos, ref.get() ? ref.rep() : (const Value *)NULL);
   }
   inline void emitPRED(int pos, const ValueDef &def) {
      emitPRED(pos, def.get() ? def.rep() : (const Value *)NULL);
   }
   inline void emitADDR(int, int, int, int, const ValueRef &);
   inline void emitCBUF(int, int, int, int, int, const ValueRef &);
   inline bool longIMMD(const ValueRef &);
   inline void emitIMMD(int, int, const ValueRef &);

   void emitCond3(int, CondCode);
   void emitCond4(int, CondCode);
   void emitCond5(int pos, CondCode cc) { emitCond4(pos, cc); }
   inline void emitO(int);
   inline void emitP(int);
   inline void emitSAT(int);
   inline void emitCC(int);
   inline void emitX(int);
   inline void emitABS(int, const ValueRef &);
   inline void emitNEG(int, const ValueRef &);
   inline void emitNEG2(int, const ValueRef &, const ValueRef &);
   inline void emitFMZ(int, int);
   inline void emitRND(int, RoundMode, int);
   inline void emitRND(int pos) {
      emitRND(pos, insn->rnd, -1);
   }
   inline void emitPDIV(int);
   inline void emitINV(int, const ValueRef &);

   void emitEXIT();
   void emitBRA();
   void emitCAL();
   void emitPCNT();
   void emitCONT();
   void emitPBK();
   void emitBRK();
   void emitPRET();
   void emitRET();
   void emitSSY();
   void emitSYNC();
   void emitSAM();
   void emitRAM();

   void emitMOV();
   void emitS2R();
   void emitF2F();
   void emitF2I();
   void emitI2F();
   void emitI2I();
   void emitSHFL();

   void emitDADD();
   void emitDMUL();
   void emitDFMA();
   void emitDMNMX();
   void emitDSET();
   void emitDSETP();

   void emitFADD();
   void emitFMUL();
   void emitFFMA();
   void emitMUFU();
   void emitFMNMX();
   void emitRRO();
   void emitFCMP();
   void emitFSET();
   void emitFSETP();
   void emitFSWZADD();

   void emitLOP();
   void emitNOT();
   void emitIADD();
   void emitIMUL();
   void emitIMAD();
   void emitIMNMX();
   void emitICMP();
   void emitISET();
   void emitISETP();
   void emitSHL();
   void emitSHR();
   void emitPOPC();
   void emitBFI();
   void emitBFE();
   void emitFLO();

   void emitLDSTs(int, DataType);
   void emitLDSTc(int);
   void emitLDC();
   void emitLDL();
   void emitLDS();
   void emitLD();
   void emitSTL();
   void emitSTS();
   void emitST();
   void emitALD();
   void emitAST();
   void emitISBERD();
   void emitAL2P();
   void emitIPA();

   void emitPIXLD();

   void emitTEXs(int);
   void emitTEX();
   void emitTLD();
   void emitTLD4();
   void emitTXD();
   void emitTXQ();
   void emitTMML();
   void emitDEPBAR();

   void emitNOP();
   void emitKIL();
   void emitOUT();
};

/*******************************************************************************
 * general instruction layout/fields
 ******************************************************************************/

void
CodeEmitterGM107::emitField(uint32_t *data, int b, int s, uint32_t v)
{
   if (b >= 0) {
      uint32_t m = ((1ULL << s) - 1);
      uint64_t d = (uint64_t)(v & m) << b;
      assert(!(v & ~m) || (v & ~m) == ~m);
      data[1] |= d >> 32;
      data[0] |= d;
   }
}

void
CodeEmitterGM107::emitPred()
{
   if (insn->predSrc >= 0) {
      emitField(16, 3, insn->getSrc(insn->predSrc)->rep()->reg.data.id);
      emitField(19, 1, insn->cc == CC_NOT_P);
   } else {
      emitField(16, 3, 7);
   }
}

void
CodeEmitterGM107::emitInsn(uint32_t hi, bool pred)
{
   code[0] = 0x00000000;
   code[1] = hi;
   if (pred)
      emitPred();
}

void
CodeEmitterGM107::emitGPR(int pos, const Value *val)
{
   emitField(pos, 8, val ? val->reg.data.id : 255);
}

void
CodeEmitterGM107::emitSYS(int pos, const Value *val)
{
   int id = val ? val->reg.data.id : -1;

   switch (id) {
   case SV_LANEID         : id = 0x00; break;
   case SV_VERTEX_COUNT   : id = 0x10; break;
   case SV_INVOCATION_ID  : id = 0x11; break;
   case SV_INVOCATION_INFO: id = 0x1d; break;
   default:
      assert(!"invalid system value");
      id = 0;
      break;
   }

   emitField(pos, 8, id);
}

void
CodeEmitterGM107::emitPRED(int pos, const Value *val)
{
   emitField(pos, 3, val ? val->reg.data.id : 7);
}

void
CodeEmitterGM107::emitADDR(int gpr, int off, int len, int shr,
                           const ValueRef &ref)
{
   const Value *v = ref.get();
   assert(!(v->reg.data.offset & ((1 << shr) - 1)));
   if (gpr >= 0)
      emitGPR(gpr, ref.getIndirect(0));
   emitField(off, len, v->reg.data.offset >> shr);
}

void
CodeEmitterGM107::emitCBUF(int buf, int gpr, int off, int len, int shr,
                           const ValueRef &ref)
{
   const Value *v = ref.get();
   const Symbol *s = v->asSym();

   assert(!(s->reg.data.offset & ((1 << shr) - 1)));

   emitField(buf,  5, v->reg.fileIndex);
   if (gpr >= 0)
      emitGPR(gpr, ref.getIndirect(0));
   emitField(off, 16, s->reg.data.offset >> shr);
}

bool
CodeEmitterGM107::longIMMD(const ValueRef &ref)
{
   if (ref.getFile() == FILE_IMMEDIATE) {
      const ImmediateValue *imm = ref.get()->asImm();
      if (isFloatType(insn->sType)) {
         if ((imm->reg.data.u32 & 0x00000fff) != 0x00000000)
            return true;
      } else {
         if ((imm->reg.data.u32 & 0xfff00000) != 0x00000000 &&
             (imm->reg.data.u32 & 0xfff00000) != 0xfff00000)
            return true;
      }
   }
   return false;
}

void
CodeEmitterGM107::emitIMMD(int pos, int len, const ValueRef &ref)
{
   const ImmediateValue *imm = ref.get()->asImm();
   uint32_t val = imm->reg.data.u32;

   if (len == 19) {
      if (isFloatType(insn->sType)) {
         assert(!(val & 0x00000fff));
         val >>= 12;
      }
      assert(!(val & 0xfff00000) || (val & 0xfff00000) == 0xfff00000);
      emitField( 56,   1, (val & 0x80000) >> 19);
      emitField(pos, len, (val & 0x7ffff));
   } else {
      emitField(pos, len, val);
   }
}

/*******************************************************************************
 * modifiers
 ******************************************************************************/

void
CodeEmitterGM107::emitCond3(int pos, CondCode code)
{
   int data = 0;

   switch (code) {
   case CC_FL : data = 0x00; break;
   case CC_LTU:
   case CC_LT : data = 0x01; break;
   case CC_EQU:
   case CC_EQ : data = 0x02; break;
   case CC_LEU:
   case CC_LE : data = 0x03; break;
   case CC_GTU:
   case CC_GT : data = 0x04; break;
   case CC_NEU:
   case CC_NE : data = 0x05; break;
   case CC_GEU:
   case CC_GE : data = 0x06; break;
   case CC_TR : data = 0x07; break;
   default:
      assert(!"invalid cond3");
      break;
   }

   emitField(pos, 3, data);
}

void
CodeEmitterGM107::emitCond4(int pos, CondCode code)
{
   int data = 0;

   switch (code) {
   case CC_FL: data = 0x00; break;
   case CC_LT: data = 0x01; break;
   case CC_EQ: data = 0x02; break;
   case CC_LE: data = 0x03; break;
   case CC_GT: data = 0x04; break;
   case CC_NE: data = 0x05; break;
   case CC_GE: data = 0x06; break;
//   case CC_NUM: data = 0x07; break;
//   case CC_NAN: data = 0x08; break;
   case CC_LTU: data = 0x09; break;
   case CC_EQU: data = 0x0a; break;
   case CC_LEU: data = 0x0b; break;
   case CC_GTU: data = 0x0c; break;
   case CC_NEU: data = 0x0d; break;
   case CC_GEU: data = 0x0e; break;
   case CC_TR:  data = 0x0f; break;
   default:
      assert(!"invalid cond4");
      break;
   }

   emitField(pos, 4, data);
}

void
CodeEmitterGM107::emitO(int pos)
{
   emitField(pos, 1, insn->getSrc(0)->reg.file == FILE_SHADER_OUTPUT);
}

void
CodeEmitterGM107::emitP(int pos)
{
   emitField(pos, 1, insn->perPatch);
}

void
CodeEmitterGM107::emitSAT(int pos)
{
   emitField(pos, 1, insn->saturate);
}

void
CodeEmitterGM107::emitCC(int pos)
{
   emitField(pos, 1, insn->defExists(1));
}

void
CodeEmitterGM107::emitX(int pos)
{
   emitField(pos, 1, insn->flagsSrc >= 0);
}

void
CodeEmitterGM107::emitABS(int pos, const ValueRef &ref)
{
   emitField(pos, 1, ref.mod.abs());
}

void
CodeEmitterGM107::emitNEG(int pos, const ValueRef &ref)
{
   emitField(pos, 1, ref.mod.neg());
}

void
CodeEmitterGM107::emitNEG2(int pos, const ValueRef &a, const ValueRef &b)
{
   emitField(pos, 1, a.mod.neg() ^ b.mod.neg());
}

void
CodeEmitterGM107::emitFMZ(int pos, int len)
{
   emitField(pos, len, insn->dnz << 1 | insn->ftz);
}

void
CodeEmitterGM107::emitRND(int rmp, RoundMode rnd, int rip)
{
   int rm = 0, ri = 0;
   switch (rnd) {
   case ROUND_NI: ri = 1;
   case ROUND_N : rm = 0; break;
   case ROUND_MI: ri = 1;
   case ROUND_M : rm = 1; break;
   case ROUND_PI: ri = 1;
   case ROUND_P : rm = 2; break;
   case ROUND_ZI: ri = 1;
   case ROUND_Z : rm = 3; break;
   default:
      assert(!"invalid round mode");
      break;
   }
   emitField(rip, 1, ri);
   emitField(rmp, 2, rm);
}

void
CodeEmitterGM107::emitPDIV(int pos)
{
   assert(insn->postFactor >= -3 && insn->postFactor <= 3);
   if (insn->postFactor > 0)
      emitField(pos, 3, 7 - insn->postFactor);
   else
      emitField(pos, 3, 0 - insn->postFactor);
}

void
CodeEmitterGM107::emitINV(int pos, const ValueRef &ref)
{
   emitField(pos, 1, !!(ref.mod & Modifier(NV50_IR_MOD_NOT)));
}

/*******************************************************************************
 * control flow
 ******************************************************************************/

void
CodeEmitterGM107::emitEXIT()
{
   emitInsn (0xe3000000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitBRA()
{
   const FlowInstruction *insn = this->insn->asFlow();
   int gpr = -1;

   if (insn->indirect) {
      if (insn->absolute)
         emitInsn(0xe2000000); // JMX
      else
         emitInsn(0xe2500000); // BRX
      gpr = 0x08;
   } else {
      if (insn->absolute)
         emitInsn(0xe2100000); // JMP
      else
         emitInsn(0xe2400000); // BRA
      emitField(0x07, 1, insn->allWarp);
   }

   emitField(0x06, 1, insn->limit);
   emitCond5(0x00, CC_TR);

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      int32_t pos = insn->target.bb->binPos;
      if (writeIssueDelays && !(pos & 0x1f))
         pos += 8;
      if (!insn->absolute)
         emitField(0x14, 24, pos - (codeSize + 8));
      else
         emitField(0x14, 32, pos);
   } else {
      emitCBUF (0x24, gpr, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitCAL()
{
   const FlowInstruction *insn = this->insn->asFlow();

   if (insn->absolute) {
      emitInsn(0xe2200000, 0); // JCAL
   } else {
      emitInsn(0xe2600000, 0); // CAL
   }

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      if (!insn->absolute)
         emitField(0x14, 24, insn->target.bb->binPos - (codeSize + 8));
      else {
         if (insn->builtin) {
            int pcAbs = targGM107->getBuiltinOffset(insn->target.builtin);
            addReloc(RelocEntry::TYPE_BUILTIN, 0, pcAbs, 0xfff00000,  20);
            addReloc(RelocEntry::TYPE_BUILTIN, 1, pcAbs, 0x000fffff, -12);
         } else {
            emitField(0x14, 32, insn->target.bb->binPos);
         }
      }
   } else {
      emitCBUF (0x24, -1, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitPCNT()
{
   const FlowInstruction *insn = this->insn->asFlow();

   emitInsn(0xe2b00000, 0);

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      emitField(0x14, 24, insn->target.bb->binPos - (codeSize + 8));
   } else {
      emitCBUF (0x24, -1, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitCONT()
{
   emitInsn (0xe3500000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitPBK()
{
   const FlowInstruction *insn = this->insn->asFlow();

   emitInsn(0xe2a00000, 0);

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      emitField(0x14, 24, insn->target.bb->binPos - (codeSize + 8));
   } else {
      emitCBUF (0x24, -1, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitBRK()
{
   emitInsn (0xe3400000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitPRET()
{
   const FlowInstruction *insn = this->insn->asFlow();

   emitInsn(0xe2700000, 0);

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      emitField(0x14, 24, insn->target.bb->binPos - (codeSize + 8));
   } else {
      emitCBUF (0x24, -1, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitRET()
{
   emitInsn (0xe3200000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitSSY()
{
   const FlowInstruction *insn = this->insn->asFlow();

   emitInsn(0xe2900000, 0);

   if (!insn->srcExists(0) || insn->src(0).getFile() != FILE_MEMORY_CONST) {
      emitField(0x14, 24, insn->target.bb->binPos - (codeSize + 8));
   } else {
      emitCBUF (0x24, -1, 20, 16, 0, insn->src(0));
      emitField(0x05, 1, 1);
   }
}

void
CodeEmitterGM107::emitSYNC()
{
   emitInsn (0xf0f80000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitSAM()
{
   emitInsn(0xe3700000, 0);
}

void
CodeEmitterGM107::emitRAM()
{
   emitInsn(0xe3800000, 0);
}

/*******************************************************************************
 * predicate/cc
 ******************************************************************************/

/*******************************************************************************
 * movement / conversion
 ******************************************************************************/

void
CodeEmitterGM107::emitMOV()
{
   if ( insn->src(0).getFile() != FILE_IMMEDIATE ||
       (insn->sType != TYPE_F32 && !longIMMD(insn->src(0)))) {
      switch (insn->src(0).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c980000);
         emitGPR (0x14, insn->src(0));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c980000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38980000);
         emitIMMD(0x14, 19, insn->src(0));
         break;
      default:
         assert(!"bad src file");
         break;
      }
      emitField(0x27, 4, insn->lanes);
   } else {
      emitInsn (0x01000000);
      emitIMMD (0x14, 32, insn->src(0));
      emitField(0x0c, 4, insn->lanes);
   }

   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitS2R()
{
   emitInsn(0xf0c80000);
   emitSYS (0x14, insn->src(0));
   emitGPR (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitF2F()
{
   RoundMode rnd = insn->rnd;

   switch (insn->op) {
   case OP_FLOOR: rnd = ROUND_MI; break;
   case OP_CEIL : rnd = ROUND_PI; break;
   case OP_TRUNC: rnd = ROUND_ZI; break;
   default:
      break;
   }

   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5ca80000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4ca80000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38a80000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src0 file");
      break;
   }

   emitField(0x32, 1, (insn->op == OP_SAT) || insn->saturate);
   emitField(0x31, 1, (insn->op == OP_ABS) || insn->src(0).mod.abs());
   emitCC   (0x2f);
   emitField(0x2d, 1, (insn->op == OP_NEG) || insn->src(0).mod.neg());
   emitFMZ  (0x2c, 1);
   emitRND  (0x27, rnd, 0x2a);
   emitField(0x0a, 2, util_logbase2(typeSizeof(insn->sType)));
   emitField(0x08, 2, util_logbase2(typeSizeof(insn->dType)));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitF2I()
{
   RoundMode rnd = insn->rnd;

   switch (insn->op) {
   case OP_FLOOR: rnd = ROUND_M; break;
   case OP_CEIL : rnd = ROUND_P; break;
   case OP_TRUNC: rnd = ROUND_Z; break;
   default:
      break;
   }

   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5cb00000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4cb00000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38b00000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src0 file");
      break;
   }

   emitField(0x31, 1, (insn->op == OP_ABS) || insn->src(0).mod.abs());
   emitCC   (0x2f);
   emitField(0x2d, 1, (insn->op == OP_NEG) || insn->src(0).mod.neg());
   emitFMZ  (0x2c, 1);
   emitRND  (0x27, rnd, 0x2a);
   emitField(0x0c, 1, isSignedType(insn->dType));
   emitField(0x0a, 2, util_logbase2(typeSizeof(insn->sType)));
   emitField(0x08, 2, util_logbase2(typeSizeof(insn->dType)));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitI2F()
{
   RoundMode rnd = insn->rnd;

   switch (insn->op) {
   case OP_FLOOR: rnd = ROUND_M; break;
   case OP_CEIL : rnd = ROUND_P; break;
   case OP_TRUNC: rnd = ROUND_Z; break;
   default:
      break;
   }

   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5cb80000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4cb80000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38b80000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src0 file");
      break;
   }

   emitField(0x31, 1, (insn->op == OP_ABS) || insn->src(0).mod.abs());
   emitCC   (0x2f);
   emitField(0x2d, 1, (insn->op == OP_NEG) || insn->src(0).mod.neg());
   emitField(0x29, 2, insn->subOp);
   emitRND  (0x27, rnd, -1);
   emitField(0x0d, 1, isSignedType(insn->sType));
   emitField(0x0a, 2, util_logbase2(typeSizeof(insn->sType)));
   emitField(0x08, 2, util_logbase2(typeSizeof(insn->dType)));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitI2I()
{
   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5ce00000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4ce00000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38e00000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src0 file");
      break;
   }

   emitSAT  (0x32);
   emitField(0x31, 1, (insn->op == OP_ABS) || insn->src(0).mod.abs());
   emitCC   (0x2f);
   emitField(0x2d, 1, (insn->op == OP_NEG) || insn->src(0).mod.neg());
   emitField(0x29, 2, insn->subOp);
   emitField(0x0d, 1, isSignedType(insn->sType));
   emitField(0x0c, 1, isSignedType(insn->dType));
   emitField(0x0a, 2, util_logbase2(typeSizeof(insn->sType)));
   emitField(0x08, 2, util_logbase2(typeSizeof(insn->dType)));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitSHFL()
{
   int type = 0;

   emitInsn (0xef100000);

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitGPR(0x14, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitIMMD(0x14, 5, insn->src(1));
      type |= 1;
      break;
   default:
      assert(!"invalid src1 file");
      break;
   }

   /*XXX: what is this arg? hardcode immediate for now */
   emitField(0x22, 13, 0x1c03);
   type |= 2;

   emitPRED (0x30);
   emitField(0x1e, 2, insn->subOp);
   emitField(0x1c, 2, type);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/*******************************************************************************
 * double
 ******************************************************************************/

void
CodeEmitterGM107::emitDADD()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c700000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c700000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38700000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }
   emitABS(0x31, insn->src(1));
   emitNEG(0x30, insn->src(0));
   emitCC (0x2f);
   emitABS(0x2e, insn->src(0));
   emitNEG(0x2d, insn->src(1));

   if (insn->op == OP_SUB)
      code[1] ^= 0x00002000;

   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDMUL()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c800000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c800000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38800000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitNEG2(0x30, insn->src(0), insn->src(1));
   emitCC  (0x2f);
   emitRND (0x27);
   emitGPR (0x08, insn->src(0));
   emitGPR (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDFMA()
{
   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5b700000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4b700000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x36700000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x53700000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }

   emitRND (0x32);
   emitNEG (0x31, insn->src(2));
   emitNEG2(0x30, insn->src(0), insn->src(1));
   emitCC  (0x2f);
   emitGPR (0x08, insn->src(0));
   emitGPR (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDMNMX()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c500000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c500000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38500000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitABS  (0x31, insn->src(1));
   emitNEG  (0x30, insn->src(0));
   emitCC   (0x2f);
   emitABS  (0x2e, insn->src(0));
   emitNEG  (0x2d, insn->src(1));
   emitField(0x2a, 1, insn->op == OP_MAX);
   emitPRED (0x27);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDSET()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x59000000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x49000000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x32000000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitABS  (0x36, insn->src(0));
   emitNEG  (0x35, insn->src(1));
   emitField(0x34, 1, insn->dType == TYPE_F32);
   emitCond4(0x30, insn->setCond);
   emitCC   (0x2f);
   emitABS  (0x2c, insn->src(1));
   emitNEG  (0x2b, insn->src(0));
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDSETP()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5b800000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4b800000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x36800000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitCond4(0x30, insn->setCond);
   emitABS  (0x2c, insn->src(1));
   emitNEG  (0x2b, insn->src(0));
   emitGPR  (0x08, insn->src(0));
   emitABS  (0x07, insn->src(0));
   emitNEG  (0x06, insn->src(1));
   emitPRED (0x03, insn->def(0));
   if (insn->defExists(1))
      emitPRED(0x00, insn->def(1));
   else
      emitPRED(0x00);
}

/*******************************************************************************
 * float
 ******************************************************************************/

void
CodeEmitterGM107::emitFADD()
{
   if (!longIMMD(insn->src(1))) {
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c580000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c580000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38580000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitSAT(0x32);
      emitABS(0x31, insn->src(1));
      emitNEG(0x30, insn->src(0));
      emitCC (0x2f);
      emitABS(0x2e, insn->src(0));
      emitNEG(0x2d, insn->src(1));
      emitFMZ(0x2c, 1);
   } else {
      emitInsn(0x08000000);
      emitABS(0x39, insn->src(1));
      emitNEG(0x38, insn->src(0));
      emitFMZ(0x37, 1);
      emitABS(0x36, insn->src(0));
      emitNEG(0x35, insn->src(1));
      emitCC  (0x34);
      emitIMMD(0x14, 32, insn->src(1));
   }

   if (insn->op == OP_SUB)
      code[1] ^= 0x00002000;

   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFMUL()
{
   if (!longIMMD(insn->src(1))) {
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c680000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c680000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38680000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitSAT (0x32);
      emitNEG2(0x30, insn->src(0), insn->src(1));
      emitCC  (0x2f);
      emitFMZ (0x2c, 2);
      emitPDIV(0x29);
      emitRND (0x27);
   } else {
      emitInsn(0x1e000000);
      emitSAT (0x37);
      emitFMZ (0x35, 2);
      emitCC  (0x34);
      emitIMMD(0x14, 32, insn->src(1));
      if (insn->src(0).mod.neg() ^ insn->src(1).mod.neg())
         code[1] ^= 0x00080000; /* flip immd sign bit */
   }

   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFFMA()
{
   /*XXX: ffma32i exists, but not using it as third src overlaps dst */
   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x59800000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x49800000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x32800000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x51800000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }
   emitRND (0x33);
   emitSAT (0x32);
   emitNEG (0x31, insn->src(2));
   emitNEG2(0x30, insn->src(0), insn->src(1));
   emitCC  (0x2f);

   emitFMZ(0x35, 2);
   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitMUFU()
{
   int mufu = 0;

   switch (insn->op) {
   case OP_COS: mufu = 0; break;
   case OP_SIN: mufu = 1; break;
   case OP_EX2: mufu = 2; break;
   case OP_LG2: mufu = 3; break;
   case OP_RCP: mufu = 4 + 2 * insn->subOp; break;
   case OP_RSQ: mufu = 5 + 2 * insn->subOp; break;
   default:
      assert(!"invalid mufu");
      break;
   }

   emitInsn (0x50800000);
   emitSAT  (0x32);
   emitNEG  (0x30, insn->src(0));
   emitABS  (0x2e, insn->src(0));
   emitField(0x14, 3, mufu);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFMNMX()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c600000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c600000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38600000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x2a, 1, insn->op == OP_MAX);
   emitPRED (0x27);

   emitABS(0x31, insn->src(1));
   emitNEG(0x30, insn->src(0));
   emitCC (0x2f);
   emitABS(0x2e, insn->src(0));
   emitNEG(0x2d, insn->src(1));
   emitFMZ(0x2c, 1);
   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitRRO()
{
   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c900000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c900000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38900000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src file");
      break;
   }

   emitABS  (0x31, insn->src(0));
   emitNEG  (0x2d, insn->src(0));
   emitField(0x27, 1, insn->op == OP_PREEX2);
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFCMP()
{
   const CmpInstruction *insn = this->insn->asCmp();
   CondCode cc = insn->setCond;

   if (insn->src(2).mod.neg())
      cc = reverseCondCode(cc);

   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5ba00000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4ba00000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x36a00000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x53a00000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }

   emitCond4(0x30, cc);
   emitFMZ  (0x2f, 1);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFSET()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x58000000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x48000000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x30000000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitFMZ  (0x37, 1);
   emitABS  (0x36, insn->src(0));
   emitNEG  (0x35, insn->src(1));
   emitField(0x34, 1, insn->dType == TYPE_F32);
   emitCond4(0x30, insn->setCond);
   emitCC   (0x2f);
   emitABS  (0x2c, insn->src(1));
   emitNEG  (0x2b, insn->src(0));
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFSETP()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5bb00000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4bb00000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x36b00000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitCond4(0x30, insn->setCond);
   emitFMZ  (0x2f, 1);
   emitABS  (0x2c, insn->src(1));
   emitNEG  (0x2b, insn->src(0));
   emitGPR  (0x08, insn->src(0));
   emitABS  (0x07, insn->src(0));
   emitNEG  (0x06, insn->src(1));
   emitPRED (0x03, insn->def(0));
   if (insn->defExists(1))
      emitPRED(0x00, insn->def(1));
   else
      emitPRED(0x00);
}

void
CodeEmitterGM107::emitFSWZADD()
{
   emitInsn (0x50f80000);
   emitCC   (0x2f);
   emitFMZ  (0x2c, 1);
   emitRND  (0x27);
   emitField(0x26, 1, insn->lanes); /* abused for .ndv */
   emitField(0x1c, 8, insn->subOp);
   emitGPR  (0x14, insn->src(1));
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/*******************************************************************************
 * integer
 ******************************************************************************/

void
CodeEmitterGM107::emitLOP()
{
   int lop = 0;

   switch (insn->op) {
   case OP_AND: lop = 0; break;
   case OP_OR : lop = 1; break;
   case OP_XOR: lop = 2; break;
   default:
      assert(!"invalid lop");
      break;
   }

   if (!longIMMD(insn->src(1))) {
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c400000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c400000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38400000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitPRED (0x30);
      emitField(0x29, 2, lop);
      emitINV  (0x28, insn->src(1));
      emitINV  (0x27, insn->src(0));
   } else {
      emitInsn (0x04000000);
      emitINV  (0x38, insn->src(1));
      emitINV  (0x37, insn->src(0));
      emitField(0x35, 2, lop);
      emitIMMD (0x14, 32, insn->src(1));
   }

   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/* special-case of emitLOP(): lop pass_b dst 0 ~src */
void
CodeEmitterGM107::emitNOT()
{
   if (!longIMMD(insn->src(0))) {
      switch (insn->src(0).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c400700);
         emitGPR (0x14, insn->src(0));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c400700);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38400700);
         emitIMMD(0x14, 19, insn->src(0));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitPRED (0x30);
   } else {
      emitInsn (0x05600000);
      emitIMMD (0x14, 32, insn->src(1));
   }

   emitGPR(0x08);
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitIADD()
{
   if (!longIMMD(insn->src(1))) {
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c100000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c100000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38100000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitSAT(0x32);
      emitNEG(0x31, insn->src(0));
      emitNEG(0x30, insn->src(1));
      emitCC (0x2f);
   } else {
      emitInsn(0x1c000000);
      emitSAT (0x36);
      emitCC  (0x34);
      emitIMMD(0x14, 32, insn->src(1));
   }

   if (insn->op == OP_SUB)
      code[1] ^= 0x00010000;

   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitIMUL()
{
   if (!longIMMD(insn->src(1))) {
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5c380000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4c380000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x38380000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitCC   (0x2f);
      emitField(0x29, 1, isSignedType(insn->sType));
      emitField(0x28, 1, isSignedType(insn->dType));
      emitField(0x27, 1, insn->subOp == NV50_IR_SUBOP_MUL_HIGH);
   } else {
      emitInsn (0x1f000000);
      emitField(0x37, 1, isSignedType(insn->sType));
      emitField(0x36, 1, isSignedType(insn->dType));
      emitField(0x35, 1, insn->subOp == NV50_IR_SUBOP_MUL_HIGH);
      emitCC   (0x34);
      emitIMMD (0x14, 32, insn->src(1));
   }

   emitGPR(0x08, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitIMAD()
{
   /*XXX: imad32i exists, but not using it as third src overlaps dst */
   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5a000000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4a000000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x34000000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x52000000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }

   emitField(0x36, 1, insn->subOp == NV50_IR_SUBOP_MUL_HIGH);
   emitField(0x35, 1, isSignedType(insn->sType));
   emitNEG  (0x34, insn->src(2));
   emitNEG2 (0x33, insn->src(0), insn->src(1));
   emitSAT  (0x32);
   emitX    (0x31);
   emitField(0x30, 1, isSignedType(insn->dType));
   emitCC   (0x2f);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitIMNMX()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c200000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c200000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38200000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x30, 1, isSignedType(insn->dType));
   emitCC   (0x2f);
   emitField(0x2a, 1, insn->op == OP_MAX);
   emitPRED (0x27);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitICMP()
{
   const CmpInstruction *insn = this->insn->asCmp();
   CondCode cc = insn->setCond;

   if (insn->src(2).mod.neg())
      cc = reverseCondCode(cc);

   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5b400000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4b400000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x36400000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x53400000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }

   emitCond3(0x31, cc);
   emitField(0x30, 1, isSignedType(insn->sType));
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitISET()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5b500000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4b500000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x36500000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitCond3(0x31, insn->setCond);
   emitField(0x30, 1, isSignedType(insn->sType));
   emitCC   (0x2f);
   emitField(0x2c, 1, insn->dType == TYPE_F32);
   emitX    (0x2b);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitISETP()
{
   const CmpInstruction *insn = this->insn->asCmp();

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5b600000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4b600000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x36600000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   if (insn->op != OP_SET) {
      switch (insn->op) {
      case OP_SET_AND: emitField(0x2d, 2, 0); break;
      case OP_SET_OR : emitField(0x2d, 2, 1); break;
      case OP_SET_XOR: emitField(0x2d, 2, 2); break;
      default:
         assert(!"invalid set op");
         break;
      }
      emitPRED(0x27, insn->src(2));
   } else {
      emitPRED(0x27);
   }

   emitCond3(0x31, insn->setCond);
   emitField(0x30, 1, isSignedType(insn->sType));
   emitX    (0x2b);
   emitGPR  (0x08, insn->src(0));
   emitPRED (0x03, insn->def(0));
   if (insn->defExists(1))
      emitPRED(0x00, insn->def(1));
   else
      emitPRED(0x00);
}

void
CodeEmitterGM107::emitSHL()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c480000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c480000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38480000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitCC   (0x2f);
   emitX    (0x2b);
   emitField(0x27, 1, insn->subOp == NV50_IR_SUBOP_SHIFT_WRAP);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitSHR()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c280000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c280000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38280000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x30, 1, isSignedType(insn->dType));
   emitCC   (0x2f);
   emitX    (0x2c);
   emitField(0x27, 1, insn->subOp == NV50_IR_SUBOP_SHIFT_WRAP);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitPOPC()
{
   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c080000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c080000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38080000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitINV(0x28, insn->src(0));
   emitGPR(0x00, insn->def(0));
}

void
CodeEmitterGM107::emitBFI()
{
   switch(insn->src(2).getFile()) {
   case FILE_GPR:
      switch (insn->src(1).getFile()) {
      case FILE_GPR:
         emitInsn(0x5bf00000);
         emitGPR (0x14, insn->src(1));
         break;
      case FILE_MEMORY_CONST:
         emitInsn(0x4bf00000);
         emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
         break;
      case FILE_IMMEDIATE:
         emitInsn(0x36f00000);
         emitIMMD(0x14, 19, insn->src(1));
         break;
      default:
         assert(!"bad src1 file");
         break;
      }
      emitGPR (0x27, insn->src(2));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x53f00000);
      emitGPR (0x27, insn->src(1));
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(2));
      break;
   default:
      assert(!"bad src2 file");
      break;
   }

   emitCC   (0x2f);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitBFE()
{
   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c000000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c000000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38000000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x30, 1, isSignedType(insn->dType));
   emitCC   (0x2f);
   emitField(0x28, 1, insn->subOp == NV50_IR_SUBOP_EXTBF_REV);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitFLO()
{
   switch (insn->src(0).getFile()) {
   case FILE_GPR:
      emitInsn(0x5c300000);
      emitGPR (0x14, insn->src(0));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0x4c300000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(0));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0x38300000);
      emitIMMD(0x14, 19, insn->src(0));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x30, 1, isSignedType(insn->dType));
   emitCC   (0x2f);
   emitField(0x29, 1, insn->subOp == NV50_IR_SUBOP_BFIND_SAMT);
   emitINV  (0x28, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/*******************************************************************************
 * memory
 ******************************************************************************/

void
CodeEmitterGM107::emitLDSTs(int pos, DataType type)
{
   int data = 0;

   switch (typeSizeof(type)) {
   case  1: data = isSignedType(type) ? 1 : 0; break;
   case  2: data = isSignedType(type) ? 3 : 2; break;
   case  4: data = 4; break;
   case  8: data = 5; break;
   case 16: data = 6; break;
   default:
      assert(!"bad type");
      break;
   }

   emitField(pos, 3, data);
}

void
CodeEmitterGM107::emitLDSTc(int pos)
{
   int mode = 0;

   switch (insn->cache) {
   case CACHE_CA: mode = 0; break;
   case CACHE_CG: mode = 1; break;
   case CACHE_CS: mode = 2; break;
   case CACHE_CV: mode = 3; break;
   default:
      assert(!"invalid caching mode");
      break;
   }

   emitField(pos, 2, mode);
}

void
CodeEmitterGM107::emitLDC()
{
   emitInsn (0xef900000);
   emitLDSTs(0x30, insn->dType);
   emitField(0x2c, 2, insn->subOp);
   emitCBUF (0x24, 0x08, 0x14, 16, 0, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitLDL()
{
   emitInsn (0xef400000);
   emitLDSTs(0x30, insn->dType);
   emitLDSTc(0x2c);
   emitADDR (0x08, 0x14, 24, 0, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitLDS()
{
   emitInsn (0xef480000);
   emitLDSTs(0x30, insn->dType);
   emitADDR (0x08, 0x14, 24, 0, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitLD()
{
   emitInsn (0x80000000);
   emitPRED (0x3a);
   emitLDSTc(0x38);
   emitLDSTs(0x35, insn->dType);
   emitADDR (0x08, 0x14, 32, 0, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitSTL()
{
   emitInsn (0xef500000);
   emitLDSTs(0x30, insn->dType);
   emitLDSTc(0x2c);
   emitADDR (0x08, 0x14, 24, 0, insn->src(0));
   emitGPR  (0x00, insn->src(1));
}

void
CodeEmitterGM107::emitSTS()
{
   emitInsn (0xef580000);
   emitLDSTs(0x30, insn->dType);
   emitADDR (0x08, 0x14, 24, 0, insn->src(0));
   emitGPR  (0x00, insn->src(1));
}

void
CodeEmitterGM107::emitST()
{
   emitInsn (0xa0000000);
   emitPRED (0x3a);
   emitLDSTc(0x38);
   emitLDSTs(0x35, insn->dType);
   emitADDR (0x08, 0x14, 32, 0, insn->src(0));
   emitGPR  (0x00, insn->src(1));
}

void
CodeEmitterGM107::emitALD()
{
   emitInsn (0xefd80000);
   emitField(0x2f, 2, (insn->getDef(0)->reg.size / 4) - 1);
   emitGPR  (0x27, insn->src(0).getIndirect(1));
   emitO    (0x20);
   emitP    (0x1f);
   emitADDR (0x08, 20, 10, 0, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitAST()
{
   emitInsn (0xeff00000);
   emitField(0x2f, 2, (typeSizeof(insn->dType) / 4) - 1);
   emitGPR  (0x27, insn->src(0).getIndirect(1));
   emitP    (0x1f);
   emitADDR (0x08, 20, 10, 0, insn->src(0));
   emitGPR  (0x00, insn->src(1));
}

void
CodeEmitterGM107::emitISBERD()
{
   emitInsn(0xefd00000);
   emitGPR (0x08, insn->src(0));
   emitGPR (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitAL2P()
{
   emitInsn (0xefa00000);
   emitField(0x2f, 2, (insn->getDef(0)->reg.size / 4) - 1);
   emitO    (0x20);
   emitField(0x14, 11, insn->src(0).get()->reg.data.offset);
   emitGPR  (0x08, insn->src(0).getIndirect(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitIPA()
{
   int ipam = 0, ipas = 0;

   switch (insn->getInterpMode()) {
   case NV50_IR_INTERP_LINEAR     : ipam = 0; break;
   case NV50_IR_INTERP_PERSPECTIVE: ipam = 1; break;
   case NV50_IR_INTERP_FLAT       : ipam = 2; break;
   case NV50_IR_INTERP_SC         : ipam = 3; break;
   default:
      assert(!"invalid ipa mode");
      break;
   }

   switch (insn->getSampleMode()) {
   case NV50_IR_INTERP_DEFAULT : ipas = 0; break;
   case NV50_IR_INTERP_CENTROID: ipas = 1; break;
   case NV50_IR_INTERP_OFFSET  : ipas = 2; break;
   default:
      assert(!"invalid ipa sample mode");
      break;
   }

   emitInsn (0xe0000000);
   emitField(0x36, 2, ipam);
   emitField(0x34, 2, ipas);
   emitSAT  (0x33);
   emitField(0x2f, 3, 7);
   emitADDR (0x08, 0x1c, 10, 0, insn->src(0));
   if ((code[0] & 0x0000ff00) != 0x0000ff00)
      code[1] |= 0x00000040; /* .idx */
   emitGPR(0x00, insn->def(0));

   if (insn->op == OP_PINTERP) {
      emitGPR(0x14, insn->src(1));
      if (insn->getSampleMode() == NV50_IR_INTERP_OFFSET)
         emitGPR(0x27, insn->src(2));
   } else {
      if (insn->getSampleMode() == NV50_IR_INTERP_OFFSET)
         emitGPR(0x27, insn->src(1));
      emitGPR(0x14);
   }

   if (insn->getSampleMode() != NV50_IR_INTERP_OFFSET)
      emitGPR(0x27);
}

/*******************************************************************************
 * surface
 ******************************************************************************/

void
CodeEmitterGM107::emitPIXLD()
{
   emitInsn (0xefe80000);
   emitPRED (0x2d);
   emitField(0x1f, 3, insn->subOp);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/*******************************************************************************
 * texture
 ******************************************************************************/

void
CodeEmitterGM107::emitTEXs(int pos)
{
   int src1 = insn->predSrc == 1 ? 2 : 1;
   if (insn->srcExists(src1))
      emitGPR(pos, insn->src(src1));
   else
      emitGPR(pos);
}

void
CodeEmitterGM107::emitTEX()
{
   const TexInstruction *insn = this->insn->asTex();
   int lodm = 0;

   if (!insn->tex.levelZero) {
      switch (insn->op) {
      case OP_TEX: lodm = 0; break;
      case OP_TXB: lodm = 2; break;
      case OP_TXL: lodm = 3; break;
      default:
         assert(!"invalid tex op");
         break;
      }
   } else {
      lodm = 1;
   }

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xdeb80000);
      emitField(0x35, 2, lodm);
      emitField(0x24, 1, insn->tex.useOffsets == 1);
   } else {
      emitInsn (0xc0380000);
      emitField(0x37, 2, lodm);
      emitField(0x36, 1, insn->tex.useOffsets == 1);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x32, 1, insn->tex.target.isShadow());
   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x23, 1, insn->tex.derivAll);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x1d, 2, insn->tex.target.isCube() ? 3 :
                      insn->tex.target.getDim() - 1);
   emitField(0x1c, 1, insn->tex.target.isArray());
   emitTEXs (0x14);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitTLD()
{
   const TexInstruction *insn = this->insn->asTex();

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xdd380000);
   } else {
      emitInsn (0xdc380000);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x37, 1, insn->tex.levelZero == 0);
   emitField(0x32, 1, insn->tex.target.isMS());
   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x23, 1, insn->tex.useOffsets == 1);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x1d, 2, insn->tex.target.isCube() ? 3 :
                      insn->tex.target.getDim() - 1);
   emitField(0x1c, 1, insn->tex.target.isArray());
   emitTEXs (0x14);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitTLD4()
{
   const TexInstruction *insn = this->insn->asTex();

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xdef80000);
      emitField(0x26, 2, insn->tex.gatherComp);
      emitField(0x25, 2, insn->tex.useOffsets == 4);
      emitField(0x24, 2, insn->tex.useOffsets == 1);
   } else {
      emitInsn (0xc8380000);
      emitField(0x38, 2, insn->tex.gatherComp);
      emitField(0x37, 2, insn->tex.useOffsets == 4);
      emitField(0x36, 2, insn->tex.useOffsets == 1);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x32, 1, insn->tex.target.isShadow());
   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x23, 1, insn->tex.derivAll);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x1d, 2, insn->tex.target.isCube() ? 3 :
                      insn->tex.target.getDim() - 1);
   emitField(0x1c, 1, insn->tex.target.isArray());
   emitTEXs (0x14);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitTXD()
{
   const TexInstruction *insn = this->insn->asTex();

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xde780000);
   } else {
      emitInsn (0xde380000);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x23, 1, insn->tex.useOffsets == 1);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x1d, 2, insn->tex.target.isCube() ? 3 :
                      insn->tex.target.getDim() - 1);
   emitField(0x1c, 1, insn->tex.target.isArray());
   emitTEXs (0x14);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitTMML()
{
   const TexInstruction *insn = this->insn->asTex();

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xdf600000);
   } else {
      emitInsn (0xdf580000);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x23, 1, insn->tex.derivAll);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x1d, 2, insn->tex.target.isCube() ? 3 :
                      insn->tex.target.getDim() - 1);
   emitField(0x1c, 1, insn->tex.target.isArray());
   emitTEXs (0x14);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitTXQ()
{
   const TexInstruction *insn = this->insn->asTex();
   int type = 0;

   switch (insn->tex.query) {
   case TXQ_DIMS           : type = 0x01; break;
   case TXQ_TYPE           : type = 0x02; break;
   case TXQ_SAMPLE_POSITION: type = 0x05; break;
   case TXQ_FILTER         : type = 0x10; break;
   case TXQ_LOD            : type = 0x12; break;
   case TXQ_WRAP           : type = 0x14; break;
   case TXQ_BORDER_COLOUR  : type = 0x16; break;
   default:
      assert(!"invalid txq query");
      break;
   }

   if (insn->tex.rIndirectSrc >= 0) {
      emitInsn (0xdf500000);
   } else {
      emitInsn (0xdf480000);
      emitField(0x24, 13, insn->tex.r);
   }

   emitField(0x31, 1, insn->tex.liveOnly);
   emitField(0x1f, 4, insn->tex.mask);
   emitField(0x16, 6, type);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

void
CodeEmitterGM107::emitDEPBAR()
{
   emitInsn (0xf0f00000);
   emitField(0x1d, 1, 1); /* le */
   emitField(0x1a, 3, 5);
   emitField(0x14, 6, insn->subOp);
   emitField(0x00, 6, insn->subOp);
}

/*******************************************************************************
 * misc
 ******************************************************************************/

void
CodeEmitterGM107::emitNOP()
{
   emitInsn(0x50b00000);
}

void
CodeEmitterGM107::emitKIL()
{
   emitInsn (0xe3300000);
   emitCond5(0x00, CC_TR);
}

void
CodeEmitterGM107::emitOUT()
{
   const int cut  = insn->op == OP_RESTART || insn->subOp;
   const int emit = insn->op == OP_EMIT;

   switch (insn->src(1).getFile()) {
   case FILE_GPR:
      emitInsn(0xfbe00000);
      emitGPR (0x14, insn->src(1));
      break;
   case FILE_IMMEDIATE:
      emitInsn(0xf6e00000);
      emitIMMD(0x14, 19, insn->src(1));
      break;
   case FILE_MEMORY_CONST:
      emitInsn(0xebe00000);
      emitCBUF(0x22, -1, 0x14, 16, 2, insn->src(1));
      break;
   default:
      assert(!"bad src1 file");
      break;
   }

   emitField(0x27, 2, (cut << 1) | emit);
   emitGPR  (0x08, insn->src(0));
   emitGPR  (0x00, insn->def(0));
}

/*******************************************************************************
 * assembler front-end
 ******************************************************************************/

bool
CodeEmitterGM107::emitInstruction(Instruction *i)
{
   const unsigned int size = (writeIssueDelays && !(codeSize & 0x1f)) ? 16 : 8;
   bool ret = true;

   insn = i;

   if (insn->encSize != 8) {
      ERROR("skipping undecodable instruction: "); insn->print();
      return false;
   } else
   if (codeSize + size > codeSizeLimit) {
      ERROR("code emitter output buffer too small\n");
      return false;
   }

   if (writeIssueDelays) {
      int n = ((codeSize & 0x1f) / 8) - 1;
      if (n < 0) {
         data = code;
         data[0] = 0x00000000;
         data[1] = 0x00000000;
         code += 2;
         codeSize += 8;
         n++;
      }

      emitField(data, n * 21, 21, insn->sched);
   }

   switch (insn->op) {
   case OP_EXIT:
      emitEXIT();
      break;
   case OP_BRA:
      emitBRA();
      break;
   case OP_CALL:
      emitCAL();
      break;
   case OP_PRECONT:
      emitPCNT();
      break;
   case OP_CONT:
      emitCONT();
      break;
   case OP_PREBREAK:
      emitPBK();
      break;
   case OP_BREAK:
      emitBRK();
      break;
   case OP_PRERET:
      emitPRET();
      break;
   case OP_RET:
      emitRET();
      break;
   case OP_JOINAT:
      emitSSY();
      break;
   case OP_JOIN:
      emitSYNC();
      break;
   case OP_QUADON:
      emitSAM();
      break;
   case OP_QUADPOP:
      emitRAM();
      break;
   case OP_MOV:
      if (insn->def(0).getFile() == FILE_GPR &&
          insn->src(0).getFile() != FILE_PREDICATE)
         emitMOV();
      else
         assert(!"R2P/P2R");
      break;
   case OP_RDSV:
      emitS2R();
      break;
   case OP_ABS:
   case OP_NEG:
   case OP_SAT:
   case OP_FLOOR:
   case OP_CEIL:
   case OP_TRUNC:
   case OP_CVT:
      if (isFloatType(insn->dType)) {
         if (isFloatType(insn->sType))
            emitF2F();
         else
            emitI2F();
      } else {
         if (isFloatType(insn->sType))
            emitF2I();
         else
            emitI2I();
      }
      break;
   case OP_SHFL:
      emitSHFL();
      break;
   case OP_ADD:
   case OP_SUB:
      if (isFloatType(insn->dType)) {
         if (insn->dType == TYPE_F64)
            emitDADD();
         else
            emitFADD();
      } else {
         emitIADD();
      }
      break;
   case OP_MUL:
      if (isFloatType(insn->dType)) {
         if (insn->dType == TYPE_F64)
            emitDMUL();
         else
            emitFMUL();
      } else {
         emitIMUL();
      }
      break;
   case OP_MAD:
   case OP_FMA:
      if (isFloatType(insn->dType)) {
         if (insn->dType == TYPE_F64)
            emitDFMA();
         else
            emitFFMA();
      } else {
         emitIMAD();
      }
      break;
   case OP_MIN:
   case OP_MAX:
      if (isFloatType(insn->dType)) {
         if (insn->dType == TYPE_F64)
            emitDMNMX();
         else
            emitFMNMX();
      } else {
         emitIMNMX();
      }
      break;
   case OP_SHL:
      emitSHL();
      break;
   case OP_SHR:
      emitSHR();
      break;
   case OP_POPCNT:
      emitPOPC();
      break;
   case OP_INSBF:
      emitBFI();
      break;
   case OP_EXTBF:
      emitBFE();
      break;
   case OP_BFIND:
      emitFLO();
      break;
   case OP_SLCT:
      if (isFloatType(insn->dType))
         emitFCMP();
      else
         emitICMP();
      break;
   case OP_SET:
   case OP_SET_AND:
   case OP_SET_OR:
   case OP_SET_XOR:
      if (insn->def(0).getFile() != FILE_PREDICATE) {
         if (isFloatType(insn->sType))
            if (insn->sType == TYPE_F64)
               emitDSET();
            else
               emitFSET();
         else
            emitISET();
      } else {
         if (isFloatType(insn->sType))
            if (insn->sType == TYPE_F64)
               emitDSETP();
            else
               emitFSETP();
         else
            emitISETP();
      }
      break;
   case OP_PRESIN:
   case OP_PREEX2:
      emitRRO();
      break;
   case OP_COS:
   case OP_SIN:
   case OP_EX2:
   case OP_LG2:
   case OP_RCP:
   case OP_RSQ:
      emitMUFU();
      break;
   case OP_AND:
   case OP_OR:
   case OP_XOR:
      emitLOP();
      break;
   case OP_NOT:
      emitNOT();
      break;
   case OP_LOAD:
      switch (insn->src(0).getFile()) {
      case FILE_MEMORY_CONST : emitLDC(); break;
      case FILE_MEMORY_LOCAL : emitLDL(); break;
      case FILE_MEMORY_SHARED: emitLDS(); break;
      case FILE_MEMORY_GLOBAL: emitLD(); break;
      default:
         assert(!"invalid load");
         emitNOP();
         break;
      }
      break;
   case OP_STORE:
      switch (insn->src(0).getFile()) {
      case FILE_MEMORY_LOCAL : emitSTL(); break;
      case FILE_MEMORY_SHARED: emitSTS(); break;
      case FILE_MEMORY_GLOBAL: emitST(); break;
      default:
         assert(!"invalid load");
         emitNOP();
         break;
      }
      break;
   case OP_VFETCH:
      emitALD();
      break;
   case OP_EXPORT:
      emitAST();
      break;
   case OP_PFETCH:
      emitISBERD();
      break;
   case OP_AFETCH:
      emitAL2P();
      break;
   case OP_LINTERP:
   case OP_PINTERP:
      emitIPA();
      break;
   case OP_PIXLD:
      emitPIXLD();
      break;
   case OP_TEX:
   case OP_TXB:
   case OP_TXL:
      emitTEX();
      break;
   case OP_TXF:
      emitTLD();
      break;
   case OP_TXG:
      emitTLD4();
      break;
   case OP_TXD:
      emitTXD();
      break;
   case OP_TXQ:
      emitTXQ();
      break;
   case OP_TXLQ:
      emitTMML();
      break;
   case OP_TEXBAR:
      emitDEPBAR();
      break;
   case OP_QUADOP:
      emitFSWZADD();
      break;
   case OP_NOP:
      emitNOP();
      break;
   case OP_DISCARD:
      emitKIL();
      break;
   case OP_EMIT:
   case OP_RESTART:
      emitOUT();
      break;
   default:
      assert(!"invalid opcode");
      emitNOP();
      ret = false;
      break;
   }

   if (insn->join) {
      /*XXX*/
   }

   code += 2;
   codeSize += 8;
   return ret;
}

uint32_t
CodeEmitterGM107::getMinEncodingSize(const Instruction *i) const
{
   return 8;
}

/*******************************************************************************
 * sched data calculator
 ******************************************************************************/

class SchedDataCalculatorGM107 : public Pass
{
public:
   SchedDataCalculatorGM107(const Target *targ) : targ(targ) {}
private:
   const Target *targ;
   bool visit(BasicBlock *bb);
};

bool
SchedDataCalculatorGM107::visit(BasicBlock *bb)
{
   for (Instruction *insn = bb->getEntry(); insn; insn = insn->next) {
      /*XXX*/
      insn->sched = 0x7e0;
   }

   return true;
}

/*******************************************************************************
 * main
 ******************************************************************************/

void
CodeEmitterGM107::prepareEmission(Function *func)
{
   SchedDataCalculatorGM107 sched(targ);
   CodeEmitter::prepareEmission(func);
   sched.run(func, true, true);
}

static inline uint32_t sizeToBundlesGM107(uint32_t size)
{
   return (size + 23) / 24;
}

void
CodeEmitterGM107::prepareEmission(Program *prog)
{
   for (ArrayList::Iterator fi = prog->allFuncs.iterator();
        !fi.end(); fi.next()) {
      Function *func = reinterpret_cast<Function *>(fi.get());
      func->binPos = prog->binSize;
      prepareEmission(func);

      // adjust sizes & positions for schedulding info:
      if (prog->getTarget()->hasSWSched) {
         uint32_t adjPos = func->binPos;
         BasicBlock *bb = NULL;
         for (int i = 0; i < func->bbCount; ++i) {
            bb = func->bbArray[i];
            int32_t adjSize = bb->binSize;
            if (adjPos % 32) {
               adjSize -= 32 - adjPos % 32;
               if (adjSize < 0)
                  adjSize = 0;
            }
            adjSize = bb->binSize + sizeToBundlesGM107(adjSize) * 8;
            bb->binPos = adjPos;
            bb->binSize = adjSize;
            adjPos += adjSize;
         }
         if (bb)
            func->binSize = adjPos - func->binPos;
      }

      prog->binSize += func->binSize;
   }
}

CodeEmitterGM107::CodeEmitterGM107(const TargetGM107 *target)
   : CodeEmitter(target),
     targGM107(target),
     writeIssueDelays(target->hasSWSched)
{
   code = NULL;
   codeSize = codeSizeLimit = 0;
   relocInfo = NULL;
}

CodeEmitter *
TargetGM107::createCodeEmitterGM107(Program::Type type)
{
   CodeEmitterGM107 *emit = new CodeEmitterGM107(this);
   emit->setProgramType(type);
   return emit;
}

} // namespace nv50_ir
