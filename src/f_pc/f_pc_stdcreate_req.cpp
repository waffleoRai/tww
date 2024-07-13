//
// Generated by dtk
// Translation Unit: f_pc_stdcreate_req.cpp
//

#include "f_pc/f_pc_stdcreate_req.h"
#include "f_pc/f_pc_load.h"
#include "f_pc/f_pc_node.h"
#include "f_pc/f_pc_manager.h"

/* 80040648-8004069C       .text fpcSCtRq_phase_Load__FP29standard_create_request_class */
s32 fpcSCtRq_phase_Load(standard_create_request_class* i_SCtReq) {
    switch (fpcLd_Load(i_SCtReq->mProcName)) {
    case cPhs_INIT_e:
        return cPhs_INIT_e;
    case cPhs_COMPLEATE_e:
        return cPhs_NEXT_e;
    case cPhs_ERROR_e:
    default:
        return cPhs_ERROR_e;
    }
}


/* 8004069C-80040704       .text fpcSCtRq_phase_CreateProcess__FP29standard_create_request_class */
s32 fpcSCtRq_phase_CreateProcess(standard_create_request_class* i_SCtReq) {
    fpcLy_SetCurrentLayer(i_SCtReq->base.mpLayer);
    i_SCtReq->base.mpRes = fpcBs_Create(i_SCtReq->mProcName, i_SCtReq->base.mBsPcId, i_SCtReq->mpUserData);
    if (i_SCtReq->base.mpRes == NULL) {
        fpcLd_Free(i_SCtReq->mProcName);
        return cPhs_ERROR_e;
    } else {
        i_SCtReq->base.mpRes->mpCtRq = (struct create_request*)i_SCtReq;
        return cPhs_NEXT_e;
    }
}

/* 80040704-8004073C       .text fpcSCtRq_phase_SubCreateProcess__FP29standard_create_request_class */
s32 fpcSCtRq_phase_SubCreateProcess(standard_create_request_class* i_SCtReq) {
    fpcLy_SetCurrentLayer(i_SCtReq->base.mpLayer);
    return fpcBs_SubCreate(i_SCtReq->base.mpRes);
}

/* 8004073C-80040794       .text fpcSCtRq_phase_IsComplete__FP29standard_create_request_class */
s32 fpcSCtRq_phase_IsComplete(standard_create_request_class* i_SCtReq) {
    process_node_class* procNode = (process_node_class*)i_SCtReq->base.mpRes;
    if (fpcBs_Is_JustOfType(g_fpcNd_type, procNode->base.mSubType) == 1) {
        if (fpcLy_IsCreatingMesg(&procNode->mLayer) == 1) {
            return cPhs_INIT_e;
        }
    }
    return cPhs_NEXT_e;
}

/* 80040794-800407E4       .text fpcSCtRq_phase_PostMethod__FP29standard_create_request_class */
s32 fpcSCtRq_phase_PostMethod(standard_create_request_class* i_SCtReq) {
    if (i_SCtReq->mpCallBack != NULL && i_SCtReq->mpCallBack(i_SCtReq->base.mpRes, i_SCtReq->mpCallBackUserData) == 0) {
        return cPhs_INIT_e;
    } else {
        return cPhs_NEXT_e;
    }
}

/* 800407E4-800407EC       .text fpcSCtRq_phase_Done__FP29standard_create_request_class */
s32 fpcSCtRq_phase_Done(standard_create_request_class* i_SCtReq) {
    return cPhs_NEXT_e;
}

/* 800407EC-8004085C       .text fpcSCtRq_Handler__FP29standard_create_request_class */
s32 fpcSCtRq_Handler(standard_create_request_class* i_SCtReq) {
    s32 phase_state = cPhs_Do(&i_SCtReq->mPhase, i_SCtReq);

    switch (phase_state) {
    case cPhs_NEXT_e:
        return fpcSCtRq_Handler(i_SCtReq);
    case cPhs_COMPLEATE_e:
        return cPhs_COMPLEATE_e;
    case cPhs_LOADING_e:
    case cPhs_ERROR_e:
    default:
        return phase_state;
    }
}

/* 8004085C-80040864       .text fpcSCtRq_Delete__FP29standard_create_request_class */
s32 fpcSCtRq_Delete(standard_create_request_class* i_SCtReq) {
    return 1;
}

/* 80040864-8004086C       .text fpcSCtRq_Cancel__FP29standard_create_request_class */
s32 fpcSCtRq_Cancel(standard_create_request_class* i_SCtReq) {
    return 1;
}

/* 8004086C-80040900       .text fpcSCtRq_Request__FP11layer_classsPFPvPv_iPvPv */
fpc_ProcID fpcSCtRq_Request(layer_class* i_layer, s16 i_procName, stdCreateFunc i_createFunc, void* param_4, void* param_5) {
    static create_request_method_class submethod = {
        (cPhs__Handler)fpcSCtRq_Handler,
        (process_method_func)fpcSCtRq_Cancel,
        (process_method_func)fpcSCtRq_Delete,
    };

    static cPhs__Handler method[] = {
        (cPhs__Handler)fpcSCtRq_phase_Load,
        (cPhs__Handler)fpcSCtRq_phase_CreateProcess,
        (cPhs__Handler)fpcSCtRq_phase_SubCreateProcess,
        (cPhs__Handler)fpcSCtRq_phase_IsComplete,
        (cPhs__Handler)fpcSCtRq_phase_PostMethod,
        (cPhs__Handler)fpcSCtRq_phase_Done,
        NULL,
    };

    if (i_procName >= 0x7FFF) {
        return fpcM_ERROR_PROCESS_ID_e;
    } else {
        standard_create_request_class* request = (standard_create_request_class*)fpcCtRq_Create(i_layer, sizeof(standard_create_request_class), &submethod);
        if (request == NULL) {
            return fpcM_ERROR_PROCESS_ID_e;
        } else {
            cPhs_Set(&request->mPhase, method);
            request->mProcName = i_procName;
            request->mpCallBack = i_createFunc;
            request->mpCallBackUserData = param_4;
            request->mpUserData = param_5;
            return request->base.mBsPcId;
        }
    }
}
