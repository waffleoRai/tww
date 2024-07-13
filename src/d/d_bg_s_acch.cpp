//
// Generated by dtk
// Translation Unit: d_bg_s_acch.cpp
//

#include "d/d_bg_s_acch.h"
#include "d/d_bg_s.h"
#include "dolphin/types.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_sea.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)
#define CHECK_PVEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v->x && v->x < 1.0e32f && -1.0e32f < v->y && v->y < 1.0e32f && -1.0e32f < v->z && v->z < 1.0e32f)

/* 800A257C-800A25F4       .text __ct__12dBgS_AcchCirFv */
dBgS_AcchCir::dBgS_AcchCir() {
    m_flags = 0;
    m_wall_rr = 0.0f;
    field_0x2c = 0.0f;
    m_wall_h = 0.0f;
    m_wall_r = 0.0f;
    m_wall_angle_y = 0;
    m_wall_h_direct = 0.0f;
}

/* 800A25F4-800A25FC       .text SetWallR__12dBgS_AcchCirFf */
void dBgS_AcchCir::SetWallR(f32 radius) {
    m_wall_r = radius;
}

/* 800A25FC-800A2624       .text SetWall__12dBgS_AcchCirFff */
void dBgS_AcchCir::SetWall(f32 height, f32 radius) {
    m_wall_h = height;
    SetWallR(radius);
}

static void dummy3() {
    // Fakematch to fix the order of vtables in this TU, cM3dGPla's should appear after dBgS_Acch's.
    cM3dGPla pla;
}

/* 800A2624-800A29B0       .text __dt__9dBgS_AcchFv */
dBgS_Acch::~dBgS_Acch() {
}

/* 800A29B0-800A2CFC       .text __ct__9dBgS_AcchFv */
dBgS_Acch::dBgS_Acch() {
    SetPolyPassChk(GetPolyPassChkInfo());
    SetGrpPassChk(GetGrpPassChkInfo());
    m_flags = 0;
    SetRoofNone();
    pm_pos = NULL;
    pm_old_pos = NULL;
    pm_speed = NULL;
    m_ground_h = -1000000000.0f;
    m_ground_up_h = 0.0f;
    m_ground_check_offset = 60.0f;
    m_ground_up_h_diff = 0.0f;
    field_0xb0 = 0;
    field_0xb4 = 0.0f;
    field_0xb8 = 0.0f;
    m_tbl_size = 0;
    pm_acch_cir = NULL;
    m_roof_y = 0.0f;
    m_roof_crr_height = 0.0f;
    m_roof_height = 0.0f;
    m_water_check_offset = 200.0f;
    pm_angle = NULL;
    pm_shape_angle = NULL;
    m_my_ac = NULL;
    pm_out_poly_info = NULL;
    m_sea_height = -1000000000.0f;
}

static void dummy1() {
    OSReport("***********************************\ndBgS_Acch::copy constructer called.\n***********************************\n");
}

/* 800A2CFC-800A2D78       .text Init__9dBgS_AcchFv */
void dBgS_Acch::Init() {
    ClrWallHit();
    for (int i = 0; i < m_tbl_size; i++) {
        pm_acch_cir[i].ClrWallHit();
        pm_acch_cir[i].ClrWallHDirect();
    }
}

/* 800A2D78-800A2E80       .text Set__9dBgS_AcchFP4cXyzP4cXyzP10fopAc_ac_ciP12dBgS_AcchCirP4cXyzP5csXyzP5csXyz */
void dBgS_Acch::Set(cXyz* pos, cXyz* old_pos, fopAc_ac_c* actor, int tbl_size, dBgS_AcchCir* acchCir, cXyz* speed,
                    csXyz* angle, csXyz* shape_angle) {
    pm_pos = pos;
    pm_old_pos = old_pos;
    JUT_ASSERT(221, pm_pos != NULL);
    JUT_ASSERT(222, pm_old_pos != NULL);

    m_my_ac = actor;
    SetActorPid(fopAcM_GetID(actor));
    pm_speed = speed;
    m_tbl_size = tbl_size;
    pm_acch_cir = acchCir;
    pm_angle = angle;
    pm_shape_angle = shape_angle;
}

/* 800A2E80-800A2EE8       .text GroundCheckInit__9dBgS_AcchFR4dBgS */
void dBgS_Acch::GroundCheckInit(dBgS&) {
    m_ground_h = -1000000000.0f;
    if (m_flags & GRND_NONE) {
        return;
    }
    m_gnd.SetExtChk(*(cBgS_Chk*)this);
    field_0xb0 = ChkGroundHit();
    ClrGroundHit();
    ClrGroundLanding();
    ClrGroundAway();
}

/* 800A2EE8-800A305C       .text GroundCheck__9dBgS_AcchFR4dBgS */
void dBgS_Acch::GroundCheck(dBgS& i_bgs) {
    if (m_flags & GRND_NONE)
        return;

    cXyz pos = *pm_pos;

    pos.y += m_ground_up_h_diff + (m_ground_check_offset - m_ground_up_h);
    m_ground_up_h_diff = 0.0f;
    m_gnd.m_pos = pos;

    m_ground_h = i_bgs.GroundCross(&m_gnd);
    if (m_ground_h != -1000000000.0f) {
        field_0xb8 = m_ground_h + m_ground_up_h;
        if (field_0xb8 > field_0xb4) {
            pm_pos->y = field_0xb8;
            if (pm_speed != NULL)
                pm_speed->y = 0.0f;

            cM3dGPla* pla = i_bgs.GetTriPla(m_gnd);
            m_pla = *pla;
            SetGroundFind();
            SetGroundHit();
            i_bgs.RideCallBack(m_gnd, m_my_ac);
            if (!field_0xb0)
                SetGroundLanding();
        }
    }

    if (field_0xb0 && !(m_flags & GROUND_HIT)) {
        m_flags |= GROUND_AWAY;
    }
}

/* 800A305C-800A313C       .text GroundRoofProc__9dBgS_AcchFR4dBgS */
f32 dBgS_Acch::GroundRoofProc(dBgS& i_bgs) {
    f32 y = -1000000000.0f;
    if (m_ground_h != -1000000000.0f) {
        // y = m_roof_height;
        // fakematch to fix load order
        if (field_0xb8 < (y = m_roof_height) && y < pm_pos->y) {
            pm_pos->y = y;
        }

        if (!(m_flags & ROOF_NONE)) {
            y = m_ground_h;
            if (y >= m_roof_y) {
                m_roof.SetExtChk(*this);
                ClrRoofHit();
                cXyz pos = *pm_pos;
                m_roof.SetPos(pos);
                y = i_bgs.RoofChk(&m_roof);
                m_roof_y = y;
            }
        }
    }
    return y;
}

/* 800A313C-800A3460       .text LineCheck__9dBgS_AcchFR4dBgS */
void dBgS_Acch::LineCheck(dBgS& i_bgs) {
    for (s32 i = 0; i < m_tbl_size; i++) {
        cBgS_LinChk linChk;
        cXyz old_pos = *pm_old_pos;
        cXyz pos = *pm_pos;

        old_pos.y += pm_acch_cir[i].GetWallH();
        pos.y += pm_acch_cir[i].GetWallH();

        linChk.Set2(&old_pos, &pos, GetActorPid());
        linChk.SetExtChk(*this);
        if (i_bgs.LineCross(&linChk)) {
            *pm_pos = linChk.GetLinP()->GetEnd();
            m_flags |= LINE_CHECK_HIT;

            if (pm_out_poly_info != NULL)
                pm_out_poly_info->SetPolyInfo(linChk);

            cM3dGPla* pla = i_bgs.GetTriPla(linChk);
            if (!(pla->GetNP()->y >= 0.5f)) {
                VECAdd(pm_pos, pla->GetNP(), pm_pos);
                if (!cM3d_IsZero(sqrtf(pla->GetNP()->x*pla->GetNP()->x + pla->GetNP()->z*pla->GetNP()->z)))
                    pm_acch_cir[i].SetWallHDirect(pm_pos->y);

                pm_pos->y -= pm_acch_cir[i].GetWallH();
            } else {
                pm_pos->y -= 1.0f;
                GroundCheck(i_bgs);
            }
        }
    }
}

/* 800A3460-800A3F50       .text CrrPos__9dBgS_AcchFR4dBgS */
void dBgS_Acch::CrrPos(dBgS& i_bgs) {
    if (m_flags & 0x1) {
        return;
    }

    JUT_ASSERT(494, pm_pos != NULL);
    JUT_ASSERT(495, pm_old_pos != NULL);

    CHECK_FLOAT_CLASS(535, pm_pos->x);
    CHECK_FLOAT_CLASS(536, pm_pos->y);
    CHECK_FLOAT_CLASS(537, pm_pos->z);
    CHECK_PVEC3_RANGE(541, pm_pos);

    i_bgs.MoveBgCrrPos(m_gnd, ChkGroundHit(), pm_pos, pm_angle, pm_shape_angle);

    GroundCheckInit(i_bgs);
    Init();

    f32 lowH_R = GetWallAllLowH_R();
    cXyz* temp9 = pm_old_pos;
    cXyz* temp10 = pm_pos;
    f32 distXZ2 = temp9->abs2XZ(*temp10);
    f32 distY = pm_old_pos->y - pm_pos->y;
    f32 lowH = GetWallAllLowH();
    field_0xb4 = pm_pos->y;
    f32 oldY = pm_old_pos->y;
    f32 temp7 = lowH + oldY;
    f32 temp8 = m_ground_check_offset + pm_pos->y;

    bool ranLineCheck = false;
    OffLineCheckHit();
    if (!ChkLineCheckNone() && !cM3d_IsZero(lowH_R)) {
        if (distXZ2 > lowH_R*lowH_R || temp7 > temp8 || distY > m_ground_check_offset || ChkLineCheck()) {
            ranLineCheck = true;
            LineCheck(i_bgs);
        }
    }
    if (!(m_flags & WALL_NONE)) {
        i_bgs.WallCorrect(this);
    }
    if (ChkWallHit() && ranLineCheck) {
        LineCheck(i_bgs);
    }

    m_roof_height = 1000000000.0f;
    if (!(m_flags & ROOF_NONE)) {
        m_roof.SetExtChk(*(cBgS_Chk*)this);
        ClrRoofHit();
        cXyz roofPos = *pm_pos;
        m_roof.SetPos(roofPos);
        m_roof_y = i_bgs.RoofChk(&m_roof);
        if (m_roof_y != 1000000000.0f && pm_pos->y + m_roof_crr_height > m_roof_y) {
            m_roof_height = m_roof_y - m_roof_crr_height;
            SetRoofHit();
        }
    }

    if (!(m_flags & GRND_NONE)) {
        ClrGroundFind();
        GroundCheck(i_bgs);
        GroundRoofProc(i_bgs);
    } else if (m_roof_height < pm_pos->y) {
        pm_pos->y = m_roof_height;
    }

    if (!(m_flags & WATER_NONE)) {
        ClrWaterHit();
        ClrWaterIn();
        m_wtr.SetHeight(-1000000000.0f);

        int room_no = i_bgs.GetRoomId(m_gnd);
        if (m_ground_h != -1000000000.0f && 0 <= room_no && room_no < 64) {
            JUT_ASSERT(693, 0 <= room_no && room_no < 64);

            dBgW* bgw = dComIfGp_roomControl_getBgW(room_no);
            if (bgw) {
                f32 top;
                f32 under;
                bgw->GetTopUnder(&top, &under);

                cXyz ground = *pm_pos;
                ground.y = under;
                m_wtr.Set(ground, top);
                m_wtr.SetPassChkInfo(*this);
                if (i_bgs.SplGrpChk(&m_wtr)) {
                    SetWaterHit();
                    if (m_wtr.GetHeight() > pm_pos->y) {
                        SetWaterIn();
                    }

                    JUT_ASSERT(718, m_wtr.GetHeight() >= ground.y);
                    JUT_ASSERT(719, m_wtr.GetHeight() <= top);
                }
            }
        }
    }

    if (ChkSeaCheckOn()) {
        m_flags &= ~SEA_IN;
        m_sea_height = -1000000000.0f;

        if (daSea_ChkArea(pm_pos->x, pm_pos->z)) {
            m_sea_height = daSea_calcWave(pm_pos->x, pm_pos->z);
        }

        if (ChkSeaWaterHeight()) {
            f32 wtr_height = m_wtr.GetHeight();
            if (m_sea_height < wtr_height) {
                m_sea_height = wtr_height;
            }
        }

        if (m_sea_height > pm_pos->y) {
            m_flags |= SEA_IN;
        }
    }

    CHECK_FLOAT_CLASS(780, pm_pos->x);
    CHECK_FLOAT_CLASS(781, pm_pos->y);
    CHECK_FLOAT_CLASS(782, pm_pos->z);
    CHECK_PVEC3_RANGE(786, pm_pos);
}

/* 800A3F50-800A3F8C       .text GetWallAllR__9dBgS_AcchFv */
f32 dBgS_Acch::GetWallAllR() {
    f32 max = 0.0f;
    for (s32 i = 0; i < m_tbl_size; i++) {
        f32 r = pm_acch_cir[i].GetWallR();
        if (max < r)
            max = r;
    }
    return max;
}

/* 800A3F8C-800A3FE4       .text SetWallCir__9dBgS_AcchFv */
void dBgS_Acch::SetWallCir() {
    for (int i = 0; i < m_tbl_size; i++) {
        pm_acch_cir[i].SetCir(*pm_pos);
    }
}

/* 800A3FE4-800A4114       .text CalcWallBmdCyl__9dBgS_AcchFv */
void dBgS_Acch::CalcWallBmdCyl() {
    if (m_tbl_size <= 0) {
        m_wall_cyl.SetC(*pm_pos);
        m_wall_cyl.SetR(0.0f);
        m_wall_cyl.SetH(0.0f);
        return;
    }

    f32 all_r = GetWallAllR();
    f32 min_h = pm_acch_cir[0].GetWallH();
    f32 max_h = min_h;
    if (m_tbl_size >= 1) {
        for (s32 i = 0; i < m_tbl_size; i++) {
            f32 h = pm_acch_cir[i].GetWallH();
            if (min_h > h)
                min_h = h;
            if (max_h < h)
                max_h = h;
        }
    }

    cXyz center = *pm_pos;
    center.y += min_h;
    m_wall_cyl.SetC(center);
    m_wall_cyl.SetR(all_r);
    m_wall_cyl.SetH(max_h - min_h);
}

/* 800A4114-800A4128       .text SetGroundUpY__9dBgS_AcchFf */
void dBgS_Acch::SetGroundUpY(f32 y) {
    m_ground_up_h_diff = y - m_ground_up_h;
    m_ground_up_h = y;
}

/* 800A4128-800A4178       .text GetWallAllLowH__9dBgS_AcchFv */
f32 dBgS_Acch::GetWallAllLowH() {
    if (m_tbl_size <= 0)
        return 0.0f;

    f32 min = pm_acch_cir[0].GetWallH();
    for (s32 i = 1; i < m_tbl_size; i++) {
        f32 h = pm_acch_cir[i].GetWallH();
        if (min > h)
            min = h;
    }
    return min;
}

/* 800A4178-800A41E4       .text GetWallAllLowH_R__9dBgS_AcchFv */
f32 dBgS_Acch::GetWallAllLowH_R() {
    if (m_tbl_size <= 0)
        return 0.0f;

    s32 bestWall = 0;
    f32 min = pm_acch_cir[0].GetWallH();
    for (s32 i = 1; i < m_tbl_size; i++) {
        f32 h = pm_acch_cir[i].GetWallH();
        if (min > h) {
            min = h;
            bestWall = i;
        }
    }
    return pm_acch_cir[bestWall].GetWallR();
}

/* 800A41E4-800A42B4       .text GetOnePolyInfo__9dBgS_AcchFP13cBgS_PolyInfo */
bool dBgS_Acch::GetOnePolyInfo(cBgS_PolyInfo* dst) {
    if (ChkGroundHit()) {
        dst->SetPolyInfo(m_gnd);
        return false;
    }

    if (ChkWallHit()) {
        for (s32 i = 0; i < m_tbl_size; i++) {
            if (pm_acch_cir[i].ChkWallHit())
                dst->SetPolyInfo(pm_acch_cir[i]);
        }

        return false;
    }

    if (ChkRoofHit()) {
        dst->SetPolyInfo(m_roof);
        return false;
    }

    return true;
}

/* 800A42B4-800A4348       .text GetWallAddY__9dBgS_AcchFR3Veci */
f32 dBgS_Acch::GetWallAddY(Vec& vec, int) {
    if (!ChkGroundFind() || m_pla.mNormal.y < 0.5f) {
        return 0.0f;
    }
    f32 cross_y;
    if (m_pla.getCrossYLessD(vec, &cross_y)) {
        if (cross_y > 0.0f)
            cross_y = 0.0f;
        return -cross_y;
    } else {
        return 0.0f;
    }
}

static void dummy2() {
    OSReport("\x1B[43;30m**************************************\ndBgS_ObjAcch::copy constructer called.\n**************************************\n\033[m");
    dBgS_ObjAcch acch; // fakematch to get dBgS_ObjAcch's vtable and destructor to show up in this TU
}
