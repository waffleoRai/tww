//
// Generated by dtk
// Translation Unit: JASHardStream.cpp
//

#include "JSystem/JAudio/JASHardStream.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "string.h"
#include "dolphin/ai/ai.h"
#include "dolphin/dvd/dvd.h"
#include "dolphin/os/OS.h"

JASystem::HardStream::TControl JASystem::HardStream::strCtrl;
bool JASystem::HardStream::useHardStreaming;
char* JASystem::HardStream::streamFiles;
JASystem::HardStream::TPlayList* JASystem::HardStream::playList;
int JASystem::HardStream::playListMax = 32;

/* 8027BE44-8027BEA4       .text unregistBgmAll__Q28JASystem10HardStreamFv */
int JASystem::HardStream::unregistBgmAll() {
    if (strCtrl.getList() == NULL) {
        return 0;
    }
    strCtrl.setList(NULL);
    for (int i = 0; i < playListMax; i++) {
        playList[i].clear();
    }
    return 1;
}

char JASystem::HardStream::rootDir[32] = "";

/* 8027BEA4-8027C318       .text main__Q28JASystem10HardStreamFv */
void JASystem::HardStream::main() {
    static DVDFileInfo finfo[3];
    static u32 cur_finfo = 0;
    static u8 cur_addr_cmd = 0;
    static DVDCommandBlock get_addr_cmd[16];
    static DVDCommandBlock stop_cmd;
    static DVDCommandBlock finish_cmd;
    if (!useHardStreaming) {
        return;
    }
    while (true) {
        u16 introNum;
        switch (strCtrl.field_0xb) {
        case 1:
            if (!strCtrl.getList()) {
                return;
            }
            introNum = strCtrl.getIntroNum();
            if (introNum != 0xffff) {
                if (!strCtrl.startFirst(introNum, finfo, &cur_finfo)) {
                    strCtrl.field_0xb = 0;
                    return;
                }
                strCtrl.field_0x8 = 0;
            } else {
                if (!strCtrl.startFirst(strCtrl.getLoopNum(), finfo, &cur_finfo)) {
                    strCtrl.field_0xb = 0;
                    return;
                }
                strCtrl.clearListOne();
                strCtrl.field_0x8 = 1;
            }
            strCtrl.field_0xb = 3;
            return;
        case 2:
            if (strCtrl.field_0x8 == 0) {
                u16 loopNum = strCtrl.getLoopNum();
                if (loopNum != 0xffff) {
                    if (!strCtrl.startSecond(loopNum, finfo, &cur_finfo)) {
                        strCtrl.field_0xb = 0;
                        return;
                    }
                    strCtrl.clearListOne();
                    strCtrl.field_0x8 = 1;
                    strCtrl.field_0xb = 4;
                    return;
                }
            }
            strCtrl.clearListOne();
            if (!strCtrl.getList()) {
                if (strCtrl.field_0x8 == 0) {
                    DVDStopStreamAtEndAsync(&stop_cmd, 0);
                    strCtrl.field_0xb = 4;
                    strCtrl.field_0x8 = 2;
                    return;
                }
                strCtrl.field_0x8 = 3;
                strCtrl.field_0xb = 4;
                return;
            }
            introNum = strCtrl.getIntroNum();
            if (introNum != 0xffff) {
                if (!strCtrl.startSecond(introNum, finfo, &cur_finfo)) {
                    strCtrl.field_0xb = 0;
                    return;
                }
                strCtrl.field_0x8 = 0;
            } else {
                if (!strCtrl.startSecond(strCtrl.getLoopNum(), finfo, &cur_finfo)) {
                    strCtrl.field_0xb = 0;
                    return;
                }
                strCtrl.clearListOne();
                strCtrl.field_0x8 = 1;
            }
            strCtrl.field_0xb = 4;
            return;
        case 4:
            u8 currentVol = strCtrl.getCurVol();
            AISetStreamVolLeft(currentVol);
            AISetStreamVolRight(currentVol);
            DVDGetStreamPlayAddrAsync(&get_addr_cmd[cur_addr_cmd], getAddrCallback);
            cur_addr_cmd++;
            cur_addr_cmd %= 16;
            return;
        case 5:
            TPlayList* list = strCtrl.getList();
            if (!list) {
                if (strCtrl.field_0x8 != 2) {
                    strCtrl.field_0x8 = 3;
                }
                strCtrl.field_0xb = 4;
                return;
            }
            if (strCtrl.field_0x8 == 0) {
                if (list->getPair()->getLoop() == 0xffff) {
                    if (list->getNext() == NULL) {
                        DVDStopStreamAtEndAsync(&stop_cmd, 0);
                        strCtrl.clearListOne();
                        strCtrl.field_0x8 = 2;
                    } else {
                        strCtrl.clearListOne();
                        strCtrl.field_0x8 = 1;
                        break;
                    }
                } else {
                    if (!strCtrl.startSecond(strCtrl.getLoopNum(), finfo, &cur_finfo)) {
                        strCtrl.field_0xb = 0;
                        return;
                    }
                    strCtrl.clearListOne();
                    strCtrl.field_0x8 = 1;
                }
            } else if (!list) {
                strCtrl.field_0x8 = 3;
                strCtrl.field_0xb = 4;
            } else {
                introNum = strCtrl.getIntroNum();
                if (introNum == 0xffff) {
                    strCtrl.field_0x8 = 0;
                    break;
                }
                if (!strCtrl.startSecond(introNum, finfo, &cur_finfo)) {
                    strCtrl.field_0xb = 0;
                    return;
                }
                strCtrl.field_0x8 = 0;
            }
            strCtrl.field_0xb = 4;
            return;
        case 6:
            AISetStreamVolLeft(0);
            AISetStreamVolRight(0);
            AISetStreamPlayState(0);
            DVDCancelStreamAsync(&finish_cmd, NULL);
            strCtrl.field_0xb = 0;
            strCtrl.field_0x8 = 0;
            strCtrl.resetFader();
            strCtrl.field_0xa = 0;
            return;
        case 0:
        case 3:
        default:
            return;
        }
    }
}

/* 8027C318-8027C39C       .text firstBgmCallback__Q28JASystem10HardStreamFlP11DVDFileInfo */
void JASystem::HardStream::firstBgmCallback(s32, DVDFileInfo*) {
    if (strCtrl.field_0xa == 0) {
        u8 vol = strCtrl.getCurVol();
        AISetStreamVolLeft(vol);
        AISetStreamVolRight(vol);
        AISetStreamSampleRate(1);
        AIResetStreamSampleCount();
        AISetStreamPlayState(1);
        strCtrl.field_0xb = 2;
    } else {
        strCtrl.field_0xb = 4;
        strCtrl.field_0xa = 0;
    }
}

/* 8027C39C-8027C3B0       .text secondBgmCallback__Q28JASystem10HardStreamFlP11DVDFileInfo */
void JASystem::HardStream::secondBgmCallback(s32, DVDFileInfo*) {
    strCtrl.field_0xb = 4;
}

/* 8027C3B0-8027C4E4       .text getAddrCallback__Q28JASystem10HardStreamFlP15DVDCommandBlock */
void JASystem::HardStream::getAddrCallback(s32 param_1, DVDCommandBlock* param_2) {
    static BOOL last_frame = 0;
    if (strCtrl.field_0x8 == 3) {
        if (param_1 == strCtrl.field_0x44[strCtrl.field_0x4c ^ 1]) {
            last_frame = true;
        } else if (last_frame) {
            last_frame = false;
            strCtrl.field_0xb = 5;
        }
    } else if (strCtrl.field_0x8 == 2) {
        if (param_1 == strCtrl.field_0x44[strCtrl.field_0x4c ^ 1] - 0x8000) {
            last_frame = true;
        } else if (last_frame) {
            strCtrl.field_0xb = 6;
            unregistBgmAll();
            last_frame = false;
        }
    } else {
        if (param_1 == strCtrl.getLastAddr()) {
            last_frame = true;
        } else if (last_frame) {
            last_frame = false;
            strCtrl.field_0xb = 5;
        }
    }
}

static float dummy1() {
    return 0.0f;
}

/* 8027C4E4-8027C544       .text __ct__Q38JASystem10HardStream8TControlFv */
JASystem::HardStream::TControl::TControl() {
    field_0x0 = 0;
    mpList = NULL;
    field_0xa = 0;
    field_0x8 = 0;
    field_0xb = 0;
    field_0xc = 1.0f;
    field_0x10 = 0.0f;
    field_0x14 = 0;
    field_0x18 = 0;
    field_0x1c = 0;
    field_0x20 = 0.0f;
    field_0x24 = 0.0f;
    field_0x2c = 1.0f;
    field_0x30 = 1.0f;
    field_0x28 = 1.0f;
    field_0x34 = 0.0f;
    field_0x38 = 0;
    field_0x3c = 0;
    field_0x40 = 0;
    field_0x4c = 0;
}

/* 8027C544-8027C57C       .text getIntroNum__Q38JASystem10HardStream8TControlFv */
u16 JASystem::HardStream::TControl::getIntroNum() {
    if (!mpList) {
        return 0xffff;
    }
    if (mpList->getPair() == NULL) {
        return 0xffff;
    }
    return mpList->getPair()->getIntro();
}

/* 8027C57C-8027C5B4       .text getLoopNum__Q38JASystem10HardStream8TControlFv */
u16 JASystem::HardStream::TControl::getLoopNum() {
    if (!mpList) {
        return 0xffff;
    }
    if (mpList->getPair() == NULL) {
        return 0xffff;
    }
    return mpList->getPair()->getLoop();
}

static void dummy2() {
    OSReport(__FILE__);
    OSReport("playPairs != 0");
    OSReport("Halt");
    OSReport("playList != 0");
    OSReport("name != 0");
    OSReport("[JASHardStream::setRootDir] ディレクトリ(%s)名が長すぎます。\n");
    OSReport("filename != 0");
    OSReport("streamFiles != 0");
    OSReport("[JASHardStream::setFile] このID(%d)には既にファイルが登録されています。\n");
    OSReport("pair_id < playPairsMax");
    OSReport("[JASHardStream::setBgmPair] このＢＧＭペアID(%d)は既に使用されています。\n");
    OSReport("[JASHardStream::setBgmPair] イントロ部のＢＧＭ番号指定が大きすぎます。(%d)\n");
    OSReport("[JASHardStream::setBgmPair] ループ部のＢＧＭ番号指定が大きすぎます。(%d)\n");
    OSReport("[JASHardStream::registBgmPair] このペア(%d)にはイントロ／ループともにありませんので登録できません。\n");
    OSReport("new_list != 0");
    OSReport("[JASHardStream::playBgm] まだ前の曲が再生中ですので、新たに開始できません。\n");
}

/* 8027C5B4-8027C648       .text fileOpen__Q38JASystem10HardStream8TControlFUsP11DVDFileInfo */
BOOL JASystem::HardStream::TControl::fileOpen(u16 param_1, DVDFileInfo* fileinfo) {
    char buffer[64];
    char* ptr = streamFiles + param_1 * 0x24;
    strcpy(buffer, rootDir);
    strcat(buffer, ptr);
    if (!DVDOpen(buffer, fileinfo)) {
        OSReport("[JASHardStream::main] ファイルが開けません。(%s)\n", buffer);
        return false;
    }
    return true;
}

/* 8027C648-8027C67C       .text clearListOne__Q38JASystem10HardStream8TControlFv */
BOOL JASystem::HardStream::TControl::clearListOne() {
    if (mpList == NULL) {
        return FALSE;
    }
    TPlayList* oldList = mpList;
    mpList = mpList->getNext();
    oldList->clear();
    return TRUE;
}

/* 8027C67C-8027C710       .text setLastAddr__Q38JASystem10HardStream8TControlFP11DVDFileInfo */
void JASystem::HardStream::TControl::setLastAddr(DVDFileInfo* finfo) {
    JUT_ASSERT(906, finfo != NULL);
    field_0x44[field_0x4c] = finfo->start_address + finfo->length - 0x8000;
    field_0x4c ^= 1;
}

/* 8027C710-8027C724       .text getLastAddr__Q38JASystem10HardStream8TControlFv */
u32 JASystem::HardStream::TControl::getLastAddr() {
    return field_0x44[field_0x4c];
}

/* 8027C724-8027C7D8       .text startFirst__Q38JASystem10HardStream8TControlFUsP11DVDFileInfoPUl */
BOOL JASystem::HardStream::TControl::startFirst(u16 param_1, DVDFileInfo* param_2, u32* param_3) {
    if (!fileOpen(param_1, param_2 + *param_3)) {
        return false;
    }
    setLastAddr(param_2 + *param_3);
    DVDPrepareStreamAsync(param_2 + *param_3, 0, 0, firstBgmCallback);
    param_3[0]++;
    param_3[0] %= 3;
    return true;
}

/* 8027C7D8-8027C88C       .text startSecond__Q38JASystem10HardStream8TControlFUsP11DVDFileInfoPUl */
BOOL JASystem::HardStream::TControl::startSecond(u16 param_1, DVDFileInfo* param_2, u32* param_3) {
    if (!fileOpen(param_1, param_2 + *param_3)) {
        return false;
    }
    setLastAddr(param_2 + *param_3);
    DVDPrepareStreamAsync(param_2 + *param_3, 0, 0, secondBgmCallback);
    param_3[0]++;
    param_3[0] %= 3;
    return true;
}

/* 8027C88C-8027C8C8       .text resetFader__Q38JASystem10HardStream8TControlFv */
void JASystem::HardStream::TControl::resetFader() {
    field_0x14 = 0;
    field_0x20 = 0.0f;
    field_0x38 = 0;
    field_0x18 = 0;
    field_0x24 = 0.0f;
    field_0x3c = 0;
    field_0x30 = 1.0f;
    field_0x2c = 1.0f;
    field_0x28 = 1.0f;
    field_0x1c = 0;
    field_0x40 = 0;
}

/* 8027C8C8-8027C900       .text getCurVol__Q38JASystem10HardStream8TControlFv */
u8 JASystem::HardStream::TControl::getCurVol() {
    calcCurVolume();
    return volFloatToU8(field_0x10);
}

/* 8027C900-8027CB5C       .text calcCurVolume__Q38JASystem10HardStream8TControlFv */
void JASystem::HardStream::TControl::calcCurVolume() {
    /* Nonmatching */
}

/* 8027CB5C-8027CB9C       .text volFloatToU8__Q38JASystem10HardStream8TControlFf */
u8 JASystem::HardStream::TControl::volFloatToU8(f32 param_1) {
    /* Nonmatching */
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
    if (param_1 < 0.0f) {
        param_1 = 0.0f;
    }
    return param_1 * 255.0f;
}
