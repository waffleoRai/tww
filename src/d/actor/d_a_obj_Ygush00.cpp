//
// Generated by dtk
// Translation Unit: d_a_obj_Ygush00.cpp
//

#include "d/actor/d_a_obj_Ygush00.h"
#include "f_op/f_op_actor_mng.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_procname.h"
#include "d/actor/d_a_obj_gryw00.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

namespace {
    static const char l_arcname[] = "Ygush00";
};

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

/* 00000078-0000009C       .text solidHeapCB__14daObjYgush00_cFP10fopAc_ac_c */
BOOL daObjYgush00_c::solidHeapCB(fopAc_ac_c* ac) {
    return ((daObjYgush00_c*)ac)->create_heap();
}

/* 0000009C-00000250       .text create_heap__14daObjYgush00_cFv */
bool daObjYgush00_c::create_heap() {
    static u32 mdl_table[] = { 0x0A, 0x09, 0x09, 0x09 };
    static u32 btk_table[] = { 0x0E, 0x0D, 0x0D, 0x0D };
    static u32 bck_table[] = { 0x06, 0x05, 0x05, 0x05 };

    bool ret = true;

    J3DModelData* pModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, mdl_table[mType]));
    J3DAnmTextureSRTKey * pBtk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes(l_arcname, btk_table[mType]));
    J3DAnmTransform * pBck = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes(l_arcname, bck_table[mType]));

    if (!pModelData || !pBtk || !pBck) {
        JUT_ASSERT(207, 0);
        ret = false;
    } else {
        mpModel = mDoExt_J3DModel__create(pModelData, 0x80000, 0x11000222);
        s32 btkRet = mBtkAnm.init(pModelData, pBtk, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false, 0);
        s32 bckRet = mBckAnm.init(pModelData, pBck, 1, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);

        if (!mpModel || !btkRet || !bckRet)
            ret = false;
    }

    return ret;
}

/* 00000250-000003F4       .text _create__14daObjYgush00_cFv */
s32 daObjYgush00_c::_create() {
    fopAcM_SetupActor(this, daObjYgush00_c);

    if (fpcM_IsFirstCreating(this)) {
        u32 type = daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        mType = type;
        if ((int)mType < 0 || 4 <= (int)mType)
            mType = 0;
    }

    s32 ret = dComIfG_resLoad(&mPhs, l_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x740) == 1) {
            mpModel->setBaseScale(mScale);
            mDoMtx_stack_c::transS(current.pos);
            mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

            fopAcM_setCullSizeBox(this,
                mScale.x * -80.0f, 0.0f, mScale.z * -80.0f,
                mScale.x * 80.0f, mScale.y * 125.0f, mScale.z * 80.0f);
        } else {
            ret = cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 000004F4-00000524       .text _delete__14daObjYgush00_cFv */
bool daObjYgush00_c::_delete() {
    dComIfG_resDelete(&mPhs, l_arcname);
    return true;
}

/* 00000524-0000066C       .text _execute__14daObjYgush00_cFv */
bool daObjYgush00_c::_execute() {
    if (mType != 3 || dComIfGs_isEventBit(EV_BIT_TALKED_TO_IRCH_IN_FOREST_HAVEN) == 1) {
        mBtkAnm.play();
        mBckAnm.play();
    }

    if (mType == 1) {
        if (mpGryw00 != NULL) {
            if (mpGryw00->get_draw_water_lv(mpGryw00) <= current.pos.y) {
                fopAcM_seStartCurrent(this, JA_SE_OBJ_SPRING, 0);
            }
        } else {
            mpGryw00 = (daObjGryw00_c*)fopAcM_SearchByName(PROC_Obj_Gryw00);
        }
    } else {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_SPRING, 0);
    }

    return true;
}

/* 0000066C-000006FC       .text _draw__14daObjYgush00_cFv */
bool daObjYgush00_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &mTevStr);
    g_env_light.setLightTevColorType(mpModel, &mTevStr);
    mBtkAnm.entry(mpModel->getModelData());
    mBckAnm.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 000006FC-0000071C       .text daObjYgush00_Create__FP14daObjYgush00_c */
static s32 daObjYgush00_Create(daObjYgush00_c* i_this) {
    return i_this->_create();
}

/* 0000071C-00000740       .text daObjYgush00_Delete__FP14daObjYgush00_c */
static BOOL daObjYgush00_Delete(daObjYgush00_c* i_this) {
    return i_this->_delete();
}

/* 00000740-00000764       .text daObjYgush00_Execute__FP14daObjYgush00_c */
static BOOL daObjYgush00_Execute(daObjYgush00_c* i_this) {
    return i_this->_execute();
}

/* 00000764-00000788       .text daObjYgush00_Draw__FP14daObjYgush00_c */
static BOOL daObjYgush00_Draw(daObjYgush00_c* i_this) {
    return i_this->_draw();
}

/* 00000788-00000790       .text daObjYgush00_IsDelete__FP14daObjYgush00_c */
static BOOL daObjYgush00_IsDelete(daObjYgush00_c* i_this) {
    return TRUE;
}

static actor_method_class l_daObjYgush00_Method = {
    (process_method_func)daObjYgush00_Create,
    (process_method_func)daObjYgush00_Delete,
    (process_method_func)daObjYgush00_Execute,
    (process_method_func)daObjYgush00_IsDelete,
    (process_method_func)daObjYgush00_Draw,
};

actor_process_profile_definition g_profile_Obj_Ygush00 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 3,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ygush00,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daObjYgush00_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x005E,
    /* Actor SubMtd */ &l_daObjYgush00_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
