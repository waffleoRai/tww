//
// Generated by dtk
// Translation Unit: d_a_obj_doguu_demo.cpp
//

#include "d/actor/d_a_obj_doguu_demo.h"
#include "d/res/res_doguud.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjDoguuD_c*)i_this)->CreateHeap();
}

/* 00000098-00000214       .text CreateHeap__13daObjDoguuD_cFv */
BOOL daObjDoguuD_c::CreateHeap() {
    mUnusedParam = fopAcM_GetParam(this) & 0xFF;

    J3DModelData* modelData = (J3DModelData*)(dComIfG_getObjectRes("DoguuD", DOGUUD_BDL_ESKZTO));
    JUT_ASSERT(0x65, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x00, 0x11020203);
    if (mpModel == NULL)
        return FALSE;

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

    mpBgW = new dBgW();

    if (mpBgW == NULL) {
        return FALSE;
    }

    if (mpBgW->Set((cBgD_t*)dComIfG_getObjectRes("DoguuD", DOGUUD_DZB_ESKZTO), cBgW::MOVE_BG_e, &mMtx))
        return FALSE;

    return TRUE;
}

/* 00000214-00000294       .text CreateInit__13daObjDoguuD_cFv */
void daObjDoguuD_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -30000.0f, -5000.0f, -30000.0f, 30000.0f, 40000.0f, 30000.0f);
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mBgwRegistered = true;
    set_mtx();
}

/* 00000294-00000314       .text set_mtx__13daObjDoguuD_cFv */
void daObjDoguuD_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

s32 daObjDoguuD_c::_create() {
    fopAcM_SetupActor(this, daObjDoguuD_c);
    mBgwRegistered = false;

    s32 phase_state = dComIfG_resLoad(&mPhs, "DoguuD");

    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x1460)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }

    return phase_state;
}

/* 00000314-000003BC       .text daObjDoguuD_create__FPv */
static s32 daObjDoguuD_create(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_create();
}

BOOL daObjDoguuD_c::_delete() {
    if (heap != NULL && mBgwRegistered == true)
        dComIfG_Bgsp()->Release(mpBgW);

    dComIfG_resDelete(&mPhs, "DoguuD");
    return TRUE;
}

/* 000003BC-00000424       .text daObjDoguuD_Delete__FPv */
static BOOL daObjDoguuD_Delete(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_delete();
}

BOOL daObjDoguuD_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 00000424-000004C8       .text daObjDoguuD_Draw__FPv */
static BOOL daObjDoguuD_Draw(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_draw();
}

BOOL daObjDoguuD_c::_execute() {
    if (demoActorID != 0) {
        dDemo_actor_c* demoAc = dComIfGp_demo_getActor(demoActorID);
        if (demoAc != NULL && demoAc->checkEnable(0x10)) {
            mShape = demoAc->mShapeId;
        }
    }
    set_mtx();
    return TRUE;
}

/* 000004C8-00000538       .text daObjDoguuD_Execute__FPv */
static BOOL daObjDoguuD_Execute(void* i_this) {
    return ((daObjDoguuD_c*)i_this)->_execute();
}

/* 00000538-00000540       .text daObjDoguuD_IsDelete__FPv */
static BOOL daObjDoguuD_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_DoguuDMethodTable = {
    (process_method_func)daObjDoguuD_create,
    (process_method_func)daObjDoguuD_Delete,
    (process_method_func)daObjDoguuD_Execute,
    (process_method_func)daObjDoguuD_IsDelete,
    (process_method_func)daObjDoguuD_Draw,
};

actor_process_profile_definition g_profile_Obj_DoguuD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_DoguuD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjDoguuD_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x01C5,
    /* Actor SubMtd */ &daObj_DoguuDMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
