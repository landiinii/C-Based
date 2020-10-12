#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

const int MAX_MEM_SIZE  = (1 << 13);

void fetchStage(int *icode, int *ifun, int *rA, int *rB, wordType *valC, wordType *valP) {
  int pc = getPC();
  byteType ibyte = getByteFromMemory(pc);
  *icode = ibyte >> 4;
  *ifun = ibyte & 0xF;
  pc++;
  
  if(*icode == OPQ || *icode == RRMOVQ || *icode == POPQ || *icode == PUSHQ){
    byteType rbyte = getByteFromMemory(pc);
    *rA = rbyte >> 4;
    *rB = rbyte & 0xF;
    pc++;
  }
  
  if(*icode == IRMOVQ || *icode == MRMOVQ || *icode == RMMOVQ){
    byteType rbyte = getByteFromMemory(pc);
    *rA = rbyte >> 4;
    *rB = rbyte & 0xF;
    pc++;
    *valC = getWordFromMemory(pc);
    pc+=8;
  }
  
  if(*icode==JXX || *icode == CALL){
    *valC = getWordFromMemory(pc);
    pc+=8;
  }
  
  if(*icode == HALT){
    setStatus(STAT_HLT);
  }
  
  *valP = pc;
}

void decodeStage(int icode, int rA, int rB, wordType *valA, wordType *valB) {
  if(icode==OPQ || icode==RRMOVQ || icode==RMMOVQ){
    *valA = getRegister(rA);
    *valB = getRegister(rB);
  }
  
  if(icode==MRMOVQ){
    *valB = getRegister(rB);
  }
  
  if(icode==PUSHQ){
    *valA = getRegister(rA);
    *valB = getRegister(RSP);
  }
  
  if(icode==POPQ || icode==RET){
    *valA = getRegister(RSP);
    *valB = getRegister(RSP);
  }
  
  if(icode==CALL){
    *valB = getRegister(RSP);
  }
}

bool setSignFlag(wordType valE){
  if(valE < 0){
    return 1;
  }
  return 0;
}

bool setZeroFlag(wordType valE){
  if(valE == 0){
    return 1;
  }
  return 0;
}

bool setOverflow(wordType valE, wordType valA, wordType valB, int ifun){
  if(ifun == ADD){
    if(valA>0 && valB>0 && valE<0){
      return 1;
    }
    else if(valA<0 && valB<0 && valE>0){
      return 1;
    }
    else {
      return 0;
    }
  }
  else if(ifun == SUB){
    if(valB<0 && valA>0 && valE>0){
      return 1;
    }
    else if(valB>0 && valA<0 && valE<0){
      return 1;
    }
    else{
      return 0;
      
    }
  }
  return 0;
}

void executeStage(int icode, int ifun, wordType valA, wordType valB, wordType valC, wordType *valE, bool *Cnd) {
  if(icode==OPQ){
    if(ifun==ADD){
      *valE = valA + valB;
    }
    else if(ifun==SUB){
      *valE = valB - valA;
    }
    else if(ifun==AND){
      *valE = valB & valA;
    }
    else if(ifun==XOR){
      *valE = valB ^ valA;
    }
    bool sf = setSignFlag(*valE);
    bool zf = setZeroFlag(*valE);
    bool of = setOverflow(*valE, valA, valB, ifun);
    setFlags(sf, zf, of);
  }
  
  if(icode==RRMOVQ){
    *valE = valA;
    if(ifun!=0){
      *Cnd = Cond(ifun);
      if(!*Cnd){
        *valE = valB;
      }
    }
  }
  
  if(icode==IRMOVQ){
    *valE = valC;
  }
  
  if(icode==MRMOVQ || icode==RMMOVQ){
    *valE = valB + valC;
  }
  
  if(icode==PUSHQ || icode==CALL){
    *valE=valB-8;
  }
  
  if(icode==POPQ || icode==RET){
    *valE=valB+8;
  }
  
  if(icode==JXX){
    *Cnd = Cond(ifun);
  }
}

void memoryStage(int icode, wordType valA, wordType valP, wordType valE, wordType *valM) {
  if(icode==MRMOVQ){
    *valM = getWordFromMemory(valE);
  }
  
  if(icode==RMMOVQ || icode==PUSHQ){
    setWordInMemory(valE, valA);
  }
  
  if(icode==POPQ || icode==RET){
    *valM = getWordFromMemory(valA);
  }
  
  if(icode==CALL){
    setWordInMemory(valE, valP);
  }
}

void writebackStage(int icode, wordType rA, wordType rB, wordType valE, wordType valM) {
  if(icode==OPQ || icode==RRMOVQ || icode==IRMOVQ){
    setRegister(rB, valE);
  }
  
  if(icode==MRMOVQ){
    setRegister(rA, valM);
  }
  
  if(icode==PUSHQ){
    setRegister(RSP, valE);
  }
  
  if(icode==POPQ){
    setRegister(RSP, valE);
    setRegister(rA, valM);
  }
  
  if(icode==CALL || icode==RET){
    setRegister(RSP, valE);
  }
}

void pcUpdateStage(int icode, wordType valC, wordType valP, bool Cnd, wordType valM) {

  if(icode==JXX){
    Cnd ? setPC(valC):setPC(valP);
  }
  else if(icode==CALL){
    setPC(valC);
  }
  else if(icode==RET){
    setPC(valM);
  }
  else{
    setPC(valP);
  }
  
  if(getStatus() == STAT_HLT){
    setStatus(STAT_HLT);
    setPC(valP);
  }
  else {
    setStatus(STAT_AOK);
  }
}

void stepMachine(int stepMode) {
  /* FETCH STAGE */
  int icode = 0, ifun = 0;
  int rA = 0, rB = 0;
  wordType valC = 0;
  wordType valP = 0;
 
  /* DECODE STAGE */
  wordType valA = 0;
  wordType valB = 0;

  /* EXECUTE STAGE */
  wordType valE = 0;
  bool Cnd = 0;

  /* MEMORY STAGE */
  wordType valM = 0;

  fetchStage(&icode, &ifun, &rA, &rB, &valC, &valP);
  applyStageStepMode(stepMode, "Fetch", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  decodeStage(icode, rA, rB, &valA, &valB);
  applyStageStepMode(stepMode, "Decode", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  executeStage(icode, ifun, valA, valB, valC, &valE, &Cnd);
  applyStageStepMode(stepMode, "Execute", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  memoryStage(icode, valA, valP, valE, &valM);
  applyStageStepMode(stepMode, "Memory", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  writebackStage(icode, rA, rB, valE, valM);
  applyStageStepMode(stepMode, "Writeback", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);
  
  pcUpdateStage(icode, valC, valP, Cnd, valM);
  applyStageStepMode(stepMode, "PC update", icode, ifun, rA, rB, valC, valP, valA, valB, valE, Cnd, valM);

  incrementCycleCounter();
}

/** 
 * main
 * */
int main(int argc, char **argv) {
  int stepMode = 0;
  FILE *input = parseCommandLine(argc, argv, &stepMode);

  initializeMemory(MAX_MEM_SIZE);
  initializeRegisters();
  loadMemory(input);

  applyStepMode(stepMode);
  while (getStatus() != STAT_HLT) {
    stepMachine(stepMode);
    applyStepMode(stepMode);
#ifdef DEBUG
    printMachineState();
    printf("\n");
#endif
  }
  printMachineState();
  return 0;
}