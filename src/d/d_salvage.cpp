//
// Generated by dtk
// Translation Unit: d_salvage.cpp
//

#include "d/d_salvage.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_salvage.h"

// maybe belongs in d_a_salvage.h?
namespace daSalvage_prm {
    inline u8 getKindCmapNo(fopAc_ac_c* pact) { return pact->home.angle.z & 0x03; }
    inline s32 getSwitchNo(fopAc_ac_c* pact) { return pact->home.angle.z & 0xFF; }
    inline u8 getRoomNo(fopAc_ac_c* pact) { return fopAcM_GetParam(pact) >> 12; }
    inline u8 getSvNo(fopAc_ac_c* pact) { return fopAcM_GetParam(pact) >> 20; }
    inline u8 getType(fopAc_ac_c* pact) { return fopAcM_GetParam(pact) & 0x0F; }
    inline u8 getItemNo(fopAc_ac_c* pact) { return fopAcM_GetParam(pact) >> 4; }
    inline u8 getKind(fopAc_ac_c* pact) { return fopAcM_GetParam(pact) >> 28; }
};

/* 800CC734-800CC76C       .text init__18dSalvage_control_cFv */
void dSalvage_control_c::init() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mInfo); i++) {
        mInfo[i].mRoomNo = -1;
        mInfo[i].mEmtr = NULL;
    }
    mSeaNum = 0;
    mRoomNum = 0;
}

/* 800CC76C-800CC7C4       .text init_end__18dSalvage_control_cFv */
void dSalvage_control_c::init_end() {
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mInfo); i++)
        init_one_sub(i);
    mSeaNum = 0;
    mRoomNum = 0;
}

/* 800CC7C4-800CCB70       .text entry__18dSalvage_control_cFP10fopAc_ac_cP14JPABaseEmitter */
void dSalvage_control_c::entry(fopAc_ac_c* pact, JPABaseEmitter* emtr) {
    JUT_ASSERT(0x8b, pact != NULL);
    s8 roomNo = fopAcM_GetRoomNo(pact);
    u32 kind = daSalvage_prm::getKind(pact);
    u32 itemNo = daSalvage_prm::getItemNo(pact);
    u32 type = daSalvage_prm::getType(pact);
    u32 saveNo = daSalvage_prm::getSvNo(pact);
    s8 roomNoPrm = daSalvage_prm::getRoomNo(pact);
    s32 switchNo = daSalvage_prm::getSwitchNo(pact);
    s8 cmapNo;
    s32 no;

    bool invalid = false;
    if (roomNo != 0) {
        cmapNo = roomNo;
        no = mRoomNum + MAX_SEA;
    } else {
        no = mSeaNum;
        cmapNo = roomNoPrm;
    }

    if (roomNo != 0) {
        if (mRoomNum > MAX_ROOM)
            invalid = true;
    } else {
        if (mSeaNum > MAX_SEA)
            invalid = true;
    }

    if (cmapNo <= 0 || cmapNo > 64)
        invalid = true;

    if (kind == 2 || kind == 3) {
        if (saveNo > 15)
            invalid = true;
    } else if (kind == 0) {
        if (saveNo < 1 || saveNo > 128)
            invalid = true;
    }
    if (kind == 2 && switchNo == 0xFF)
        invalid = true;

    if (invalid)
        return;

    mInfo[no].resetFlag();
    mInfo[no].clrFlag(1);
    switch (kind) {
    case 0:
        if (dComIfGs_isCompleteCollectMap(saveNo))
            return;
        if (daSalvage_prm::getKindCmapNo(pact) != dComIfGs_getRandomSalvagePoint())
            return;
        mInfo[no].setFlag(1);
        break;
    case 2:
        if (!fopAcM_isSwitch(pact, switchNo))
            mInfo[no].setFlag(1);
    case 3:
        if (saveNo != 31 && dComIfGs_isOceanSvBit(cmapNo, saveNo))
            return;
        break;
    case 4:
        if (saveNo != 31 && dComIfGs_isOceanSvBit(cmapNo, saveNo))
            return;
        if (!dKy_daynight_check())
            mInfo[no].setFlag(1);
        break;
    case 6:
        if (dKy_moon_type_chk() || dComIfGs_isEventBit(daSalvage_c::m_savelabel[saveNo & 0xFF]))
            mInfo[no].setFlag(1);
        break;
    }

    mInfo[no].mRoomNo = roomNo;
    mInfo[no].mPos = pact->current.pos;
    mInfo[no].mScale = pact->scale;
    mInfo[no].mSaveNo = saveNo;
    mInfo[no].mType = type;
    mInfo[no].mKind = kind;
    mInfo[no].mItemNo = itemNo;
    mInfo[no].mSwitchNo = switchNo;
    mInfo[no].mEmtr = emtr;

    switch (kind) {
    case 0:
        mInfo[no].mH = pact->scale.y * 1000.0f;
        mInfo[no].mR = pact->scale.x * 700.0f;
        break;
    case 5:
        mInfo[no].mH = pact->scale.y * 1000.0f;
        mInfo[no].mR = pact->scale.x * 500.0f;
        break;
    default:
        mInfo[no].mH = pact->scale.y * 500.0f;
        mInfo[no].mR = pact->scale.x * 400.0f;
        break;
    }

    if (roomNo != 0)
        mRoomNum++;
    else
        mSeaNum++;
}

/* 800CCB70-800CCBC4       .text init_room__18dSalvage_control_cFSc */
void dSalvage_control_c::init_room(s8 roomNo) {
    for (s32 i = MAX_SEA; i < (s32)ARRAY_SIZE(mInfo); i++)
        init_one_sub(i);
    mRoomNum = 0;
}

/* 800CCBC4-800CCC20       .text init_one__18dSalvage_control_cFi */
void dSalvage_control_c::init_one(int no) {
    init_one_sub(no);
    if (no < MAX_SEA)
        mSeaNum--;
    else
        mRoomNum--;
}

/* 800CCC20-800CCCA8       .text init_one_sub__18dSalvage_control_cFi */
void dSalvage_control_c::init_one_sub(int no) {
    JPABaseEmitter* emtr = mInfo[no].mEmtr;
    if (emtr != NULL)
        emtr->becomeInvalidEmitter();
    mInfo[no].mRoomNo = -1;
    mInfo[no].mPos = cXyz::Zero;
    mInfo[no].mScale = cXyz::Zero;
    mInfo[no].mSaveNo = 0;
    mInfo[no].mType = 0;
    mInfo[no].mItemNo = 0;
    mInfo[no].mSwitchNo = 0;
    mInfo[no].mEmtr = NULL;
    mInfo[no].resetFlag();
}

/* 800CCCA8-800CCDAC       .text calcDistanceXZ__18dSalvage_control_cFv */
void dSalvage_control_c::calcDistanceXZ() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mInfo); i++) {
        if (!checkRegist(i))
            continue;

        mInfo[i].mDistance = (player->current.pos - mInfo[i].mPos).absXZ();
    }
}

/* 800CCDAC-800CCDD0       .text getPos__18dSalvage_control_cFi */
cXyz dSalvage_control_c::getPos(int no) {
    return mInfo[no].mPos;
}

/* 800CCDD0-800CCDE4       .text getPosP__18dSalvage_control_cFi */
cXyz* dSalvage_control_c::getPosP(int no) {
    return &mInfo[no].mPos;
}

/* 800CCDE4-800CCE08       .text getScale__18dSalvage_control_cFi */
cXyz dSalvage_control_c::getScale(int no) {
    return mInfo[no].mScale;
}

/* 800CCE08-800CCE18       .text getR__18dSalvage_control_cFi */
f32 dSalvage_control_c::getR(int no) {
    return mInfo[no].mR;
}

/* 800CCE18-800CCE28       .text getH__18dSalvage_control_cFi */
f32 dSalvage_control_c::getH(int no) {
    return mInfo[no].mH;
}

/* 800CCE28-800CCE38       .text getRoomNo__18dSalvage_control_cFi */
u8 dSalvage_control_c::getRoomNo(int no) {
    return mInfo[no].mRoomNo;
}

/* 800CCE38-800CCE48       .text getItemNo__18dSalvage_control_cFi */
u8 dSalvage_control_c::getItemNo(int no) {
    return mInfo[no].mItemNo;
}

/* 800CCE48-800CCE58       .text getSwitchNo__18dSalvage_control_cFi */
s32 dSalvage_control_c::getSwitchNo(int no) {
    return mInfo[no].mSwitchNo;
}

/* 800CCE58-800CCE68       .text getSaveNo__18dSalvage_control_cFi */
u8 dSalvage_control_c::getSaveNo(int no) {
    return mInfo[no].mSaveNo;
}

/* 800CCE68-800CCE78       .text getType__18dSalvage_control_cFi */
u8 dSalvage_control_c::getType(int no) {
    return mInfo[no].mType;
}

/* 800CCE78-800CCE88       .text getKind__18dSalvage_control_cFi */
u8 dSalvage_control_c::getKind(int no) {
    return mInfo[no].mKind;
}

/* 800CCE88-800CCE98       .text getDistance__18dSalvage_control_cFi */
f32 dSalvage_control_c::getDistance(int no) {
    return mInfo[no].mDistance;
}

/* 800CCE98-800CCEAC       .text getAlphaPtr__18dSalvage_control_cFi */
u8* dSalvage_control_c::getAlphaPtr(int no) {
    return &mInfo[no].mNowAlpha;
}

/* 800CCEAC-800CCEBC       .text getDrawMode__18dSalvage_control_cFi */
u8 dSalvage_control_c::getDrawMode(int no) {
    return mInfo[no].mNowAlpha; // ???
}

/* 800CCEBC-800CCEDC       .text checkRegist__18dSalvage_control_cFi */
BOOL dSalvage_control_c::checkRegist(int no) {
    return mInfo[no].mRoomNo != -1 ? TRUE : FALSE;
}

/* 800CCEDC-800CCEF8       .text checkUsed__18dSalvage_control_cFi */
bool dSalvage_control_c::checkUsed(int no) {
    return !mInfo[no].checkFlag(1);
}

/* 800CCEF8-800CCF1C       .text setPos__18dSalvage_control_cFi4cXyz */
void dSalvage_control_c::setPos(int no, cXyz pos) {
    mInfo[no].mPos = pos;
}

/* 800CCF1C-800CCF34       .text setFlag__18dSalvage_control_cFiUc */
void dSalvage_control_c::setFlag(int no, u8 v) {
    mInfo[no].setFlag(v);
}

/* 800CCF34-800CCF4C       .text clrFlag__18dSalvage_control_cFiUc */
void dSalvage_control_c::clrFlag(int no, u8 v) {
    mInfo[no].clrFlag(v);
}

/* 800CCF4C-800CCF5C       .text setNowAlpha__18dSalvage_control_cFiUc */
void dSalvage_control_c::setNowAlpha(int no, u8 v) {
    mInfo[no].mNowAlpha = v;
}

/* 800CCF5C-800CCF6C       .text setDrawMode__18dSalvage_control_cFii */
void dSalvage_control_c::setDrawMode(int no, int v) {
    mInfo[no].mDrawMode = v;
}
