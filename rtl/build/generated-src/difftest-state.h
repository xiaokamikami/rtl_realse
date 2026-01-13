#ifndef __DIFFTEST_STATE_H__
#define __DIFFTEST_STATE_H__

#include <cstdint>

#define CONFIG_DIFFTEST_DPIC
#define CONFIG_DIFFTEST_ZONESIZE 1
#define CONFIG_DIFFTEST_BUFLEN 64
#define CONFIG_DIFFTEST_BATCH
#define CONFIG_DIFFTEST_BATCH_SIZE 64
#define CONFIG_DIFFTEST_BATCH_BYTELEN 2000
#define CONFIG_DIFFTEST_SQUASH
#define CONFIG_DIFFTEST_SQUASH_STAMPSIZE 4096
#define CONFIG_DIFFTEST_DELTA
#define CONFIG_DIFFTEST_DEFERRED_RESULT
#define CONFIG_DIFFTEST_INTERNAL_STEP
#define CONFIG_DIFFTEST_FPGA

#define CPU_XIANGSHAN


#ifndef NUM_CORES
#define NUM_CORES 1
#endif

#define CONFIG_DIFFTEST_NONREGINTERRUPTPENDINGEVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint8_t  platformIRPMeip;
  uint8_t  platformIRPMtip;
  uint8_t  platformIRPMsip;
  uint8_t  platformIRPSeip;
  uint8_t  platformIRPStip;
  uint8_t  platformIRPVseip;
  uint8_t  platformIRPVstip;
  uint8_t  fromAIAMeip;
  uint8_t  fromAIASeip;
  uint8_t  localCounterOverflowInterruptReq;
} DifftestNonRegInterruptPendingEvent;

#define CONFIG_DIFFTEST_LRSCEVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint8_t  success;
} DifftestLrScEvent;

#define CONFIG_DIFFTEST_SYNCAIAEVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint64_t mtopei;
  uint64_t stopei;
  uint64_t vstopei;
  uint64_t hgeip;
} DifftestSyncAIAEvent;

#define CONFIG_DIFFTEST_CRITICALERROREVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint8_t  criticalError;
} DifftestCriticalErrorEvent;

#define CONFIG_DIFFTEST_PHYFPREGSTATE
typedef struct __attribute__((packed)) {
  uint64_t value[192];
} DifftestPhyFpRegState;

#define CONFIG_DIFFTEST_SYNCCUSTOMMFLUSHPWREVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint8_t  l2FlushDone;
} DifftestSyncCustomMflushpwrEvent;

#define CONFIG_DIFFTEST_DEBUGMODE
typedef struct __attribute__((packed)) {
  uint64_t debugMode;
  uint64_t dcsr;
  uint64_t dpc;
  uint64_t dscratch0;
  uint64_t dscratch1;
} DifftestDebugMode;

#define CONFIG_DIFFTEST_TRIGGERCSRSTATE
typedef struct __attribute__((packed)) {
  uint64_t tselect;
  uint64_t tdata1;
  uint64_t tinfo;
} DifftestTriggerCSRState;

#define CONFIG_DIFFTEST_ARCHFPRENAMETABLE
typedef struct __attribute__((packed)) {
  uint8_t  value[32];
} DifftestArchFpRenameTable;

#define CONFIG_DIFFTEST_INSTRCOMMIT
#define CONFIG_DIFF_COMMIT_WIDTH 8
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint8_t  skip;
  uint8_t  isRVC;
  uint8_t  rfwen;
  uint8_t  fpwen;
  uint8_t  vecwen;
  uint8_t  v0wen;
  uint16_t wpdest;
  uint8_t  wdest;
  uint16_t otherwpdest[16];
  uint64_t pc;
  uint32_t instr;
  uint16_t robIdx;
  uint8_t  lqIdx;
  uint8_t  sqIdx;
  uint8_t  isLoad;
  uint8_t  isStore;
  uint8_t  nFused;
  uint8_t  special;
} DifftestInstrCommit;

#define CONFIG_DIFFTEST_PHYINTREGSTATE
typedef struct __attribute__((packed)) {
  uint64_t value[224];
} DifftestPhyIntRegState;

#define CONFIG_DIFFTEST_MHPMEVENTOVERFLOWEVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint64_t mhpmeventOverflow;
} DifftestMhpmeventOverflowEvent;

#define CONFIG_DIFFTEST_ARCHEVENT
typedef struct __attribute__((packed)) {
  uint8_t  valid;
  uint32_t interrupt;
  uint32_t exception;
  uint64_t exceptionPC;
  uint32_t exceptionInst;
  uint8_t  hasNMI;
  uint8_t  virtualInterruptIsHvictlInject;
  uint8_t  irToHS;
  uint8_t  irToVS;
} DifftestArchEvent;

#define CONFIG_DIFFTEST_ARCHINTREGSTATE
typedef struct __attribute__((packed)) {
  uint64_t value[32];
} DifftestArchIntRegState;

#define CONFIG_DIFFTEST_HCSRSTATE
typedef struct __attribute__((packed)) {
  uint64_t virtMode;
  uint64_t mtval2;
  uint64_t mtinst;
  uint64_t hstatus;
  uint64_t hideleg;
  uint64_t hedeleg;
  uint64_t hcounteren;
  uint64_t htval;
  uint64_t htinst;
  uint64_t hgatp;
  uint64_t vsstatus;
  uint64_t vstvec;
  uint64_t vsepc;
  uint64_t vscause;
  uint64_t vstval;
  uint64_t vsatp;
  uint64_t vsscratch;
} DifftestHCSRState;

#define CONFIG_DIFFTEST_ARCHINTRENAMETABLE
typedef struct __attribute__((packed)) {
  uint8_t  value[32];
} DifftestArchIntRenameTable;

#define CONFIG_DIFFTEST_ARCHFPREGSTATE
typedef struct __attribute__((packed)) {
  uint64_t value[32];
} DifftestArchFpRegState;

#define CONFIG_DIFFTEST_CSRSTATE
typedef struct __attribute__((packed)) {
  uint64_t privilegeMode;
  uint64_t mstatus;
  uint64_t sstatus;
  uint64_t mepc;
  uint64_t sepc;
  uint64_t mtval;
  uint64_t stval;
  uint64_t mtvec;
  uint64_t stvec;
  uint64_t mcause;
  uint64_t scause;
  uint64_t satp;
  uint64_t mip;
  uint64_t mie;
  uint64_t mscratch;
  uint64_t sscratch;
  uint64_t mideleg;
  uint64_t medeleg;
} DifftestCSRState;

#define CONFIG_DIFFTEST_TRAPEVENT
typedef struct __attribute__((packed)) {
  uint8_t  hasTrap;
  uint64_t cycleCnt;
  uint64_t instrCnt;
  uint8_t  hasWFI;
  uint64_t code;
  uint64_t pc;
} DifftestTrapEvent;

#define CONFIG_DIFFTEST_FPCSRSTATE
typedef struct __attribute__((packed)) {
  uint64_t fcsr;
} DifftestFpCSRState;

typedef struct {
  DifftestArchIntRegState        xrf;
  DifftestArchFpRegState         frf;
  DifftestCSRState               csr;
  DifftestHCSRState              hcsr;
  DifftestFpCSRState             fcsr;
  DifftestTriggerCSRState        triggercsr;
} DiffTestRegState;

typedef struct {
  DiffTestRegState regs;
  DifftestArchEvent              event;
  DifftestArchFpRenameTable      rat_frf;
  DifftestArchIntRenameTable     rat_xrf;
  DifftestCriticalErrorEvent     critical_error;
  DifftestDebugMode              dmregs;
  DifftestInstrCommit            commit[8];
  DifftestLrScEvent              lrsc;
  DifftestMhpmeventOverflowEvent mhpmevent_overflow;
  DifftestNonRegInterruptPendingEvent non_reg_interrupt_pending;
  DifftestPhyFpRegState          pregs_frf;
  DifftestPhyIntRegState         pregs_xrf;
  DifftestSyncAIAEvent           sync_aia;
  DifftestSyncCustomMflushpwrEvent sync_custom_mflushpwr;
  DifftestTrapEvent              trap;
} DiffTestState;


class DiffStateBuffer {
public:
  virtual ~DiffStateBuffer() {}
  virtual DiffTestState* get(int zone, int index) = 0;
  virtual DiffTestState* next() = 0;
  virtual void switch_zone() = 0;
};

extern DiffStateBuffer** diffstate_buffer;

extern void diffstate_buffer_init();
extern void diffstate_buffer_free();


#ifdef CONFIG_DIFFTEST_PERFCNT
void diffstate_perfcnt_init();
void diffstate_perfcnt_finish(long long msec);
#endif // CONFIG_DIFFTEST_PERFCNT


#ifdef CONFIG_DIFFTEST_QUERY
void difftest_query_init();
void difftest_query_step();
void difftest_query_finish();
#endif // CONFIG_DIFFTEST_QUERY

#endif // __DIFFTEST_STATE_H__

