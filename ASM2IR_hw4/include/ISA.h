// ISA format:
// Opcode
// Name
// SkipArgs: string -> 0 [ifstream InputFile]
// ReadArgs: string -> args [ifstream InputFile, Instr I, map BBName2PC]
// WriteArgs: args -> string [stringstream Stream, Instr I, map PC2BBName]
// Execute: args -> EXECUTION [uint32_t R1, uint32_t R2Imm, uint32_t R3Imm, uint32_t R4Imm, CPU *C]
// IRGenExecute = args -> IR [IRBuilder builder, regFileType regFile, Instr I,
//                            map BBMap, uint32_t PC, GraphicalFuncs]

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

// SkipArgs
#define SKIP_4ARGS                                                             \
  { InputFile >> Arg >> Arg >> Arg >> Arg; }
#define SKIP_3ARGS                                                             \
  { InputFile >> Arg >> Arg >> Arg; }
#define SKIP_2ARGS                                                             \
  { InputFile >> Arg >> Arg; }
#define SKIP_1ARGS                                                             \
  { InputFile >> Arg; }

// ReadArgs
#define READ_REG(Reg)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.Reg = std::stoi(Arg.substr(1));                                          \
  }
#define READ_IMM(Imm)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    I.Imm = std::stoi(Arg);                                                    \
  }
#define READ_LABEL(L)                                                          \
  {                                                                            \
    InputFile >> Arg;                                                          \
    if (BBName2PC.find(Arg) == BBName2PC.end()) {                              \
      ErrorMsg = std::string("Can't find label: " + Arg);                      \
      return true;                                                             \
    }                                                                          \
    I.L = BBName2PC[Arg];                                                      \
  }
#define L1 R3Imm
#define L2 R4Imm
#define READ_4REGS                                                             \
  { READ_REG(R1) READ_REG(R2Imm) READ_REG(R3Imm) READ_REG(R4Imm) }
#define READ_3REGS                                                             \
  { READ_REG(R1) READ_REG(R2Imm) READ_REG(R3Imm) }
#define READ_2REGS_IMM                                                         \
  { READ_REG(R1) READ_REG(R2Imm) READ_IMM(R3Imm) }
#define READ_2REGS                                                             \
  { READ_REG(R1) READ_REG(R2Imm) }
#define READ_REG_LABEL                                                         \
  { READ_REG(R1) READ_LABEL(L1) }
#define READ_REG_2LABELS                                                       \
  { READ_REG(R1) READ_LABEL(L1) READ_LABEL(L2) }
#define READ_2REGS_2LABELS                                                     \
  { READ_REG(R1) READ_REG(R2Imm) READ_LABEL(L1) READ_LABEL(L2) }
#define READ_REG_IMM                                                           \
  { READ_REG(R1) READ_IMM(R2Imm) }
#define READ_REG_IMM_2LABELS                                                   \
  { READ_REG(R1) READ_IMM(R2Imm) READ_LABEL(L1) READ_LABEL(L2) }
#define READ_REG_2IMMS                                                         \
  { READ_REG(R1) READ_IMM(R2Imm) READ_IMM(R3Imm) }


// WriteArgs
#define WRITE_REG(Reg)                                                         \
  { Stream << " x" << I.Reg; }
#define WRITE_IMM(Imm)                                                         \
  { Stream << " " << I.Imm; }
#define WRITE_LABEL(L)                                                         \
  { Stream << " " << PC2BBName[I.L]; }
#define WRITE_4REGS                                                            \
  { WRITE_REG(R1) WRITE_REG(R2Imm) WRITE_REG(R3Imm) WRITE_REG(R4Imm) }
#define WRITE_3REGS                                                            \
  { WRITE_REG(R1) WRITE_REG(R2Imm) WRITE_REG(R3Imm) }
#define WRITE_2REGS_IMM                                                        \
  { WRITE_REG(R1) WRITE_REG(R2Imm) WRITE_IMM(R3Imm) }
#define WRITE_2REGS                                                            \
  { WRITE_REG(R1) WRITE_REG(R2Imm) }
#define WRITE_REG_LABEL                                                        \
  { WRITE_REG(R1) WRITE_LABEL(L1) }
#define WRITE_REG_2LABELS                                                      \
  { WRITE_REG(R1) WRITE_LABEL(L1) WRITE_LABEL(L2) }
#define WRITE_2REGS_2LABELS                                                    \
  { WRITE_REG(R1) WRITE_REG(R2Imm) WRITE_LABEL(L1) WRITE_LABEL(L2) }
#define WRITE_REG_IMM                                                          \
  { WRITE_REG(R1) WRITE_IMM(R2Imm) }
#define WRITE_REG_IMM_2LABELS                                                  \
  { WRITE_REG(R1) WRITE_IMM(R2Imm) WRITE_LABEL(L1) WRITE_LABEL(L2) }
#define WRITE_REG_2IMMS                                                        \
  { WRITE_REG(R1) WRITE_IMM(R2Imm) WRITE_IMM(R3Imm) }

// _IRGenExecute
#define GEP2_32(Arg) builder.CreateConstGEP2_32(regFileType, regFile, 0, Arg)
#define LOAD_REG(Arg) builder.CreateLoad(int32Type, GEP2_32(Arg))
#define GEN_IMM(Arg) builder.getInt32(Arg)
#define LOAD_SP() builder.CreateLoad(int32Type, sp)

// _ISA(_Opcode, _Name, _SkipArgs, _ReadArgs, _WriteArgs, _Execute,
// _IRGenExecute)

//    EXIT (NO ARGS)
_ISA(
    0x1, EXIT, {}, {}, {}, { C->Run = 0; }, 
    { builder.CreateRetVoid(); })
//    FLUSH (NO ARGS)
_ISA(
    0x2, FLUSH, {}, {}, {}, 
    { simFlush(); },
    { builder.CreateCall(simFlushFunc); })
//    PUT_PIXEL x5 x2 x6 (3REGS)
_ISA(
    0x3, PUT_PIXEL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { simPutPixel(C->RegFile[R1], C->RegFile[R2Imm], C->RegFile[R3Imm]); },
    {
      builder.CreateCall(simPutPixelFunc,
                         {LOAD_REG(I.R1), LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)});
    })
//    RAND r4 (REG)
_ISA(
    0x4, RAND, SKIP_1ARGS, READ_REG(R1), WRITE_REG(R1),
    { C->RegFile[R1] = simRand(); },
    { builder.CreateStore(builder.CreateCall(simRandFunc), GEP2_32(I.R1)); })
//    TO_ABS r4 (REG)
_ISA(
    0x5, TO_ABS, SKIP_1ARGS, READ_REG(R1), WRITE_REG(R1),
    {
      int32_t r_abs = C->RegFile[R1];
      C->RegFile[R1] = r_abs < 0 ? -r_abs : r_abs;
    },
    {
      builder.CreateStore(
          builder.CreateCall(AbsFunc, {LOAD_REG(I.R1), builder.getInt1(true)}),
          GEP2_32(I.R1));
    })
//    ADD x3 x2 x1 (3REGS)
_ISA(
    0x6, ADD, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2Imm] + C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateAdd(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    ADDi x3 x2 1 (2REGS_IMM)
_ISA(
    0x7, ADDi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2Imm] + R3Imm; },
    {
      builder.CreateStore(builder.CreateAdd(LOAD_REG(I.R2Imm), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    MUL x3 x2 x1 (3REGS)
_ISA(
    0x8, MUL, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2Imm] * C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateMul(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    MULi x3 x2 1 (2REGS_IMM)
_ISA(
    0x9, MULi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = C->RegFile[R2Imm] * R3Imm; },
    {
      builder.CreateStore(builder.CreateMul(LOAD_REG(I.R2Imm), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    XOR x1 x1 x1 (3REGS)
_ISA(
    0x10, XOR, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    {
      C->RegFile[R1] = C->RegFile[R2Imm] ^ C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateXor(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SUB x3 x2 x4 (3REGS)
_ISA(
    0x11, SUB, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = C->RegFile[R2Imm] - C->RegFile[R3Imm]; },
    {
      builder.CreateStore(builder.CreateSub(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    iSUB x20 x17 255 (2REGS_IMM)
_ISA(
    0x12, iSUB, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = R3Imm - C->RegFile[R2Imm]; },
    {
      builder.CreateStore(builder.CreateSub(GEN_IMM(I.R3Imm), LOAD_REG(I.R2Imm)),
                          GEP2_32(I.R1));
    })
//    DIVi x3 x2 4 (2REGS_IMM)
_ISA(
    0x13, DIVi, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    {
      C->RegFile[R1] = C->RegFile[R2Imm] / R3Imm; },
    {
      builder.CreateStore(builder.CreateSDiv(LOAD_REG(I.R2Imm), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SDIV_MUL x7 x7 x8 x15 (4REGS)
_ISA(
    0x14, SDIV_MUL, SKIP_4ARGS, READ_4REGS, WRITE_4REGS,
    {
      int32_t r2 = C->RegFile[R2Imm];
      int32_t r3 = C->RegFile[R3Imm];
      int32_t r4 = C->RegFile[R4Imm];
      C->RegFile[R1] = (r2 * r3) / r4;
    },
    {
      builder.CreateStore(
        builder.CreateSDiv(builder.CreateMul(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          LOAD_REG(I.R4Imm)),
                          GEP2_32(I.R1));
    })
//    SDIV_ADD x7 x7 x8 x15 (4REGS)
_ISA(
    0x15, SDIV_ADD, SKIP_4ARGS, READ_4REGS, WRITE_4REGS,
    {
      int32_t r2 = C->RegFile[R2Imm];
      int32_t r3 = C->RegFile[R3Imm];
      int32_t r4 = C->RegFile[R4Imm];
      C->RegFile[R1] = (r2 + r3) / r4;
    },
    {
      builder.CreateStore(
        builder.CreateSDiv(builder.CreateAdd(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          LOAD_REG(I.R4Imm)),
                          GEP2_32(I.R1));
    })
//    MOVi r2 0 (REG_IMM)
_ISA(
    0x16, MOVi, SKIP_2ARGS, READ_REG_IMM, WRITE_REG_IMM,
    { C->RegFile[R1] = R2Imm; },
    { builder.CreateStore(GEN_IMM(I.R2Imm), GEP2_32(I.R1)); })
//    MOV r2 r3 (2REGS)
_ISA(
    0x17, MOV, SKIP_2ARGS, READ_2REGS, WRITE_2REGS,
    { C->RegFile[R1] = C->RegFile[R2Imm]; },
    { builder.CreateStore(LOAD_REG(I.R2Imm), GEP2_32(I.R1)); })
//    ICMPi_SGT x0 x1 0 (2REGS_IMM)
_ISA(
    0x18, ICMPi_SGT, SKIP_3ARGS, READ_2REGS_IMM, WRITE_2REGS_IMM,
    { C->RegFile[R1] = (C->RegFile[R2Imm] > R3Imm); },
    {
      builder.CreateStore(builder.CreateICmpSGT(LOAD_REG(I.R2Imm), GEN_IMM(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    ICMP_SGT x0 x1 x2 (3REGS)
_ISA(
    0x19, ICMP_SGT, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = (C->RegFile[R2Imm] > C->RegFile[R3Imm]); },
    {
      builder.CreateStore(builder.CreateICmpSGT(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    ICMP_ULT x23 x23 x24 (3REGS)
_ISA(
    0x20, ICMP_ULT, SKIP_3ARGS, READ_3REGS, WRITE_3REGS,
    { C->RegFile[R1] = (C->RegFile[R2Imm] < C->RegFile[R3Imm]); },
    {
      builder.CreateStore(builder.CreateICmpULT(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
                          GEP2_32(I.R1));
    })
//    SELECT x17 -1 1 (REG_2IMMS)
_ISA(
    0x21, SELECT, SKIP_3ARGS, READ_REG_2IMMS, WRITE_REG_2IMMS,
    { C->RegFile[R1] = C->RegFile[R1] ? R2Imm : R3Imm; },
    {
      builder.CreateStore(
        builder.CreateSelect(
          builder.CreateTrunc(LOAD_REG(I.R1), builder.getInt1Ty()), 
          GEN_IMM(I.R2Imm), GEN_IMM(I.R3Imm)),
        GEP2_32(I.R1));
    }
)
//    BR label_13 (LABEL)
_ISA(
    0x22, BR, SKIP_1ARGS, READ_LABEL(L1), WRITE_LABEL(L1), 
    { C->NextPC = L1; },
    {
      PC++;
      builder.CreateBr(BBMap[I.L1]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })
//    BR_COND x1 label_6 label_1 (REG_2LABELS)
_ISA(
    0x23, BR_COND, SKIP_3ARGS, READ_REG_2LABELS, WRITE_REG_2LABELS,
    {
      if (C->RegFile[R1]) {
        C->NextPC = L1;
      } else {
        C->NextPC = L2;
      }
    },
    {
      PC++;
      builder.CreateCondBr(
          builder.CreateTrunc(LOAD_REG(I.R1), builder.getInt1Ty()),
          BBMap[I.L1], BBMap[I.L2]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })
//    BR_EQi x1 0 label_3 label_2 (REG_IMM_2LABELS)
_ISA(
    0x24, BR_EQi, SKIP_4ARGS, READ_REG_IMM_2LABELS, WRITE_REG_IMM_2LABELS,
    {
      if (C->RegFile[R1] == R2Imm) {
        C->NextPC = L1;
      } else {
        C->NextPC = L2;
      }
    },
    {
      PC++;
      builder.CreateCondBr(
          builder.CreateICmpEQ(LOAD_REG(I.R1), GEN_IMM(I.R2Imm)),
          BBMap[I.L1], BBMap[I.L2]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })
//    BR_EQ x3 x1 label_1 label_6 (2REGS_2LABELS)
_ISA(
    0x25, BR_EQ, SKIP_4ARGS, READ_2REGS_2LABELS, WRITE_2REGS_2LABELS,
    {
      if (C->RegFile[R1] == C->RegFile[R2Imm]) {
        C->NextPC = L1;
      } else {
        C->NextPC = L2;
      }
    },
    {
      PC++;
      builder.CreateCondBr(
          builder.CreateICmpEQ(LOAD_REG(I.R1), LOAD_REG(I.R2Imm)),
          BBMap[I.L1], BBMap[I.L2]);
      builder.SetInsertPoint(BBMap[PC]);
      continue;
    })
//    PUSH arg (ARG)
_ISA(
    0x26, PUSH, SKIP_1ARGS, READ_REG(R1), WRITE_REG(R1),
    {
      *C->SP = C->RegFile[R1];
      ++C->SP;
    },
    {
      builder.CreateStore(
        LOAD_REG(I.R1), 
        builder.CreateGEP(regFileType, regFile, {GEN_IMM(0), LOAD_SP()}));
      builder.CreateStore(
        builder.CreateAdd(LOAD_SP(), GEN_IMM(1)), 
        sp);
    }
)
//  POP arg (ARG)
_ISA(
  0x27, POP, SKIP_1ARGS, READ_REG(R1), WRITE_REG(R1),
    {
      --C->SP;
      C->RegFile[R1] = *C->SP;
    }, 
    {
    Value *cur = builder.CreateSub(LOAD_SP(), GEN_IMM(1));
    builder.CreateStore(cur, sp);
    builder.CreateStore(
      builder.CreateLoad(int32Type, builder.CreateGEP(regFileType, regFile, {GEN_IMM(0), cur})), 
      GEP2_32(I.R1));
    }
)
//	TURN x1 x2 x3 x4 (4REGS)
_ISA(
    0x28, TURN, SKIP_4ARGS, READ_4REGS, WRITE_4REGS,
    {
	  C->RegFile[R1] = C->RegFile[R2Imm] + C->RegFile[R3Imm] - C->RegFile[R4Imm];
	},
    {
	  builder.CreateStore(
		builder.CreateSub(
				builder.CreateAdd(LOAD_REG(I.R2Imm), LOAD_REG(I.R3Imm)),
				LOAD_REG(I.R4Imm)
		),
		GEP2_32(I.R1));
    })
#undef L1
#undef L2
