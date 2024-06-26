#ifndef RES_DEMO01_H
#define RES_DEMO01_H

#include "global.h"

enum DEMO01_RES_FILE_ID {
    /* STB */
    DEMO01_STB_TALE=0xA,
    DEMO01_STB_TALE_2=0x25,
    
    /* BDL */
    DEMO01_BDL_BA=0xB,
    DEMO01_BDL_FUKU=0xC,
    
    /* BCKS */
    DEMO01_BCK_01B_VFUKU_CUT03_TURN_O=0xD,
    DEMO01_BCK_01B_VFUKU_CUT03_TURNWAIT_L=0xE,
    DEMO01_BCK_01B_VFUKU_CUT1_WAITPRESENT_L=0xF,
    DEMO01_BCK_01B_BA_CUT1_WAITPRESENT_L=0x10,
    DEMO01_BCK_01_ROLL_FUKU=0x1A,
    DEMO01_BCK_BA_WAIT_L=0x1B,
    
    /* BRK */
    DEMO01_BRK_FADEBOX_INVISIBLE=0x12,
    DEMO01_BRK_FADE_IN45F=0x13,
    DEMO01_BRK_FADE_OUT15F=0x14,
    DEMO01_BRK_FADE_OUT30F=0x15,
    DEMO01_BRK_FADEBOX_BLACK=0x16,
    DEMO01_BRK_FADE_IN15F=0x17,
    
    /* BDLM */
    DEMO01_BDL_BLACKFADEBOX=0x18,
};

enum DEMO01_RES_FILE_INDEX {
    /* STB */
    DEMO01_INDEX_STB_TALE=0x7,
    DEMO01_INDEX_STB_TALE_2=0x8,
    
    /* BDL */
    DEMO01_INDEX_BDL_BA=0xB,
    DEMO01_INDEX_BDL_FUKU=0xC,
    
    /* BCKS */
    DEMO01_INDEX_BCK_01B_VFUKU_CUT03_TURN_O=0xF,
    DEMO01_INDEX_BCK_01B_VFUKU_CUT03_TURNWAIT_L=0x10,
    DEMO01_INDEX_BCK_01B_VFUKU_CUT1_WAITPRESENT_L=0x11,
    DEMO01_INDEX_BCK_01B_BA_CUT1_WAITPRESENT_L=0x12,
    DEMO01_INDEX_BCK_01_ROLL_FUKU=0x13,
    DEMO01_INDEX_BCK_BA_WAIT_L=0x14,
    
    /* BRK */
    DEMO01_INDEX_BRK_FADEBOX_INVISIBLE=0x17,
    DEMO01_INDEX_BRK_FADE_IN45F=0x18,
    DEMO01_INDEX_BRK_FADE_OUT15F=0x19,
    DEMO01_INDEX_BRK_FADE_OUT30F=0x1A,
    DEMO01_INDEX_BRK_FADEBOX_BLACK=0x1B,
    DEMO01_INDEX_BRK_FADE_IN15F=0x1C,
    
    /* BDLM */
    DEMO01_INDEX_BDL_BLACKFADEBOX=0x1F,
};

#endif /* RES_DEMO01_H */
