//
// Generated by dtk
// Translation Unit: JASCmdStack.cpp
//

#include "JSystem/JAudio/JASCmdStack.h"
#include "JSystem/JAudio/JASCallback.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "dolphin/types.h"

/* 8027D6F4-8027D70C       .text __ct__Q38JASystem6Kernel8TPortCmdFv */
JASystem::Kernel::TPortCmd::TPortCmd() {
    field_0x0 = NULL;
    field_0x4 = NULL;
    field_0x8 = NULL;
    field_0xc = NULL;
}

JASystem::Kernel::TPortHead cmd_once;

/* 8027D70C-8027D730       .text addPortCmdOnce__Q38JASystem6Kernel8TPortCmdFv */
bool JASystem::Kernel::TPortCmd::addPortCmdOnce() {
    return addPortCmd(&cmd_once);
}

/* 8027D730-8027D7E8       .text setPortCmd__Q38JASystem6Kernel8TPortCmdFPFPQ38JASystem6Kernel9TPortArgs_vPQ38JASystem6Kernel9TPortArgs */
bool JASystem::Kernel::TPortCmd::setPortCmd(void (*func)(JASystem::Kernel::TPortArgs*), JASystem::Kernel::TPortArgs* pargs) {
    JUT_ASSERT(83, func != NULL);
    JUT_ASSERT(84, pargs != NULL);
    field_0x8 = func;
    field_0xc = pargs;
    field_0x0 = NULL;
    return 1;
}

/* 8027D7E8-8027D8A4       .text addPortCmd__Q38JASystem6Kernel8TPortCmdFPQ38JASystem6Kernel9TPortHead */
bool JASystem::Kernel::TPortCmd::addPortCmd(JASystem::Kernel::TPortHead* phead) {
    /* Nonmatching */
    JUT_ASSERT(105, phead != NULL);
    BOOL enable = OSDisableInterrupts();
    if (field_0x0) {
        OSRestoreInterrupts(enable);
        return false;
    }
    if (phead->field_0x4) {
        phead->field_0x4->field_0x4 = this;
    } else {
        phead->field_0x0 = this;
    }
    phead->field_0x4 = this;
    field_0x4 = NULL;
    field_0x0 = phead;
    OSRestoreInterrupts(enable);
    return true;
}

/* 8027D8A4-8027D924       .text portCmdProcOnce__Q28JASystem6KernelFPQ38JASystem6Kernel9TPortHead */
void JASystem::Kernel::portCmdProcOnce(JASystem::Kernel::TPortHead* phead) {
    JUT_ASSERT(223, phead != NULL);
    while (true) {
        TPortCmd* cmd = getPortCmd(phead);
        if (!cmd) {
            break;
        }
        cmd->field_0x8(cmd->field_0xc);
    }
}

/* 8027D924-8027D9A4       .text portCmdProcStay__Q28JASystem6KernelFPQ38JASystem6Kernel9TPortHead */
void JASystem::Kernel::portCmdProcStay(JASystem::Kernel::TPortHead* phead) {
    JUT_ASSERT(245, phead != NULL);
    TPortCmd* cmd = phead->field_0x0;
    while (true) {
        if (!cmd) {
            break;
        }
        cmd->field_0x8(cmd->field_0xc);
        cmd = cmd->field_0x4;
    }
}

/* 8027D9A4-8027DA0C       .text portHeadInit__Q28JASystem6KernelFPQ38JASystem6Kernel9TPortHead */
void JASystem::Kernel::portHeadInit(JASystem::Kernel::TPortHead* phead) {
    JUT_ASSERT(267, phead != NULL);
    phead->field_0x0 = NULL;
    phead->field_0x4 = NULL;
}

JASystem::Kernel::TPortHead cmd_stay;

/* 8027DA0C-8027DA48       .text portCmdInit__Q28JASystem6KernelFv */
void JASystem::Kernel::portCmdInit() {
    portHeadInit(&cmd_once);
    portHeadInit(&cmd_stay);
    registerDspCallback(portCmdMain, NULL);
}

/* 8027DA48-8027DB08       .text getPortCmd__Q28JASystem6KernelFPQ38JASystem6Kernel9TPortHead */
JASystem::Kernel::TPortCmd* JASystem::Kernel::getPortCmd(JASystem::Kernel::TPortHead* phead) {
    TPortCmd* r31;
    TPortCmd* r30 = NULL;
    JUT_ASSERT(311, phead != NULL);
    r31 = phead->field_0x0;
    if (r31) {
        r30 = r31;
        phead->field_0x0 = r31->field_0x4;
        if (!phead->field_0x0) {
            phead->field_0x4 = NULL;
        }
        if (phead != r31->field_0x0) {
            OSReport("[JASKernel::getPortCmd] 不正な登録データブロックです。\n");
        }
        r31->field_0x0 = NULL;
    }
    return r30;
}

/* 8027DB08-8027DB38       .text portCmdMain__Q28JASystem6KernelFPv */
s32 JASystem::Kernel::portCmdMain(void*) {
    portCmdProcOnce(&cmd_once);
    portCmdProcStay(&cmd_stay);
    return 0;
}
