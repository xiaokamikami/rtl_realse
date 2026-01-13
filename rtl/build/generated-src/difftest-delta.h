#ifndef __DIFFTEST_DELTA_H__
#define __DIFFTEST_DELTA_H__
#include "difftest-state.h"
typedef struct __attribute__((packed)) {
  uint8_t  inPending;
} DifftestDeltaInfo;

typedef struct {
  DifftestDeltaInfo delta_info;
  uint8_t rat_xrf_elem[32];
  uint8_t rat_frf_elem[32];
  uint64_t pregs_xrf_elem[224];
  uint64_t pregs_frf_elem[192];
  uint64_t csr_elem[18];
  uint64_t dmregs_elem[5];
  uint64_t triggercsr_elem[3];
  uint64_t fcsr_elem[1];
  uint64_t hcsr_elem[17];
} DeltaState;


class DeltaStats {
private:
  DeltaState buffer[NUM_CORES];
public:
  DeltaStats() {
    memset(buffer, 0, sizeof(buffer));
  }
  DeltaState* get(int coreid){
    return buffer + coreid;
  }
  bool need_pending() {
    for (int i = 0; i < NUM_CORES; i++) {
      auto info = get(i)->delta_info;
      if (info.inPending != 0) {
        return true;
      }
    }
    return false;
  }
  void sync(int zone, int index) {
    for (int i = 0; i < NUM_CORES; i++) {
      DiffTestState* dut = diffstate_buffer[i]->get(zone, index);
      DeltaState* delta = get(i);
      memcpy(&(dut->rat_xrf), delta->rat_xrf_elem, sizeof(DifftestArchIntRenameTable));
      memcpy(&(dut->rat_frf), delta->rat_frf_elem, sizeof(DifftestArchFpRenameTable));
      memcpy(&(dut->pregs_xrf), delta->pregs_xrf_elem, sizeof(DifftestPhyIntRegState));
      memcpy(&(dut->pregs_frf), delta->pregs_frf_elem, sizeof(DifftestPhyFpRegState));
      memcpy(&(dut->regs.csr), delta->csr_elem, sizeof(DifftestCSRState));
      memcpy(&(dut->dmregs), delta->dmregs_elem, sizeof(DifftestDebugMode));
      memcpy(&(dut->regs.triggercsr), delta->triggercsr_elem, sizeof(DifftestTriggerCSRState));
      memcpy(&(dut->regs.fcsr), delta->fcsr_elem, sizeof(DifftestFpCSRState));
      memcpy(&(dut->regs.hcsr), delta->hcsr_elem, sizeof(DifftestHCSRState));
    }
  }
};

#endif // __DIFFTEST_DELTA_H__
