//
// Generated by dtk
// Translation Unit: d_cc_s.cpp
//

#include "d/d_cc_s.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"

/* 800AD5B0-800AD5E4       .text Ct__4dCcSFv */
void dCcS::Ct() {
    cCcS::Ct();
    mMass_Mng.Ct();
}

/* 800AD5E4-800AD604       .text Dt__4dCcSFv */
void dCcS::Dt() {
    cCcS::Dt();
}

/* 800AD604-800AD748       .text ChkShieldFrontRange__4dCcSFP8cCcD_ObjP8cCcD_Obj */
bool dCcS::ChkShieldFrontRange(cCcD_Obj* obj1, cCcD_Obj* obj2) {
    dCcD_GObjInf* inf1 = (dCcD_GObjInf*)obj1->GetGObjInf();
    if (inf1 == NULL) { return false; }
    fopAc_ac_c* ac1 = inf1->GetAc();
    if (ac1 == NULL) { return false; }
    dCcD_GObjInf* inf2 = (dCcD_GObjInf*)obj2->GetGObjInf();
    if (inf2 == NULL) { return false; }
    fopAc_ac_c* ac2 = inf2->GetAc();
    if (ac2 == NULL) { return false; }
    
    cXyz delta;
    VECSubtract(&ac1->eyePos, &ac2->eyePos, &delta);
    f32 dist = VECMag(&delta);
    if (cM3d_IsZero(dist)) {
        return false;
    }
    VECNormalize(&delta, &delta);
    s16 deltaAngle = cM_atan2s(delta.x, delta.z);
    s16 shieldAngle = inf2->GetTgShieldFrontRangeYAngle() ? *inf2->GetTgShieldFrontRangeYAngle() : ac2->shape_angle.y;
    if (cLib_distanceAngleS(deltaAngle, shieldAngle) > 0x4000) {
        return false;
    }
    
    return true;
}

/* 800AD748-800AD7D0       .text ChkShield__4dCcSFP8cCcD_ObjP8cCcD_ObjP12dCcD_GObjInfP12dCcD_GObjInf */
bool dCcS::ChkShield(cCcD_Obj* obj1, cCcD_Obj* obj2, dCcD_GObjInf* inf1, dCcD_GObjInf* inf2) {
    if (inf1->ChkAtNoGuard()) {
        return false;
    }
    if (inf2->ChkTgShield()) {
        if (inf2->ChkTgShieldFrontRange()) {
            return ChkShieldFrontRange(obj1, obj2);
        } else {
            return true;
        }
    } else {
        return false;
    }
}

/* 800AD7D0-800AD86C       .text CalcTgPlusDmg__4dCcSFP8cCcD_ObjP8cCcD_ObjP9cCcD_SttsP9cCcD_Stts */
void dCcS::CalcTgPlusDmg(cCcD_Obj* obj1, cCcD_Obj* obj2, cCcD_Stts* stts1, cCcD_Stts* stts2) {
    dCcD_GObjInf* inf1 = (dCcD_GObjInf*)obj1->GetGObjInf();
    dCcD_GObjInf* inf2 = (dCcD_GObjInf*)obj2->GetGObjInf();
    if (!ChkShield(obj1, obj2, inf1, inf2)) {
        int atp = obj1->GetAtAtp();
        if (stts2->GetDmg() < atp) {
            stts2->PlusDmg(atp);
        }
    }
}

/* 800AD86C-800AD8EC       .text ChkAtTgHitAfterCross__4dCcSFbbPC12cCcD_GObjInfPC12cCcD_GObjInfP9cCcD_SttsP9cCcD_SttsP10cCcD_GSttsP10cCcD_GStts */
bool dCcS::ChkAtTgHitAfterCross(bool r4, bool r5, const cCcD_GObjInf* inf1_, const cCcD_GObjInf* inf2_,
                                cCcD_Stts* stts1_, cCcD_Stts* stts2_, cCcD_GStts* gstts1_, cCcD_GStts* gstts2_) {
    dCcD_GObjInf* inf1 = (dCcD_GObjInf*)inf1_;
    dCcD_GObjInf* inf2 = (dCcD_GObjInf*)inf2_;
    dCcD_Stts* stts1 = (dCcD_Stts*)stts1_;
    dCcD_Stts* stts2 = (dCcD_Stts*)stts2_;
    dCcD_GStts* gstts1 = (dCcD_GStts*)gstts1_;
    dCcD_GStts* gstts2 = (dCcD_GStts*)gstts2_;
    fpc_ProcID r11 = stts1->GetApid();
    fpc_ProcID r3 = stts2->GetApid();
    if (r4) {
        gstts1->SetAtApid(r3);
        if (inf1->ChkAtNoConHit() && gstts1->GetAtOldApid() == stts2->GetApid()) {
            return true;
        }
    }
    if (r5) {
        gstts2->SetTgApid(r11);
        if (inf2->ChkTgNoConHit() && !inf1->ChkAtStopNoConHit() && gstts2->GetTgOldApid() == stts1->GetApid()) {
            return true;
        }
    }
    return false;
}

/* 800AD8EC-800ADA30       .text SetCoGObjInf__4dCcSFbbP12cCcD_GObjInfP12cCcD_GObjInfP9cCcD_SttsP9cCcD_SttsP10cCcD_GSttsP10cCcD_GStts */
void dCcS::SetCoGObjInf(bool r4, bool r5, cCcD_GObjInf* inf1_, cCcD_GObjInf* inf2_, cCcD_Stts* stts1, cCcD_Stts* stts2,
                        cCcD_GStts* gstts1_, cCcD_GStts* gstts2_) {
    dCcD_GObjInf* inf1 = (dCcD_GObjInf*)inf1_;
    dCcD_GObjInf* inf2 = (dCcD_GObjInf*)inf2_;
    dCcD_GStts* gstts1 = (dCcD_GStts*)gstts1_;
    dCcD_GStts* gstts2 = (dCcD_GStts*)gstts2_;
    if (r4) {
        inf1->SetCoHitApid(stts2->GetApid());
        if (gstts2->ChkNoActor())
            inf1->OnCoHitNoActor();
    }
    if (r5) {
        inf2->SetCoHitApid(stts1->GetApid());
        if (gstts1->ChkNoActor())
            inf2->OnCoHitNoActor();
    }
    
    if (r4) {
        dCcD_HitCallback callback = inf1->GetCoHitCallback();
        if (callback != NULL) {
            fopAc_ac_c* ac1 = inf1->GetAc();
            fopAc_ac_c* ac2 = inf2->GetAc();
            callback(ac1, inf1, ac2, inf2);
        }
    }
    if (r5) {
        dCcD_HitCallback callback = inf2->GetCoHitCallback();
        if (callback != NULL) {
            fopAc_ac_c* ac2 = inf2->GetAc();
            fopAc_ac_c* ac1 = inf1->GetAc();
            callback(ac2, inf2, ac1, inf1);
        }
    }
}

static u8 rank_tbl[11][11] = {
    { 0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,  50, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
    { 0,   0,  50,  75,  90, 100, 100, 100, 100, 100, 100 },
    { 0,   0,  25,  50,  75,  90, 100, 100, 100, 100, 100 },
    { 0,   0,  10,  25,  50,  75,  90, 100, 100, 100, 100 },
    { 0,   0,   0,  10,  25,  50,  75,  90, 100, 100, 100 },
    { 0,   0,   0,   0,  10,  25,  50,  75,  90, 100, 100 },
    { 0,   0,   0,   0,   0,  10,  25,  50,  75, 100, 100 },
    { 0,   0,   0,   0,   0,   0,  10,  25,  50, 100, 100 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,  50, 100 },
    { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
};

/* 800ADA30-800ADAD4       .text GetRank__4dCcSFUc */
int dCcS::GetRank(u8 weight) {
    if (weight == 0xFF) {
        return 10;
    } else if (weight == 0xFE) {
        return 9;
    } else if (weight >= 0xD9) {
        return 8;
    } else if (weight >= 0xB5) {
        return 7;
    } else if (weight >= 0x91) {
        return 6;
    } else if (weight >= 0x6D) {
        return 5;
    } else if (weight >= 0x49) {
        return 4;
    } else if (weight >= 0x25) {
        return 3;
    } else if (weight >= 0x02) {
        return 2;
    } else if (weight == 0x01) {
        return 1;
    } else {
        return 0;
    }
}

/* 800ADAD4-800ADEF0       .text SetPosCorrect__4dCcSFP8cCcD_ObjP4cXyzP8cCcD_ObjP4cXyzf */
void dCcS::SetPosCorrect(cCcD_Obj* obj1, cXyz* ppos1, cCcD_Obj* obj2, cXyz* ppos2, f32 cross_len) {
    if (obj1->ChkCoNoCrr() || obj2->ChkCoNoCrr()) {
        return;
    }
    if (obj1->GetStts() == NULL || obj2->GetStts() == NULL) {
        return;
    }
    if (obj1->GetStts()->GetActor() != NULL && obj1->GetStts()->GetActor() == obj2->GetStts()->GetActor()) {
        return;
    }
    if (cM3d_IsZero(cross_len)) {
        return;
    }
    
    SetCoGCorrectProc(obj1, obj2);
    
    bool correctY = false;
    if (obj1->ChkCoSph3DCrr() && obj2->ChkCoSph3DCrr()) {
        correctY = true;
    }
    
    if ((obj1->GetStts()->GetWeightUc() == 0 && obj2->GetStts()->GetWeightUc() == 0) ||
        (obj1->GetStts()->GetWeightUc() == 0xFF && obj2->GetStts()->GetWeightUc() == 0xFF)
    ) {
        return;
    }
    int obj1WeightRank = GetRank(obj1->GetStts()->GetWeightUc());
    int obj2WeightRank = GetRank(obj2->GetStts()->GetWeightUc());
    u8 rank = rank_tbl[obj1WeightRank][obj2WeightRank];
    u8 invRank = 100 - rank;
    f32 obj2Weight = rank * 0.01f;
    f32 obj1Weight = invRank * 0.01f;
    
    f32 objDistLen;
    Vec vec1;
    Vec vec2;
    Vec objsDist;
    if (correctY) {
        objsDist.x = ppos2->x - ppos1->x;
        objsDist.y = ppos2->y - ppos1->y;
        objsDist.z = ppos2->z - ppos1->z;
        objDistLen = sqrtf(objsDist.x*objsDist.x + objsDist.y*objsDist.y + objsDist.z*objsDist.z);
    } else {
        objsDist.x = ppos2->x - ppos1->x;
        objsDist.y = 0.0f;
        objsDist.z = ppos2->z - ppos1->z;
        objDistLen = sqrtf(objsDist.x*objsDist.x + objsDist.z*objsDist.z);
    }
    if (!cM3d_IsZero(objDistLen)) {
        if (correctY) {
            f32 pushFactor = cross_len / objDistLen;
            objsDist.x *= pushFactor;
            objsDist.y *= pushFactor;
            objsDist.z *= pushFactor;
            vec1.x = -objsDist.x * obj2Weight;
            vec1.y = -objsDist.y * obj2Weight;
            vec1.z = -objsDist.z * obj2Weight;
            vec2.x = objsDist.x * obj1Weight;
            vec2.y = objsDist.y * obj1Weight;
            vec2.z = objsDist.z * obj1Weight;
        } else {
            f32 pushFactor = cross_len / objDistLen;
            objsDist.x *= pushFactor;
            objsDist.z *= pushFactor;
            vec1.x = -objsDist.x * obj2Weight;
            vec1.y = 0;
            vec1.z = -objsDist.z * obj2Weight;
            vec2.x = objsDist.x * obj1Weight;
            vec2.y = 0;
            vec2.z = objsDist.z * obj1Weight;
        }
    } else {
        vec1.y = 0;
        vec1.z = 0;
        vec2.y = 0;
        vec2.z = 0;
        if (!cM3d_IsZero(cross_len)) {
            vec1.x = -cross_len * obj2Weight;
            vec2.x = cross_len * obj1Weight;
        } else {
            vec1.x = -obj2Weight;
            vec2.x = obj1Weight;
        }
    }
    
    obj1->GetStts()->PlusCcMove(vec1.x, vec1.y, vec1.z);
    obj2->GetStts()->PlusCcMove(vec2.x, vec2.y, vec2.z);
    (*ppos1) += vec1;
    (*ppos2) += vec2;
}

/* 800ADEF0-800ADFF8       .text CalcParticleAngle__4dCcSFP12dCcD_GObjInfP9cCcD_SttsP9cCcD_SttsP5csXyz */
void dCcS::CalcParticleAngle(dCcD_GObjInf* i_atObjInf, cCcD_Stts* i_atStts, cCcD_Stts* i_tgStts, csXyz* o_angle) {
    cXyz vec(*i_atObjInf->GetAtVecP());

    if (cM3d_IsZero(VECMag(&vec))) {
        fopAc_ac_c* atActor = i_atStts->GetActor();
        fopAc_ac_c* tgActor = i_tgStts->GetActor();

        if (atActor == NULL || tgActor == NULL) {
            vec.z = 0.0f;
            vec.x = 0.0f;
            vec.y = -1.0f;
        } else {
            VECSubtract(&tgActor->current.pos, &atActor->current.pos, &vec);

            if (cM3d_IsZero(VECMag(&vec))) {
                vec.z = 0.0f;
                vec.x = 0.0f;
                vec.y = -1.0f;
            } else {
                VECNormalize(&vec, &vec);
            }
        }
    } else {
        VECNormalize(&vec, &vec);
    }

    cM3d_CalcVecZAngle(vec, o_angle);
}

/* 800ADFF8-800AE308       .text ProcAtTgHitmark__4dCcSFbbP8cCcD_ObjP8cCcD_ObjP12dCcD_GObjInfP12dCcD_GObjInfP9cCcD_SttsP9cCcD_SttsP10dCcD_GSttsP10dCcD_GSttsP4cXyz */
void dCcS::ProcAtTgHitmark(bool, bool, cCcD_Obj* r6, cCcD_Obj* r7, dCcD_GObjInf* atInf, dCcD_GObjInf* tgInf,
                           cCcD_Stts* r10, cCcD_Stts* r30, dCcD_GStts*, dCcD_GStts* r4, cXyz* pos)
{
    if (atInf->ChkAtNoHitMark()) { return; }
    if (tgInf->ChkTgNoHitMark()) { return; }
    if (tgInf->GetTgHitMark() == 0xFF) { return; }
    if (!r4->ChkNoneActorPerfTblId()) { return; }
    
    if (!ChkShield(r6, r7, atInf, tgInf)) {
        if (atInf->GetAtHitMark() == 0) { return; }
        if (atInf->GetAtHitMark() == 1 && tgInf->GetTgHitMark() == 1) {
            dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, pos);
        } else {
            csXyz angle;
            CalcParticleAngle(atInf, r10, r30, &angle);
            if (atInf->GetAtHitMark() == 0xF) {
                dComIfGp_particle_set(0x10, pos);
                cXyz scale;
                scale.x = scale.y = scale.z = 2.0f;
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, pos, &angle, &scale);
            } else if (atInf->GetAtHitMark() == 1) {
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, pos, &angle);
            } else {
                dComIfGp_particle_set(atInf->GetAtHitMark(), pos, &angle);
            }
            dKy_SordFlush_set(*pos, 1);
        }
    } else {
        if (tgInf->GetTgHitMark() == 0) { return; }
        dKy_SordFlush_set(*pos, 0);
        csXyz angle;
        CalcParticleAngle(atInf, r10, r30, &angle);
        dComIfGp_particle_set(tgInf->GetTgHitMark(), pos, &angle);
    }
}

/* 800AE308-800AE5AC       .text SetAtTgGObjInf__4dCcSFbbP8cCcD_ObjP8cCcD_ObjP12cCcD_GObjInfP12cCcD_GObjInfP9cCcD_SttsP9cCcD_SttsP10cCcD_GSttsP10cCcD_GSttsP4cXyz */
void dCcS::SetAtTgGObjInf(bool i_setAt, bool i_setTg, cCcD_Obj* param_2, cCcD_Obj* param_3,
                          cCcD_GObjInf* i_atObjInf, cCcD_GObjInf* i_tgObjInf, cCcD_Stts* param_6,
                          cCcD_Stts* param_7, cCcD_GStts* param_8, cCcD_GStts* param_9,
                          cXyz* i_hitPos) {
    dCcD_GObjInf* atObjInf = (dCcD_GObjInf*)i_atObjInf;
    dCcD_GObjInf* tgObjInf = (dCcD_GObjInf*)i_tgObjInf;
    dCcD_GStts* stts1 = (dCcD_GStts*)param_8;
    dCcD_GStts* stts2 = (dCcD_GStts*)param_9;

    bool chk_shield = ChkShield(param_2, param_3, atObjInf, tgObjInf);

    if (i_setAt) {
        atObjInf->SetAtHitPos(*i_hitPos);
        atObjInf->SetAtRVec(*tgObjInf->GetTgVecP());

        if (stts1 != NULL && stts1->GetTgSpl() == 0) {
            stts1->SetTgSpl(tgObjInf->GetTgSpl());
        }

        atObjInf->SetAtHitApid(param_7->GetApid());

        if (chk_shield) {
            atObjInf->OnAtShieldHit();
        }

        if (stts2->ChkNoActor()) {
            atObjInf->OnAtHitNoActor();
        }
    }

    if (i_setTg) {
        tgObjInf->SetTgHitPos(*i_hitPos);
        tgObjInf->SetTgRVec(*atObjInf->GetAtVecP());

        if (stts2 != NULL && stts1->GetAtSpl() == 0) {
            stts2->SetAtSpl(atObjInf->GetAtSpl());
        }

        tgObjInf->SetTgHitApid(param_6->GetApid());

        if (chk_shield) {
            tgObjInf->OnTgShieldHit();
        }

        if (stts1->ChkNoActor()) {
            tgObjInf->OnTgHitNoActor();
        }
    }

    if (i_setAt) {
        dCcD_HitCallback at_callback = atObjInf->GetAtHitCallback();

        if (at_callback != NULL) {
            fopAc_ac_c* atAc = atObjInf->GetAc();
            fopAc_ac_c* tgAc = tgObjInf->GetAc();
            at_callback(atAc, atObjInf, tgAc, tgObjInf);
        }
    }

    if (i_setTg) {
        dCcD_HitCallback tg_callback = tgObjInf->GetTgHitCallback();

        if (tg_callback != NULL) {
            fopAc_ac_c* tgAc = tgObjInf->GetAc();
            fopAc_ac_c* atAc = atObjInf->GetAc();
            tg_callback(tgAc, tgObjInf, atAc, atObjInf);
        }
    }

    if (i_setAt && i_setTg && (!atObjInf->ChkAtEffCounter() || !tgObjInf->ChkTgEffCounter())) {
        atObjInf->SetAtEffCounterTimer();
        tgObjInf->SetTgEffCounterTimer();

        ProcAtTgHitmark(i_setAt, i_setTg, param_2, param_3, atObjInf, tgObjInf, param_6, param_7,
                        stts1, stts2, i_hitPos);
    }
}

/* 800AE5AC-800AE814       .text ChkCamera__4dCcSFR4cXyzR4cXyzfP10fopAc_ac_cP10fopAc_ac_c */
bool dCcS::ChkCamera(cXyz& start, cXyz& end, f32 radius, fopAc_ac_c* r26, fopAc_ac_c* r27) {
    if (mObjCoCount <= 0)
        return false;
    
    cCcD_Obj** objCoEnd = mpObjCo + mObjCoCount;
    cCcD_CpsAttr cpsAttr;
    cpsAttr.Set(start, end, radius);
    cpsAttr.CalcAabBox();
    cCcD_DivideInfo divideInfo;
    mDivideArea.CalcDivideInfoOverArea(&divideInfo, cpsAttr.GetWorkAab());
    for (cCcD_Obj** pObjCo = mpObjCo; pObjCo < objCoEnd; pObjCo++) {
        if (!(*pObjCo)->ChkCoSet())
            continue;
        if ((*pObjCo)->GetAc() == r26 || (*pObjCo)->GetAc() == r27)
            continue;
        if ((*pObjCo)->GetDivideInfo().Chk(divideInfo)) {
            cCcD_ShapeAttr* shapeAttr = (*pObjCo)->GetShapeAttr();
            if (shapeAttr == NULL)
                continue;
            f32 cross_len;
            if (shapeAttr->CrossCo(cpsAttr, &cross_len))
                return true;
        }
    }
    
    return false;
}

/* 800AE814-800AE818       .text MoveAfterCheck__4dCcSFv */
void dCcS::MoveAfterCheck() {
}

/* 800AE818-800AE81C       .text DrawAfter__4dCcSFv */
void dCcS::DrawAfter() {
}

/* 800AE81C-800AE83C       .text Move__4dCcSFv */
void dCcS::Move() {
    cCcS::Move();
}

/* 800AE83C-800AE878       .text Draw__4dCcSFv */
void dCcS::Draw() {
    DrawAfter();
    DrawClear();
    mMass_Mng.Clear();
}

/* 800AE878-800AE89C       .text MassClear__4dCcSFv */
void dCcS::MassClear() {
    mMass_Mng.Clear();
}

/* 800AE89C-800AE930       .text ChkNoHitGCo__4dCcSFP8cCcD_ObjP8cCcD_Obj */
bool dCcS::ChkNoHitGCo(cCcD_Obj* obj1, cCcD_Obj* obj2) {
    dCcD_GObjInf* inf1 = (dCcD_GObjInf*)obj1->GetGObjInf();
    dCcD_GObjInf* inf2 = (dCcD_GObjInf*)obj2->GetGObjInf();
    if ((inf1->ChkCoAtLasso() && !inf2->ChkCoTgLasso()) || (inf2->ChkCoAtLasso() && !inf1->ChkCoTgLasso())) {
        return true;
    }
    return false;
}

/* 800AE930-800AE938       .text ChkNoHitGAtTg__4cCcSFPC12cCcD_GObjInfPC12cCcD_GObjInfP10cCcD_GSttsP10cCcD_GStts */
bool cCcS::ChkNoHitGAtTg(const cCcD_GObjInf*, const cCcD_GObjInf*, cCcD_GStts*, cCcD_GStts*) {
    return false;
}

