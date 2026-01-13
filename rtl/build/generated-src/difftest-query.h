
#ifndef __DIFFTEST_QUERY_H__
#define __DIFFTEST_QUERY_H__

#include <cstdint>
#include "difftest-state.h"
#include "query.h"
#ifdef CONFIG_DIFFTEST_DELTA
#include "difftest-delta.h"
#endif // CONFIG_DIFFTEST_DELTA

#ifdef CONFIG_DIFFTEST_QUERY

class QueryStats: public QueryStatsBase {
public:
  Query* query_InstrCommit;
  Query* query_TrapEvent;
  Query* query_ArchEvent;
  Query* query_CriticalErrorEvent;
  Query* query_NonRegInterruptPendingEvent;
  Query* query_MhpmeventOverflowEvent;
  Query* query_SyncAIAEvent;
  Query* query_SyncCustomMflushpwrEvent;
  Query* query_LrScEvent;
  Query* query_ArchIntRenameTableElem;
  Query* query_ArchFpRenameTableElem;
  Query* query_PhyIntRegStateElem;
  Query* query_PhyFpRegStateElem;
  Query* query_CSRStateElem;
  Query* query_DebugModeElem;
  Query* query_TriggerCSRStateElem;
  Query* query_FpCSRStateElem;
  Query* query_HCSRStateElem;
  Query* query_DeltaInfo;
  QueryStats(char *path): QueryStatsBase(path) {
    InstrCommit_init();
    TrapEvent_init();
    ArchEvent_init();
    CriticalErrorEvent_init();
    NonRegInterruptPendingEvent_init();
    MhpmeventOverflowEvent_init();
    SyncAIAEvent_init();
    SyncCustomMflushpwrEvent_init();
    LrScEvent_init();
    ArchIntRenameTableElem_init();
    ArchFpRenameTableElem_init();
    PhyIntRegStateElem_init();
    PhyFpRegStateElem_init();
    CSRStateElem_init();
    DebugModeElem_init();
    TriggerCSRStateElem_init();
    FpCSRStateElem_init();
    HCSRStateElem_init();
    DeltaInfo_init();
  }
  
  void InstrCommit_init() {
    const char* createSql = " CREATE TABLE InstrCommit(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "VALID INT NOT NULL," \
      "SKIP INT NOT NULL," \
      "ISRVC INT NOT NULL," \
      "RFWEN INT NOT NULL," \
      "FPWEN INT NOT NULL," \
      "VECWEN INT NOT NULL," \
      "V0WEN INT NOT NULL," \
      "WPDEST INT NOT NULL," \
      "WDEST INT NOT NULL," \
      "OTHERWPDEST_0 INT NOT NULL," \
      "OTHERWPDEST_1 INT NOT NULL," \
      "OTHERWPDEST_2 INT NOT NULL," \
      "OTHERWPDEST_3 INT NOT NULL," \
      "OTHERWPDEST_4 INT NOT NULL," \
      "OTHERWPDEST_5 INT NOT NULL," \
      "OTHERWPDEST_6 INT NOT NULL," \
      "OTHERWPDEST_7 INT NOT NULL," \
      "OTHERWPDEST_8 INT NOT NULL," \
      "OTHERWPDEST_9 INT NOT NULL," \
      "OTHERWPDEST_10 INT NOT NULL," \
      "OTHERWPDEST_11 INT NOT NULL," \
      "OTHERWPDEST_12 INT NOT NULL," \
      "OTHERWPDEST_13 INT NOT NULL," \
      "OTHERWPDEST_14 INT NOT NULL," \
      "OTHERWPDEST_15 INT NOT NULL," \
      "PC INT NOT NULL," \
      "INSTR INT NOT NULL," \
      "ROBIDX INT NOT NULL," \
      "LQIDX INT NOT NULL," \
      "SQIDX INT NOT NULL," \
      "ISLOAD INT NOT NULL," \
      "ISSTORE INT NOT NULL," \
      "NFUSED INT NOT NULL," \
      "SPECIAL INT NOT NULL);";
    const char* insertSql = "INSERT INTO InstrCommit (STEP,COREID,MY_INDEX,VALID,SKIP,ISRVC,RFWEN,FPWEN,VECWEN,V0WEN,WPDEST,WDEST,OTHERWPDEST_0,OTHERWPDEST_1,OTHERWPDEST_2,OTHERWPDEST_3,OTHERWPDEST_4,OTHERWPDEST_5,OTHERWPDEST_6,OTHERWPDEST_7,OTHERWPDEST_8,OTHERWPDEST_9,OTHERWPDEST_10,OTHERWPDEST_11,OTHERWPDEST_12,OTHERWPDEST_13,OTHERWPDEST_14,OTHERWPDEST_15,PC,INSTR,ROBIDX,LQIDX,SQIDX,ISLOAD,ISSTORE,NFUSED,SPECIAL) " \
      " VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";
    query_InstrCommit = new Query(mem_db, createSql, insertSql);
  }

  void TrapEvent_init() {
    const char* createSql = " CREATE TABLE TrapEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "HASTRAP INT NOT NULL," \
      "CYCLECNT INT NOT NULL," \
      "INSTRCNT INT NOT NULL," \
      "HASWFI INT NOT NULL," \
      "CODE INT NOT NULL," \
      "PC INT NOT NULL);";
    const char* insertSql = "INSERT INTO TrapEvent (STEP,COREID,HASTRAP,CYCLECNT,INSTRCNT,HASWFI,CODE,PC) " \
      " VALUES (?,?,?,?,?,?,?,?);";
    query_TrapEvent = new Query(mem_db, createSql, insertSql);
  }

  void ArchEvent_init() {
    const char* createSql = " CREATE TABLE ArchEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "INTERRUPT INT NOT NULL," \
      "EXCEPTION INT NOT NULL," \
      "EXCEPTIONPC INT NOT NULL," \
      "EXCEPTIONINST INT NOT NULL," \
      "HASNMI INT NOT NULL," \
      "VIRTUALINTERRUPTISHVICTLINJECT INT NOT NULL," \
      "IRTOHS INT NOT NULL," \
      "IRTOVS INT NOT NULL);";
    const char* insertSql = "INSERT INTO ArchEvent (STEP,COREID,VALID,INTERRUPT,EXCEPTION,EXCEPTIONPC,EXCEPTIONINST,HASNMI,VIRTUALINTERRUPTISHVICTLINJECT,IRTOHS,IRTOVS) " \
      " VALUES (?,?,?,?,?,?,?,?,?,?,?);";
    query_ArchEvent = new Query(mem_db, createSql, insertSql);
  }

  void CriticalErrorEvent_init() {
    const char* createSql = " CREATE TABLE CriticalErrorEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "CRITICALERROR INT NOT NULL);";
    const char* insertSql = "INSERT INTO CriticalErrorEvent (STEP,COREID,VALID,CRITICALERROR) " \
      " VALUES (?,?,?,?);";
    query_CriticalErrorEvent = new Query(mem_db, createSql, insertSql);
  }

  void NonRegInterruptPendingEvent_init() {
    const char* createSql = " CREATE TABLE NonRegInterruptPendingEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "PLATFORMIRPMEIP INT NOT NULL," \
      "PLATFORMIRPMTIP INT NOT NULL," \
      "PLATFORMIRPMSIP INT NOT NULL," \
      "PLATFORMIRPSEIP INT NOT NULL," \
      "PLATFORMIRPSTIP INT NOT NULL," \
      "PLATFORMIRPVSEIP INT NOT NULL," \
      "PLATFORMIRPVSTIP INT NOT NULL," \
      "FROMAIAMEIP INT NOT NULL," \
      "FROMAIASEIP INT NOT NULL," \
      "LOCALCOUNTEROVERFLOWINTERRUPTREQ INT NOT NULL);";
    const char* insertSql = "INSERT INTO NonRegInterruptPendingEvent (STEP,COREID,VALID,PLATFORMIRPMEIP,PLATFORMIRPMTIP,PLATFORMIRPMSIP,PLATFORMIRPSEIP,PLATFORMIRPSTIP,PLATFORMIRPVSEIP,PLATFORMIRPVSTIP,FROMAIAMEIP,FROMAIASEIP,LOCALCOUNTEROVERFLOWINTERRUPTREQ) " \
      " VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?);";
    query_NonRegInterruptPendingEvent = new Query(mem_db, createSql, insertSql);
  }

  void MhpmeventOverflowEvent_init() {
    const char* createSql = " CREATE TABLE MhpmeventOverflowEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "MHPMEVENTOVERFLOW INT NOT NULL);";
    const char* insertSql = "INSERT INTO MhpmeventOverflowEvent (STEP,COREID,VALID,MHPMEVENTOVERFLOW) " \
      " VALUES (?,?,?,?);";
    query_MhpmeventOverflowEvent = new Query(mem_db, createSql, insertSql);
  }

  void SyncAIAEvent_init() {
    const char* createSql = " CREATE TABLE SyncAIAEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "MTOPEI INT NOT NULL," \
      "STOPEI INT NOT NULL," \
      "VSTOPEI INT NOT NULL," \
      "HGEIP INT NOT NULL);";
    const char* insertSql = "INSERT INTO SyncAIAEvent (STEP,COREID,VALID,MTOPEI,STOPEI,VSTOPEI,HGEIP) " \
      " VALUES (?,?,?,?,?,?,?);";
    query_SyncAIAEvent = new Query(mem_db, createSql, insertSql);
  }

  void SyncCustomMflushpwrEvent_init() {
    const char* createSql = " CREATE TABLE SyncCustomMflushpwrEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "L2FLUSHDONE INT NOT NULL);";
    const char* insertSql = "INSERT INTO SyncCustomMflushpwrEvent (STEP,COREID,VALID,L2FLUSHDONE) " \
      " VALUES (?,?,?,?);";
    query_SyncCustomMflushpwrEvent = new Query(mem_db, createSql, insertSql);
  }

  void LrScEvent_init() {
    const char* createSql = " CREATE TABLE LrScEvent(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "VALID INT NOT NULL," \
      "SUCCESS INT NOT NULL);";
    const char* insertSql = "INSERT INTO LrScEvent (STEP,COREID,VALID,SUCCESS) " \
      " VALUES (?,?,?,?);";
    query_LrScEvent = new Query(mem_db, createSql, insertSql);
  }

  void ArchIntRenameTableElem_init() {
    const char* createSql = " CREATE TABLE ArchIntRenameTableElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO ArchIntRenameTableElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_ArchIntRenameTableElem = new Query(mem_db, createSql, insertSql);
  }

  void ArchFpRenameTableElem_init() {
    const char* createSql = " CREATE TABLE ArchFpRenameTableElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO ArchFpRenameTableElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_ArchFpRenameTableElem = new Query(mem_db, createSql, insertSql);
  }

  void PhyIntRegStateElem_init() {
    const char* createSql = " CREATE TABLE PhyIntRegStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO PhyIntRegStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_PhyIntRegStateElem = new Query(mem_db, createSql, insertSql);
  }

  void PhyFpRegStateElem_init() {
    const char* createSql = " CREATE TABLE PhyFpRegStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO PhyFpRegStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_PhyFpRegStateElem = new Query(mem_db, createSql, insertSql);
  }

  void CSRStateElem_init() {
    const char* createSql = " CREATE TABLE CSRStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO CSRStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_CSRStateElem = new Query(mem_db, createSql, insertSql);
  }

  void DebugModeElem_init() {
    const char* createSql = " CREATE TABLE DebugModeElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO DebugModeElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_DebugModeElem = new Query(mem_db, createSql, insertSql);
  }

  void TriggerCSRStateElem_init() {
    const char* createSql = " CREATE TABLE TriggerCSRStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO TriggerCSRStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_TriggerCSRStateElem = new Query(mem_db, createSql, insertSql);
  }

  void FpCSRStateElem_init() {
    const char* createSql = " CREATE TABLE FpCSRStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO FpCSRStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_FpCSRStateElem = new Query(mem_db, createSql, insertSql);
  }

  void HCSRStateElem_init() {
    const char* createSql = " CREATE TABLE HCSRStateElem(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "MY_INDEX INT NOT NULL," \
      "DATA INT NOT NULL);";
    const char* insertSql = "INSERT INTO HCSRStateElem (STEP,COREID,MY_INDEX,DATA) " \
      " VALUES (?,?,?,?);";
    query_HCSRStateElem = new Query(mem_db, createSql, insertSql);
  }

  void DeltaInfo_init() {
    const char* createSql = " CREATE TABLE DeltaInfo(" \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "STEP INT NOT NULL," \
      "COREID INT NOT NULL," \
      "INPENDING INT NOT NULL);";
    const char* insertSql = "INSERT INTO DeltaInfo (STEP,COREID,INPENDING) " \
      " VALUES (?,?,?);";
    query_DeltaInfo = new Query(mem_db, createSql, insertSql);
  }

  
  void InstrCommit_write(uint8_t coreid, uint8_t index, DifftestInstrCommit* packet) {
    query_InstrCommit->write(37, query_step, coreid, index, packet->valid, packet->skip, packet->isRVC, packet->rfwen, packet->fpwen, packet->vecwen, packet->v0wen, packet->wpdest, packet->wdest, packet->otherwpdest[0], packet->otherwpdest[1], packet->otherwpdest[2], packet->otherwpdest[3], packet->otherwpdest[4], packet->otherwpdest[5], packet->otherwpdest[6], packet->otherwpdest[7], packet->otherwpdest[8], packet->otherwpdest[9], packet->otherwpdest[10], packet->otherwpdest[11], packet->otherwpdest[12], packet->otherwpdest[13], packet->otherwpdest[14], packet->otherwpdest[15], packet->pc, packet->instr, packet->robIdx, packet->lqIdx, packet->sqIdx, packet->isLoad, packet->isStore, packet->nFused, packet->special);
  }

  void TrapEvent_write(uint8_t coreid, DifftestTrapEvent* packet) {
    query_TrapEvent->write(8, query_step, coreid, packet->hasTrap, packet->cycleCnt, packet->instrCnt, packet->hasWFI, packet->code, packet->pc);
  }

  void ArchEvent_write(uint8_t coreid, DifftestArchEvent* packet) {
    query_ArchEvent->write(11, query_step, coreid, packet->valid, packet->interrupt, packet->exception, packet->exceptionPC, packet->exceptionInst, packet->hasNMI, packet->virtualInterruptIsHvictlInject, packet->irToHS, packet->irToVS);
  }

  void CriticalErrorEvent_write(uint8_t coreid, DifftestCriticalErrorEvent* packet) {
    query_CriticalErrorEvent->write(4, query_step, coreid, packet->valid, packet->criticalError);
  }

  void NonRegInterruptPendingEvent_write(uint8_t coreid, DifftestNonRegInterruptPendingEvent* packet) {
    query_NonRegInterruptPendingEvent->write(13, query_step, coreid, packet->valid, packet->platformIRPMeip, packet->platformIRPMtip, packet->platformIRPMsip, packet->platformIRPSeip, packet->platformIRPStip, packet->platformIRPVseip, packet->platformIRPVstip, packet->fromAIAMeip, packet->fromAIASeip, packet->localCounterOverflowInterruptReq);
  }

  void MhpmeventOverflowEvent_write(uint8_t coreid, DifftestMhpmeventOverflowEvent* packet) {
    query_MhpmeventOverflowEvent->write(4, query_step, coreid, packet->valid, packet->mhpmeventOverflow);
  }

  void SyncAIAEvent_write(uint8_t coreid, DifftestSyncAIAEvent* packet) {
    query_SyncAIAEvent->write(7, query_step, coreid, packet->valid, packet->mtopei, packet->stopei, packet->vstopei, packet->hgeip);
  }

  void SyncCustomMflushpwrEvent_write(uint8_t coreid, DifftestSyncCustomMflushpwrEvent* packet) {
    query_SyncCustomMflushpwrEvent->write(4, query_step, coreid, packet->valid, packet->l2FlushDone);
  }

  void LrScEvent_write(uint8_t coreid, DifftestLrScEvent* packet) {
    query_LrScEvent->write(4, query_step, coreid, packet->valid, packet->success);
  }

  void ArchIntRenameTableElem_write(uint8_t coreid, uint8_t index, uint8_t* packet) {
    query_ArchIntRenameTableElem->write(4, query_step, coreid, index, *packet);
  }

  void ArchFpRenameTableElem_write(uint8_t coreid, uint8_t index, uint8_t* packet) {
    query_ArchFpRenameTableElem->write(4, query_step, coreid, index, *packet);
  }

  void PhyIntRegStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_PhyIntRegStateElem->write(4, query_step, coreid, index, *packet);
  }

  void PhyFpRegStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_PhyFpRegStateElem->write(4, query_step, coreid, index, *packet);
  }

  void CSRStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_CSRStateElem->write(4, query_step, coreid, index, *packet);
  }

  void DebugModeElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_DebugModeElem->write(4, query_step, coreid, index, *packet);
  }

  void TriggerCSRStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_TriggerCSRStateElem->write(4, query_step, coreid, index, *packet);
  }

  void FpCSRStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_FpCSRStateElem->write(4, query_step, coreid, index, *packet);
  }

  void HCSRStateElem_write(uint8_t coreid, uint8_t index, uint64_t* packet) {
    query_HCSRStateElem->write(4, query_step, coreid, index, *packet);
  }

  void DeltaInfo_write(uint8_t coreid, DifftestDeltaInfo* packet) {
    query_DeltaInfo->write(3, query_step, coreid, packet->inPending);
  }

};
#endif // CONFIG_DIFFTEST_QUERY
#endif // __DIFFTEST_QUERY_H__

