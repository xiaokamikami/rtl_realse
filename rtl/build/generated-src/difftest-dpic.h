#ifndef __DIFFTEST_DPIC_H__
#define __DIFFTEST_DPIC_H__

#include <cstdint>
#include "difftest-state.h"
#if defined(CONFIG_DIFFTEST_BATCH) && !defined(CONFIG_DIFFTEST_FPGA)
#include "svdpi.h"
#endif // CONFIG_DIFFTEST_BATCH && !CONFIG_DIFFTEST_FPGA
#include "difftest-delta.h"
static inline void diffstate_update_archreg(DiffTestState* dut) {
  for (int i = 0; i < 32; i++) { dut->regs.xrf.value[i] = dut->pregs_xrf.value[dut->rat_xrf.value[i]]; }
  for (int i = 0; i < 32; i++) { dut->regs.frf.value[i] = dut->pregs_frf.value[dut->rat_frf.value[i]]; }
}


class DPICBuffer : public DiffStateBuffer {
private:
  DiffTestState buffer[CONFIG_DIFFTEST_ZONESIZE][CONFIG_DIFFTEST_BUFLEN];
  int read_ptr = 0;
  int zone_ptr = 0;
  bool init = true;
public:
  DPICBuffer() {
    memset(buffer, 0, sizeof(buffer));
  }
  inline DiffTestState* get(int zone, int index) {
    return buffer[zone] + index;
  }
  inline DiffTestState* next() {
    DiffTestState* ret = buffer[zone_ptr] + read_ptr;
    diffstate_update_archreg(ret);
    read_ptr = (read_ptr + 1) % CONFIG_DIFFTEST_BUFLEN;
    return ret;
  }
  inline void switch_zone() {
    if (init) {
      init = false;
      return;
    }
    zone_ptr = (zone_ptr + 1) % CONFIG_DIFFTEST_ZONESIZE;
    read_ptr = 0;
  }
};


extern "C" void v_difftest_Batch (
  uint8_t  io[2000]
);

#endif // __DIFFTEST_DPIC_H__

