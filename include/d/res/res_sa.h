#ifndef RES_SA_H
#define RES_SA_H

#include "global.h"

enum SA_RES_FILE_ID {
    /* BCKS */
    SA_BCK_SA01HEAD_TALK01=0x5,
    SA_BCK_SA01HEAD_WAIT01=0x6,
    SA_BCK_SA_TALK01=0x7,
    SA_BCK_SA_WAIT01=0x8,
    SA_BCK_SA01HEAD_TALK02=0x9,
    SA_BCK_SA_TALK02=0xA,
    SA_BCK_SA_KIAI=0x16,
    SA_BCK_SA_TALK03=0x17,
    SA_BCK_SA_WAIT02=0x18,
    SA_BCK_SA01HEAD_CTALK01=0x19,
    SA_BCK_SA01HEAD_CWAIT01=0x1A,
    SA_BCK_SA_CTALK01=0x1B,
    SA_BCK_SA_CTALK03=0x1C,
    SA_BCK_SA_CTALK04=0x1D,
    SA_BCK_SA_CTALK05=0x1E,
    SA_BCK_SA_CWAIT01=0x1F,
    SA_BCK_SA_CWAIT03=0x20,
    SA_BCK_SA_CWAIT04=0x21,
    SA_BCK_SA_CWAIT05=0x22,
    SA_BCK_SA_DRINK=0x23,
    SA_BCK_SA_LAUGH=0x24,
    
    /* BDL */
    SA_BDL_SA=0x2,
    SA_BDL_SA_CUP04=0x25,
    SA_BDL_SA_CUP05=0x26,
    
    /* BDLM */
    SA_BDL_SA01_HEAD=0x3,
    SA_BDL_SA02_HEAD=0xB,
    SA_BDL_SA03_HEAD=0xC,
    SA_BDL_SA04_HEAD=0xD,
    SA_BDL_SA05_HEAD=0xE,
    
    /* BTP */
    SA_BTP_SA01_MABA=0x4,
    SA_BTP_SA02_MABA=0xF,
    SA_BTP_SA04_MABA=0x10,
    SA_BTP_SA05_MABA=0x11,
    
    /* BMT */
    SA_BMT_SA02=0x12,
    SA_BMT_SA03=0x13,
    SA_BMT_SA04=0x14,
    SA_BMT_SA05=0x15,
};

enum SA_RES_FILE_INDEX {
    /* BCKS */
    SA_INDEX_BCK_SA01HEAD_TALK01=0x7,
    SA_INDEX_BCK_SA01HEAD_WAIT01=0x8,
    SA_INDEX_BCK_SA_TALK01=0x9,
    SA_INDEX_BCK_SA_WAIT01=0xA,
    SA_INDEX_BCK_SA01HEAD_TALK02=0xB,
    SA_INDEX_BCK_SA_TALK02=0xC,
    SA_INDEX_BCK_SA_KIAI=0xD,
    SA_INDEX_BCK_SA_TALK03=0xE,
    SA_INDEX_BCK_SA_WAIT02=0xF,
    SA_INDEX_BCK_SA01HEAD_CTALK01=0x10,
    SA_INDEX_BCK_SA01HEAD_CWAIT01=0x11,
    SA_INDEX_BCK_SA_CTALK01=0x12,
    SA_INDEX_BCK_SA_CTALK03=0x13,
    SA_INDEX_BCK_SA_CTALK04=0x14,
    SA_INDEX_BCK_SA_CTALK05=0x15,
    SA_INDEX_BCK_SA_CWAIT01=0x16,
    SA_INDEX_BCK_SA_CWAIT03=0x17,
    SA_INDEX_BCK_SA_CWAIT04=0x18,
    SA_INDEX_BCK_SA_CWAIT05=0x19,
    SA_INDEX_BCK_SA_DRINK=0x1A,
    SA_INDEX_BCK_SA_LAUGH=0x1B,
    
    /* BDL */
    SA_INDEX_BDL_SA=0x1E,
    SA_INDEX_BDL_SA_CUP04=0x1F,
    SA_INDEX_BDL_SA_CUP05=0x20,
    
    /* BDLM */
    SA_INDEX_BDL_SA01_HEAD=0x23,
    SA_INDEX_BDL_SA02_HEAD=0x24,
    SA_INDEX_BDL_SA03_HEAD=0x25,
    SA_INDEX_BDL_SA04_HEAD=0x26,
    SA_INDEX_BDL_SA05_HEAD=0x27,
    
    /* BTP */
    SA_INDEX_BTP_SA01_MABA=0x2A,
    SA_INDEX_BTP_SA02_MABA=0x2B,
    SA_INDEX_BTP_SA04_MABA=0x2C,
    SA_INDEX_BTP_SA05_MABA=0x2D,
    
    /* BMT */
    SA_INDEX_BMT_SA02=0x30,
    SA_INDEX_BMT_SA03=0x31,
    SA_INDEX_BMT_SA04=0x32,
    SA_INDEX_BMT_SA05=0x33,
};

#endif /* RES_SA_H */
