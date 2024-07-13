//
// Generated by dtk
// Translation Unit: f_pc_layer_tag.cpp
//

#include "f_pc/f_pc_layer_tag.h"
#include "f_pc/f_pc_layer.h"

/* 8003DF4C-8003E044       .text fpcLyTg_ToQueue__FP26layer_management_tag_classUiUsUs */
s32 fpcLyTg_ToQueue(layer_management_tag_class* i_lyTag, uint i_layerID, u16 i_listID,
                    u16 i_listPriority) {
    if (i_lyTag->mpLayer == NULL && i_layerID == fpcLy_NONE_e) {
        return 0;
    } else {
        if (i_layerID != fpcLy_NONE_e && i_layerID != fpcLy_CURRENT_e && i_lyTag->mpLayer->mLayerID != i_layerID) {
            i_lyTag->mpLayer = fpcLy_Layer(i_layerID);
        }

        if (i_layerID == fpcLy_NONE_e || i_layerID == fpcLy_CURRENT_e) {
            s32 idx = fpcLy_ToQueue(i_lyTag->mpLayer, i_listID, &i_lyTag->mCreateTag);
            if (idx != 0) {
                i_lyTag->mNodeListID = i_listID;
                i_lyTag->mNodeListIdx = idx - 1;
                return 1;
            }
        } else if (fpcLy_IntoQueue(i_lyTag->mpLayer, i_listID, &i_lyTag->mCreateTag, i_listPriority) != 0) {
            i_lyTag->mNodeListID = i_listID;
            i_lyTag->mNodeListIdx = i_listPriority;
            return 1;
        }
        return 0;
    }
}

/* 8003E044-8003E0A4       .text fpcLyTg_QueueTo__FP26layer_management_tag_class */
s32 fpcLyTg_QueueTo(layer_management_tag_class* i_lyTag) {
    if (fpcLy_QueueTo(i_lyTag->mpLayer, &i_lyTag->mCreateTag) == 1) {
        i_lyTag->mpLayer = NULL;
        i_lyTag->mNodeListID = 0xFFFF;
        i_lyTag->mNodeListIdx = 0xFFFF;
        return 1;
    } else {
        return 0;
    }
}

/* 8003E0A4-8003E128       .text fpcLyTg_Move__FP26layer_management_tag_classUiUsUs */
s32 fpcLyTg_Move(layer_management_tag_class* i_lyTag, uint i_layerID, u16 i_listID,
                 u16 i_listPriority) {
    layer_class* layer = fpcLy_Layer(i_layerID);
    if (layer == NULL) {
        return 0;
    } else if (fpcLyTg_QueueTo(i_lyTag) == 0x1) {
        i_lyTag->mpLayer = layer;
        return fpcLyTg_ToQueue(i_lyTag, i_layerID, i_listID, i_listPriority);
    } else {
        return 0;
    }
}

/* 8003E128-8003E1DC       .text fpcLyTg_Init__FP26layer_management_tag_classUiPv */
s32 fpcLyTg_Init(layer_management_tag_class* i_lyTag, uint i_layerID, void* i_data) {
    static layer_management_tag_class crear = {
        NULL, NULL, NULL, NULL, 0, NULL, 0xFFFF, 0xFFFF,
    };

    layer_class* layer;
    *i_lyTag = crear;
    cTg_Create(&i_lyTag->mCreateTag, i_data);
    layer = fpcLy_Layer(i_layerID);
    if (layer != NULL) {
        i_lyTag->mpLayer = layer;
        return 1;
    } else {
        return 0;
    }
}
