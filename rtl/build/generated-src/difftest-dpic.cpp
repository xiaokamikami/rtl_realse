#ifndef CONFIG_NO_DIFFTEST

#include "difftest.h"
#include "difftest-dpic.h"
#include "difftest-query.h"
#ifdef CONFIG_DIFFTEST_PERFCNT
#include "perf.h"
#endif // CONFIG_DIFFTEST_PERFCNT


#include "difftest-delta.h"
DeltaStats* dStats = nullptr;
#define DELTA_BUF(core_id) (dStats->get(core_id))


DiffStateBuffer** diffstate_buffer = nullptr;
#define DUT_BUF(core_id, zone, index) (diffstate_buffer[core_id]->get(zone, index))

void diffstate_buffer_init() {
  diffstate_buffer = new DiffStateBuffer*[NUM_CORES];
  for (int i = 0; i < NUM_CORES; i++) {
    diffstate_buffer[i] = new DPICBuffer;
  }
  dStats = new DeltaStats;
}

void diffstate_buffer_free() {
  for (int i = 0; i < NUM_CORES; i++) {
    delete diffstate_buffer[i];
  }
  delete[] diffstate_buffer;
  diffstate_buffer = nullptr;
  delete dStats;
}
      

#ifdef CONFIG_DIFFTEST_PERFCNT
enum DIFFSTATE_PERF {
  perf_v_difftest_Batch,
  perf_Batch_InstrCommit,
  perf_Batch_TrapEvent,
  perf_Batch_ArchEvent,
  perf_Batch_CriticalErrorEvent,
  perf_Batch_NonRegInterruptPendingEvent,
  perf_Batch_MhpmeventOverflowEvent,
  perf_Batch_SyncAIAEvent,
  perf_Batch_SyncCustomMflushpwrEvent,
  perf_Batch_LrScEvent,
  perf_Batch_ArchIntRenameTableElem,
  perf_Batch_ArchFpRenameTableElem,
  perf_Batch_PhyIntRegStateElem,
  perf_Batch_PhyFpRegStateElem,
  perf_Batch_CSRStateElem,
  perf_Batch_DebugModeElem,
  perf_Batch_TriggerCSRStateElem,
  perf_Batch_FpCSRStateElem,
  perf_Batch_HCSRStateElem,
  perf_Batch_DeltaInfo,
  DIFFSTATE_PERF_NUM
};
long long dpic_calls[DIFFSTATE_PERF_NUM] = {0}, dpic_bytes[DIFFSTATE_PERF_NUM] = {0};
void diffstate_perfcnt_init() {
  for (int i = 0; i < DIFFSTATE_PERF_NUM; i++) {
    dpic_calls[i] = 0;
    dpic_bytes[i] = 0;
  }
}
void diffstate_perfcnt_finish(long long msec) {
  long long calls_sum = 0, bytes_sum = 0;
  const char *dpic_name[DIFFSTATE_PERF_NUM] = {
    "v_difftest_Batch",
    "Batch_InstrCommit",
    "Batch_TrapEvent",
    "Batch_ArchEvent",
    "Batch_CriticalErrorEvent",
    "Batch_NonRegInterruptPendingEvent",
    "Batch_MhpmeventOverflowEvent",
    "Batch_SyncAIAEvent",
    "Batch_SyncCustomMflushpwrEvent",
    "Batch_LrScEvent",
    "Batch_ArchIntRenameTableElem",
    "Batch_ArchFpRenameTableElem",
    "Batch_PhyIntRegStateElem",
    "Batch_PhyFpRegStateElem",
    "Batch_CSRStateElem",
    "Batch_DebugModeElem",
    "Batch_TriggerCSRStateElem",
    "Batch_FpCSRStateElem",
    "Batch_HCSRStateElem",
    "Batch_DeltaInfo"
  };
  for (int i = 0; i < DIFFSTATE_PERF_NUM; i++) {
    difftest_perfcnt_print(dpic_name[i], dpic_calls[i], dpic_bytes[i], msec);
  }
  for (int i = 1; i < DIFFSTATE_PERF_NUM; i++) {
    calls_sum += dpic_calls[i];
    bytes_sum += dpic_bytes[i];
  }
  difftest_perfcnt_print("DIFFSTATE_SUM", calls_sum, bytes_sum, msec);
}
#endif // CONFIG_DIFFTEST_PERFCNT



extern "C" void v_difftest_Batch (
  uint8_t  io[2000]
) {
  if (!diffstate_buffer) return;

#ifdef CONFIG_DIFFTEST_PERFCNT
  dpic_calls[perf_v_difftest_Batch] ++;
  dpic_bytes[perf_v_difftest_Batch] += 2000;
#endif // CONFIG_DIFFTEST_PERFCNT

  
  enum DifftestBundleType {
  InstrCommit,
  TrapEvent,
  ArchEvent,
  CriticalErrorEvent,
  NonRegInterruptPendingEvent,
  MhpmeventOverflowEvent,
  SyncAIAEvent,
  SyncCustomMflushpwrEvent,
  LrScEvent,
  ArchIntRenameTableElem,
  ArchFpRenameTableElem,
  PhyIntRegStateElem,
  PhyFpRegStateElem,
  CSRStateElem,
  DebugModeElem,
  TriggerCSRStateElem,
  FpCSRStateElem,
  HCSRStateElem,
  DeltaInfo,
  BatchStep,
  BatchFinish
  };
  static int dut_index = 0;
  
  typedef struct {
    uint8_t  num;
    uint8_t  id;
  } BatchInfo;
  typedef struct {
    BatchInfo info[50];
    uint8_t  data[1900];
  } BatchPack;
  BatchPack* batch = (BatchPack*)io;
  BatchInfo* info = batch->info;
  uint8_t* data = batch->data;

  for (int i = 0; i < 50; i++) {
    if (!diffstate_buffer) return;
    uint8_t id = info[i].id;
    uint8_t num = info[i].num;
    uint32_t coreid, index, address;
    if (id == BatchFinish) {
      break;
    }
    else if (id == BatchStep) {
      
      if (dStats->need_pending())
        continue; // Not changing dut_index
      dStats->sync(0, dut_index);

      dut_index = (dut_index + 1) % CONFIG_DIFFTEST_BATCH_SIZE;
#ifdef CONFIG_DIFFTEST_QUERY
      difftest_query_step();
#endif // CONFIG_DIFFTEST_QUERY
#ifdef CONFIG_DIFFTEST_INTERNAL_STEP
#ifdef FPGA_HOST
      extern void fpga_nstep(uint8_t step);
      fpga_nstep(1);
#else
      extern void simv_nstep(uint8_t step);
      simv_nstep(1);
#endif // FPGA_HOST
#endif // CONFIG_DIFFTEST_INTERNAL_STEP
      continue;
    }
    
    else if (id == InstrCommit) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_InstrCommit] += num;
      dpic_bytes[perf_Batch_InstrCommit] += num * 64;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[62];
        index = data[63];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->commit[index]);
        memcpy(packet, data, sizeof(DifftestInstrCommit));
        data += 64;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->InstrCommit_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == TrapEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_TrapEvent] += num;
      dpic_bytes[perf_Batch_TrapEvent] += num * 35;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[34];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->trap);
        memcpy(packet, data, sizeof(DifftestTrapEvent));
        data += 35;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->TrapEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == ArchEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_ArchEvent] += num;
      dpic_bytes[perf_Batch_ArchEvent] += num * 26;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[25];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->event);
        memcpy(packet, data, sizeof(DifftestArchEvent));
        data += 26;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->ArchEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == CriticalErrorEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_CriticalErrorEvent] += num;
      dpic_bytes[perf_Batch_CriticalErrorEvent] += num * 3;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[2];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->critical_error);
        memcpy(packet, data, sizeof(DifftestCriticalErrorEvent));
        data += 3;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->CriticalErrorEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == NonRegInterruptPendingEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_NonRegInterruptPendingEvent] += num;
      dpic_bytes[perf_Batch_NonRegInterruptPendingEvent] += num * 12;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[11];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->non_reg_interrupt_pending);
        memcpy(packet, data, sizeof(DifftestNonRegInterruptPendingEvent));
        data += 12;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->NonRegInterruptPendingEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == MhpmeventOverflowEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_MhpmeventOverflowEvent] += num;
      dpic_bytes[perf_Batch_MhpmeventOverflowEvent] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[9];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->mhpmevent_overflow);
        memcpy(packet, data, sizeof(DifftestMhpmeventOverflowEvent));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->MhpmeventOverflowEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == SyncAIAEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_SyncAIAEvent] += num;
      dpic_bytes[perf_Batch_SyncAIAEvent] += num * 34;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[33];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->sync_aia);
        memcpy(packet, data, sizeof(DifftestSyncAIAEvent));
        data += 34;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->SyncAIAEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == SyncCustomMflushpwrEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_SyncCustomMflushpwrEvent] += num;
      dpic_bytes[perf_Batch_SyncCustomMflushpwrEvent] += num * 3;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[2];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->sync_custom_mflushpwr);
        memcpy(packet, data, sizeof(DifftestSyncCustomMflushpwrEvent));
        data += 3;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->SyncCustomMflushpwrEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == LrScEvent) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_LrScEvent] += num;
      dpic_bytes[perf_Batch_LrScEvent] += num * 3;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[2];
        auto packet = &(DUT_BUF(coreid, 0, dut_index)->lrsc);
        memcpy(packet, data, sizeof(DifftestLrScEvent));
        data += 3;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->LrScEvent_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == ArchIntRenameTableElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_ArchIntRenameTableElem] += num;
      dpic_bytes[perf_Batch_ArchIntRenameTableElem] += num * 3;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[1];
        index = data[2];
        auto packet = &(DELTA_BUF(coreid)->rat_xrf_elem[index]);
        memcpy(packet, data, sizeof(uint8_t));
        data += 3;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->ArchIntRenameTableElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == ArchFpRenameTableElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_ArchFpRenameTableElem] += num;
      dpic_bytes[perf_Batch_ArchFpRenameTableElem] += num * 3;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[1];
        index = data[2];
        auto packet = &(DELTA_BUF(coreid)->rat_frf_elem[index]);
        memcpy(packet, data, sizeof(uint8_t));
        data += 3;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->ArchFpRenameTableElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == PhyIntRegStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_PhyIntRegStateElem] += num;
      dpic_bytes[perf_Batch_PhyIntRegStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->pregs_xrf_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->PhyIntRegStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == PhyFpRegStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_PhyFpRegStateElem] += num;
      dpic_bytes[perf_Batch_PhyFpRegStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->pregs_frf_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->PhyFpRegStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == CSRStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_CSRStateElem] += num;
      dpic_bytes[perf_Batch_CSRStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->csr_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->CSRStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == DebugModeElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_DebugModeElem] += num;
      dpic_bytes[perf_Batch_DebugModeElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->dmregs_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->DebugModeElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == TriggerCSRStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_TriggerCSRStateElem] += num;
      dpic_bytes[perf_Batch_TriggerCSRStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->triggercsr_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->TriggerCSRStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == FpCSRStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_FpCSRStateElem] += num;
      dpic_bytes[perf_Batch_FpCSRStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->fcsr_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->FpCSRStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == HCSRStateElem) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_HCSRStateElem] += num;
      dpic_bytes[perf_Batch_HCSRStateElem] += num * 10;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[8];
        index = data[9];
        auto packet = &(DELTA_BUF(coreid)->hcsr_elem[index]);
        memcpy(packet, data, sizeof(uint64_t));
        data += 10;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->HCSRStateElem_write(coreid, index, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
    else if (id == DeltaInfo) {
#ifdef CONFIG_DIFFTEST_PERFCNT
      dpic_calls[perf_Batch_DeltaInfo] += num;
      dpic_bytes[perf_Batch_DeltaInfo] += num * 2;
#endif // CONFIG_DIFFTEST_PERFCNT
      for (int j = 0; j < num; j++) {
        coreid = data[1];
        auto packet = &(DELTA_BUF(coreid)->delta_info);
        memcpy(packet, data, sizeof(DifftestDeltaInfo));
        data += 2;
        
#ifdef CONFIG_DIFFTEST_QUERY
        qStats->DeltaInfo_write(coreid, packet);
#endif // CONFIG_DIFFTEST_QUERY

      }
    }
        
  }

}


#endif // CONFIG_NO_DIFFTEST

