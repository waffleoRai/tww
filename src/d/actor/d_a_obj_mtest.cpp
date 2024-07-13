//
// Generated by dtk
// Translation Unit: d_a_obj_mtest.cpp
//

#include "d/actor/d_a_obj_mtest.h"
#include "d/res/res_mtest.h"
#include "d/res/res_owater.h"
#include "d/res/res_astop.h"
#include "d/d_procname.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"

// Needed for the .data and .bss sections to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};
static u8 dummy5[0x4C];

char* daObjMtest::Act_c::M_arcname[Type_Max] = {
    "Mtest",
    "Mtest",
    "Mtest",
    "Mtest",
    "Mtest",
    "Mtest",
    "Owater",
    "Astop",
};

cXyz daObjMtest::Act_c::M_scl_mult[Type_Max] = {
    cXyz(1.0f,  1.0f,  1.0f),
    cXyz(1.0f,  0.5f,  1.0f),
    cXyz(10.0f, 10.0f, 10.0f),
    cXyz(10.0f, 5.0f,  10.0f),
    cXyz(0.2f,  0.2f,  0.2f),
    cXyz(0.2f,  0.2f,  0.2f),
    cXyz(1.0f,  1.0f,  1.0f),
    cXyz(40.0f, 1.0f,  40.0f),
};

const dCcD_SrcCyl daObjMtest::Act_c::M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
        /* Height */ 100.0f,
    },
};

/* 000000EC-00000198       .text chk_appear__Q210daObjMtest5Act_cFv */
bool daObjMtest::Act_c::chk_appear() {
    s32 swSave = prm_get_swSave();
    s32 arg0 = prm_get_arg0();
    if (arg0 == 0) {
        return fopAcM_isSwitch(this, swSave) ? true : false;
    } else if (arg0 == 1) {
        return !fopAcM_isSwitch(this, swSave) ? true : false;
    } else {
        return true;
    }
}

/* 00000198-00000284       .text CreateHeap__Q210daObjMtest5Act_cFv */
BOOL daObjMtest::Act_c::CreateHeap() {
    static s16 bmd_data[Type_Max] = {
        MTEST_BMD_MCUBE,
        MTEST_BMD_MCYLN,
        MTEST_BMD_MCUBE,
        MTEST_BMD_MCYLN,
        -1,
        -1,
        -1,
        -1,
    };
    
    s16 bmdIdx = bmd_data[M_type];
    if (bmdIdx >= 0) {
        J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname[M_type], bmdIdx);
        JUT_ASSERT(257, model_data != NULL);
        
        mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);
        return !!mpModel;
    } else {
        mpModel = NULL;
        return TRUE;
    }
}

/* 00000284-000003E8       .text Create__Q210daObjMtest5Act_cFv */
BOOL daObjMtest::Act_c::Create() {
    fopAcM_SetMtx(this, mMtx);
    init_mtx();
    
    if (M_type == Type_MwtrSB || M_type == Type_MygnSB) {
        fopAcM_setCullSizeBox(this, -3000.0f, -10.0f, -3000.0f, 3000.0f, 10.0f, 3000.0f);
    } else if (M_type != Type_Owater) {
        fopAcM_setCullSizeBox(this, -51.0f, -1.0f, -51.0f, 51.0f, 101.0f, 51.0f);
    }
    
    if (M_type == Type_Astop) {
        fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
    }
    
    if (prm_get_arg1() == 0) {
        mStts.Init(0xFF, 0xFF, this);
        mCyl.Set(M_cyl_src);
        mCyl.SetStts(&mStts);
        mCyl.SetTgVec((cXyz&)cXyz::Zero);
        mCyl.OnTgNoHitMark();
        f32 scaleMag = scale.x < scale.z ? scale.x : scale.z;
        mCyl.SetR(scaleMag * 50.0f);
        mCyl.SetH(scale.y * 100.0f);
    }
    
    return TRUE;
}

/* 000003E8-00000708       .text Mthd_Create__Q210daObjMtest5Act_cFv */
s32 daObjMtest::Act_c::Mthd_Create() {
    static s16 dzb_data[5][Type_Max] = {
        {
            MTEST_DZB_MCUBE,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MCUBE,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MWTRSB,
            MTEST_DZB_MYGNSB,
            OWATER_DZB_OWATER,
            ASTOP_DZB_ASLOW,
        },
        {
            MTEST_DZB_MCUBEHG,
            MTEST_DZB_MCYLNHG,
            MTEST_DZB_MCUBEHG,
            MTEST_DZB_MCYLNHG,
            MTEST_DZB_MWTRSB,
            MTEST_DZB_MYGNSB,
            OWATER_DZB_OWATER,
            ASTOP_DZB_ASLOW00,
        },
        {
            MTEST_DZB_MCUBENC,
            MTEST_DZB_MCYLNNC,
            MTEST_DZB_MCUBENC,
            MTEST_DZB_MCYLNNC,
            MTEST_DZB_MWTRSB,
            MTEST_DZB_MYGNSB,
            OWATER_DZB_OWATER,
            ASTOP_DZB_ASTOP,
        },
        {
            MTEST_DZB_MCUBELK,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MCUBELK,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MWTRSB,
            MTEST_DZB_MYGNSB,
            OWATER_DZB_OWATER,
            ASTOP_DZB_ASTOP00,
        },
        {
            MTEST_DZB_MCUBE,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MCUBE,
            MTEST_DZB_MCYLN,
            MTEST_DZB_MWTRSB,
            MTEST_DZB_MYGNSB,
            OWATER_DZB_OWATER,
            ASTOP_DZB_A00,
        },
    };
    static u32 heap_size[5][Type_Max] = {
        {
            0x1620,
            0x20A0,
            0x1620,
            0x20A0,
            0x0200,
            0x0200,
            0x4000,
            0x4000,
        },
        {
            0x1620,
            0x20A0,
            0x1620,
            0x20A0,
            0x0200,
            0x0200,
            0x4000,
            0x4000,
        },
        {
            0x1620,
            0x20A0,
            0x1620,
            0x20A0,
            0x0200,
            0x0200,
            0x4000,
            0x4000,
        },
        {
            0x1620,
            0x20A0,
            0x1620,
            0x20A0,
            0x0200,
            0x0200,
            0x4000,
            0x4000,
        },
        {
            0x1620,
            0x20A0,
            0x1620,
            0x20A0,
            0x0200,
            0x0200,
            0x4000,
            0x4000,
        },
    };
    
    fopAcM_SetupActor(this, Act_c);
    
    M_type = prm_get_type();
    JUT_ASSERT(327, M_type < Type_Max);
    
    s32 phase_state = dComIfG_resLoad(&mPhase, M_arcname[M_type]);
    if (phase_state == cPhs_COMPLEATE_e) {
        s32 dzb_idx = 0;
        if (prm_get_arg1() == 1) {
            dzb_idx = 1;
        } else if (prm_get_arg1() == 2) {
            dzb_idx = 2;
        } else if (prm_get_arg1() == 3) {
            dzb_idx = 3;
        } else if (prm_get_arg1() == 4) {
            dzb_idx = 4;
        }
        
        mbAppear = chk_appear();
        
        cXyz& scl_mult = M_scl_mult[M_type];
        scale.x *= scl_mult.x;
        scale.y *= scl_mult.y;
        scale.z *= scl_mult.z;
        
        phase_state = MoveBGCreate(M_arcname[M_type], dzb_data[dzb_idx][M_type], NULL, heap_size[dzb_idx][M_type]);
        
        JUT_ASSERT(451, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
        
        if (phase_state == cPhs_COMPLEATE_e) {
            mpBgW->SetLock();
            if (mbAppear == 0) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
        }
    }
    
    return phase_state;
}

/* 00000958-00000960       .text Delete__Q210daObjMtest5Act_cFv */
BOOL daObjMtest::Act_c::Delete() {
    return TRUE;
}

/* 00000960-000009B8       .text Mthd_Delete__Q210daObjMtest5Act_cFv */
BOOL daObjMtest::Act_c::Mthd_Delete() {
    s32 result = MoveBGDelete();
    dComIfG_resDelete(&mPhase, M_arcname[M_type]);
    return result;
}

/* 000009B8-00000A4C       .text set_mtx__Q210daObjMtest5Act_cFv */
void daObjMtest::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    if (mpModel) {
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    mDoMtx_stack_c::scaleM(scale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000A4C-00000A90       .text init_mtx__Q210daObjMtest5Act_cFv */
void daObjMtest::Act_c::init_mtx() {
    if (mpModel) {
        mpModel->setBaseScale(scale);
    }
    set_mtx();
}

/* 00000A90-00000B80       .text Execute__Q210daObjMtest5Act_cFPPA3_A4_f */
BOOL daObjMtest::Act_c::Execute(Mtx** pMtx) {
    bool appear = chk_appear();
    
    if (mCyl.ChkTgHit()) {
        fopAcM_delete(this);
    } else if (appear) {
        if (!mbAppear) {
            dComIfG_Bgsp()->Regist(mpBgW, this);
        }
        if (prm_get_arg1() == 0) {
            mCyl.MoveCAtTg(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);
        }
    } else if (mbAppear) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    
    *pMtx = &mMtx;
    mbAppear = appear;
    return TRUE;
}

/* 00000B80-00000C64       .text Draw__Q210daObjMtest5Act_cFv */
BOOL daObjMtest::Act_c::Draw() {
    if (mbAppear && mpModel && prm_get_arg1() != 3 && prm_get_arg1() != 4) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        dComIfGd_setListBG();
        mDoExt_modelUpdateDL(mpModel);
        dComIfGd_setList();
    }
    return TRUE;
}

namespace daObjMtest {
    namespace {
        s32 Mthd_Create(void* i_this) {
            return ((Act_c*)i_this)->Mthd_Create();
        }
        
        BOOL Mthd_Delete(void* i_this) {
            return ((Act_c*)i_this)->Mthd_Delete();
        }
        
        BOOL Mthd_Execute(void* i_this) {
            return ((Act_c*)i_this)->MoveBGExecute();
        }
        
        BOOL Mthd_Draw(void* i_this) {
            return ((Act_c*)i_this)->MoveBGDraw();
        }
        
        BOOL Mthd_IsDelete(void* i_this) {
            return ((Act_c*)i_this)->MoveBGIsDelete();
        }
        
        static actor_method_class Mthd_Table = {
            (process_method_func)Mthd_Create,
            (process_method_func)Mthd_Delete,
            (process_method_func)Mthd_Execute,
            (process_method_func)Mthd_IsDelete,
            (process_method_func)Mthd_Draw,
        };
    }
}

actor_process_profile_definition g_profile_Obj_Mtest = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Mtest,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMtest::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x002B,
    /* Actor SubMtd */ &daObjMtest::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
