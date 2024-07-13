//
// Generated by dtk
// Translation Unit: JASCallback.cpp
//

#include "JSystem/JAudio/JASCallback.h"
#include "JSystem/JAudio/JASSystemHeap.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/os/OSInterrupt.h"

u32 JASystem::Kernel::maxCallbacksUser = 16;
JASystem::Kernel::unk_callList* JASystem::Kernel::callList;
bool JASystem::Kernel::callbackInit;

/* 8027BA70-8027BB24       .text resetCallback__Q28JASystem6KernelFv */
void JASystem::Kernel::resetCallback() {
    if (callbackInit != true) {
        callList = (unk_callList*)new (JASDram, 0) unk_callList[maxCallbacksUser];
        JUT_ASSERT(58, callList != NULL);
        BOOL enable = OSDisableInterrupts();
        for (int i = 0; i < maxCallbacksUser; i++) {
            callList[i].field_0x0 = NULL;
        }
        callbackInit = true;
        OSRestoreInterrupts(enable);
    }
}

/* 8027BB24-8027BB8C       .text checkCallback__Q28JASystem6KernelFPFPv_lPv */
int JASystem::Kernel::checkCallback(s32 (*param_1)(void*), void* param_2) {
    if (callbackInit == false) {
        return -1;
    }
    for (int i = 0; i < maxCallbacksUser; i++) {
        if (callList[i].field_0x0 == param_1 && callList[i].field_0x4 == param_2) {
            return i;
        }
    }
    return -1;
}

/* 8027BB8C-8027BC24       .text registerDspCallback__Q28JASystem6KernelFPFPv_lPv */
int JASystem::Kernel::registerDspCallback(s32 (*param_1)(void*), void* param_2) {
    if (callbackInit == false) {
        return -1;
    }
    BOOL enable = OSDisableInterrupts();
    int r30 = registerSubFrameCallback(param_1, param_2);
    if (r30 == -1) {
        OSRestoreInterrupts(enable);
        return -1;
    };
    callList[r30].field_0x8 = 1;
    OSRestoreInterrupts(enable);
    return r30;
}

/* 8027BC24-8027BD14       .text registerSubFrameCallback__Q28JASystem6KernelFPFPv_lPv */
int JASystem::Kernel::registerSubFrameCallback(s32 (*param_1)(void*), void* param_2) {
    if (callbackInit == false) {
        return -1;
    }
    int idx;
    for (idx = 0; idx < maxCallbacksUser; idx++) {
        if (callList[idx].field_0x0 == NULL) {
            break;
        }
    }
    if (idx == maxCallbacksUser) {
        OSReport("[JASKernel::registerAiCallbak] コールバック登録バッファが一杯です。\n");
        return -1;
    }
    if (checkCallback(param_1, param_2) != -1) {
        return -1;
    }
    BOOL enable = OSDisableInterrupts();
    callList[idx].field_0x0 = param_1;
    callList[idx].field_0x4 = param_2;
    callList[idx].field_0x8 = 0;
    OSRestoreInterrupts(enable);
    return idx;
}

/* 8027BD14-8027BDAC       .text aiCallback__Q28JASystem6KernelFv */
void JASystem::Kernel::aiCallback() {
    if (callbackInit) {
        for (int i = 0; i < maxCallbacksUser; i++) {
            if (callList[i].field_0x0 && callList[i].field_0x8 == 0) {
                int result = callList[i].field_0x0(callList[i].field_0x4);
                if (result == -1) {
                    callList[i].field_0x0 = NULL;
                }
            }
        }
    }
}

/* 8027BDAC-8027BE44       .text subframeCallback__Q28JASystem6KernelFv */
void JASystem::Kernel::subframeCallback() {
    if (callbackInit) {
        for (int i = 0; i < maxCallbacksUser; i++) {
            if (callList[i].field_0x0 && callList[i].field_0x8 == 1) {
                int result = callList[i].field_0x0(callList[i].field_0x4);
                if (result == -1) {
                    callList[i].field_0x0 = NULL;
                }
            }
        }
    }
}
