//
// Generated by dtk
// Translation Unit: d_a_obj_hbrf1.cpp
//

#include "d/actor/d_a_obj_hbrf1.h"
#include "d/d_procname.h"

/* 00000078-0000012C       .text CreateHeap__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::CreateHeap() {
    /* Nonmatching */
}

/* 0000012C-000002B4       .text Create__Q210daObjHbrf15Act_cFv */
s32 daObjHbrf1::Act_c::Create() {
    /* Nonmatching */
}

/* 000002B4-000003B0       .text Mthd_Create__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::Mthd_Create() {
    /* Nonmatching */
}

/* 000003B0-000003B8       .text Delete__Q210daObjHbrf15Act_cFv */
BOOL daObjHbrf1::Act_c::Delete() {
    /* Nonmatching */
}

/* 000003B8-00000404       .text Mthd_Delete__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::Mthd_Delete() {
    /* Nonmatching */
}

/* 00000404-00000484       .text set_mtx__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00000484-000004C0       .text init_mtx__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::init_mtx() {
    /* Nonmatching */
}

/* 000004C0-0000066C       .text daObjHbrf1_down_stop__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_down_stop() {
    /* Nonmatching */
}

/* 0000066C-0000068C       .text daObjHbrf1_up_demo_wait__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_up_demo_wait() {
    /* Nonmatching */
}

/* 0000068C-000006B0       .text daObjHbrf1_up_demo_timer__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_up_demo_timer() {
    /* Nonmatching */
}

/* 000006B0-000007FC       .text daObjHbrf1_up_demo__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_up_demo() {
    /* Nonmatching */
}

/* 000007FC-000009B0       .text daObjHbrf1_up_stop__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_up_stop() {
    /* Nonmatching */
}

/* 000009B0-00000A08       .text daObjHbrf1_down_demo_wait__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_down_demo_wait() {
    /* Nonmatching */
}

/* 00000A08-00000A2C       .text daObjHbrf1_down_demo_timer__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_down_demo_timer() {
    /* Nonmatching */
}

/* 00000A2C-00000B70       .text daObjHbrf1_down_demo__Q210daObjHbrf15Act_cFv */
void daObjHbrf1::Act_c::daObjHbrf1_down_demo() {
    /* Nonmatching */
}

/* 00000B70-00000C1C       .text Execute__Q210daObjHbrf15Act_cFPPA3_A4_f */
void daObjHbrf1::Act_c::Execute(float(**)[3][4]) {
    /* Nonmatching */
}

/* 00000C1C-00000CBC       .text Draw__Q210daObjHbrf15Act_cFv */
BOOL daObjHbrf1::Act_c::Draw() {
    /* Nonmatching */
}

namespace daObjHbrf1 {
namespace {
/* 00000CBC-00000CDC       .text Mthd_Create__Q210daObjHbrf127@unnamed@d_a_obj_hbrf1_cpp@FPv */
void Mthd_Create(void*) {
    /* Nonmatching */
}

/* 00000CDC-00000CFC       .text Mthd_Delete__Q210daObjHbrf127@unnamed@d_a_obj_hbrf1_cpp@FPv */
void Mthd_Delete(void*) {
    /* Nonmatching */
}

/* 00000CFC-00000D1C       .text Mthd_Execute__Q210daObjHbrf127@unnamed@d_a_obj_hbrf1_cpp@FPv */
void Mthd_Execute(void*) {
    /* Nonmatching */
}

/* 00000D1C-00000D48       .text Mthd_Draw__Q210daObjHbrf127@unnamed@d_a_obj_hbrf1_cpp@FPv */
void Mthd_Draw(void*) {
    /* Nonmatching */
}

/* 00000D48-00000D74       .text Mthd_IsDelete__Q210daObjHbrf127@unnamed@d_a_obj_hbrf1_cpp@FPv */
void Mthd_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class Mthd_Hbrf1 = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjHbrf1

actor_process_profile_definition g_profile_Obj_Hbrf1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hbrf1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHbrf1::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x001C,
    /* Actor SubMtd */ &daObjHbrf1::Mthd_Hbrf1,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
