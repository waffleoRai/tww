//
// Generated by dtk
// Translation Unit: d_a_wind_tag.cpp
//

#include "d/actor/d_a_wind_tag.h"
#include "d/d_procname.h"

/* 00000078-000000F0       .text _delete__Q29daWindTag11daWindTag_cFv */
BOOL daWindTag::daWindTag_c::_delete() {
    /* Nonmatching */
}

/* 000000F0-00000110       .text CheckCreateHeap__9daWindTagFP10fopAc_ac_c */
BOOL daWindTag::CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000110-000003E4       .text CreateHeap__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::CreateHeap() {
    /* Nonmatching */
}

/* 000003E4-00000828       .text CreateInit__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::CreateInit() {
    /* Nonmatching */
}

/* 00000828-000008D4       .text set_wind_angle__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::set_wind_angle() {
    /* Nonmatching */
}

/* 000008D4-0000099C       .text _create__Q29daWindTag11daWindTag_cFv */
s32 daWindTag::daWindTag_c::_create() {
    /* Nonmatching */
}

/* 00000E60-00000F74       .text set_mtx__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::set_mtx() {
    /* Nonmatching */
}

/* 00000F74-00000F88       .text checkSizeSpecialBig__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::checkSizeSpecialBig() {
    /* Nonmatching */
}

/* 00000F88-00001044       .text set_wind_se_sub__Q29daWindTag11daWindTag_cFUlP4cXyz */
void daWindTag::daWindTag_c::set_wind_se_sub(unsigned long, cXyz*) {
    /* Nonmatching */
}

/* 00001044-000011CC       .text set_wind_se__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::set_wind_se() {
    /* Nonmatching */
}

/* 00001234-000015C8       .text _execute__Q29daWindTag11daWindTag_cFv */
BOOL daWindTag::daWindTag_c::_execute() {
    /* Nonmatching */
}

/* 000015C8-0000161C       .text path_move__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::path_move() {
    /* Nonmatching */
}

/* 0000161C-00001700       .text set_next_pnt__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::set_next_pnt() {
    /* Nonmatching */
}

/* 00001700-00001814       .text _draw__Q29daWindTag11daWindTag_cFv */
BOOL daWindTag::daWindTag_c::_draw() {
    /* Nonmatching */
}

/* 00001814-00001AA4       .text MoveEmitter__Q29daWindTag11daWindTag_cFv */
void daWindTag::daWindTag_c::MoveEmitter() {
    /* Nonmatching */
}

/* 00001B00-00001B20       .text daWindTag_Create__FPv */
static s32 daWindTag_Create(void*) {
    /* Nonmatching */
}

/* 00001B20-00001B44       .text daWindTag_Delete__FPv */
static BOOL daWindTag_Delete(void*) {
    /* Nonmatching */
}

/* 00001B44-00001B68       .text daWindTag_Draw__FPv */
static BOOL daWindTag_Draw(void*) {
    /* Nonmatching */
}

/* 00001B68-00001B8C       .text daWindTag_Execute__FPv */
static BOOL daWindTag_Execute(void*) {
    /* Nonmatching */
}

/* 00001B8C-00001B94       .text daWindTag_IsDelete__FPv */
static BOOL daWindTag_IsDelete(void*) {
    /* Nonmatching */
}

static actor_method_class daWindTagMethodTable = {
    (process_method_func)daWindTag_Create,
    (process_method_func)daWindTag_Delete,
    (process_method_func)daWindTag_Execute,
    (process_method_func)daWindTag_IsDelete,
    (process_method_func)daWindTag_Draw,
};

actor_process_profile_definition g_profile_WindTag = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_WindTag,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWindTag::daWindTag_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00A8,
    /* Actor SubMtd */ &daWindTagMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
