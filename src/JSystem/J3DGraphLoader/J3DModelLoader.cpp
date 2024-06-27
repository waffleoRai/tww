//
// Generated by dtk
// Translation Unit: J3DModelLoader.cpp
//

#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include "JSystem/J3DGraphLoader/J3DMaterialFactory.h"
#include "JSystem/J3DGraphLoader/J3DMaterialFactory_v21.h"
#include "JSystem/J3DGraphLoader/J3DShapeFactory.h"
#include "JSystem/J3DGraphLoader/J3DJointFactory.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/os/OS.h"

/* 802FB758-802FB8A4       .text load__22J3DModelLoaderDataBaseFPCvUl */
J3DModelData* J3DModelLoaderDataBase::load(const void* i_data, u32 i_flags) {
    if (i_data == NULL) {
        return NULL;
    }
    const JUTDataFileHeader* fileHeader = (const JUTDataFileHeader*)i_data;
    if (fileHeader->mMagic == 'J3D1' && fileHeader->mType == 'bmd1') {
        return NULL;
    }
    if (fileHeader->mMagic == 'J3D2' && fileHeader->mType == 'bmd2') {
        J3DModelLoader_v21 loader;
        return loader.load(i_data, i_flags);
    }
    if (fileHeader->mMagic == 'J3D2' && fileHeader->mType == 'bmd3') {
        J3DModelLoader_v26 loader;
        return loader.load(i_data, i_flags);
    }
    return NULL;
}

/* 802FB8A4-802FB94C       .text loadMaterialTable__22J3DModelLoaderDataBaseFPCv */
J3DMaterialTable* J3DModelLoaderDataBase::loadMaterialTable(const void* i_data) {
    if (!i_data) {
        return NULL;
    }
    const JUTDataFileHeader* fileHeader = (const JUTDataFileHeader*)i_data;
    if (fileHeader->mMagic == 'J3D2' && fileHeader->mType == 'bmt3') {
        J3DModelLoader_v26 loader;
        return loader.loadMaterialTable(i_data);
    }
    return NULL;
}

/* 802FB94C-802FBA04       .text loadBinaryDisplayList__22J3DModelLoaderDataBaseFPCvUl */
J3DModelData* J3DModelLoaderDataBase::loadBinaryDisplayList(const void* i_data, u32 i_flags) {
    if (!i_data) {
        return NULL;
    }
    const JUTDataFileHeader* fileHeader = (const JUTDataFileHeader*)i_data;
    if (fileHeader->mMagic == 'J3D2' && (fileHeader->mType == 'bdl3' || fileHeader->mType == 'bdl4')) {
        J3DModelLoader_v26 loader;
        return loader.loadBinaryDisplayList(i_data, i_flags);
    }
    return NULL;
}

/* 802FBA04-802FBCC4       .text load__14J3DModelLoaderFPCvUl */
J3DModelData* J3DModelLoader::load(const void* i_data, u32 i_flags) {
    JKRGetCurrentHeap()->getTotalFreeSize();
    mpModelData = new J3DModelData();
    mpModelData->clear();
    mpModelData->mpRawData = i_data;
    mpModelData->setModelDataType(0);
    mpMaterialTable = &mpModelData->mMaterialTable;
    const JUTDataFileHeader* data = (JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &data->mFirstBlock;
    for (u32 block_no = 0; block_no < data->mBlockNum; block_no++) {
        switch (block->mType) {
            case 'INF1':
                readInformation((J3DModelInfoBlock*)block, (u32)i_flags); // cast fixes regalloc
                break;
            case 'VTX1':
                readVertex((J3DVertexBlock*)block);
                break;
            case 'EVP1':
                readEnvelop((J3DEnvelopBlock*)block);
                break;
            case 'DRW1':
                readDraw((J3DDrawBlock*)block);
                break;
            case 'JNT1':
                readJoint((J3DJointBlock*)block);
                break;
            case 'MAT3':
                readMaterial((J3DMaterialBlock*)block, i_flags);
                break;
            case 'MAT2':
                readMaterial_v21((J3DMaterialBlock_v21*)block, i_flags);
                break;
            case 'SHP1':
                readShape((J3DShapeBlock*)block, i_flags);
                break;
            case 'TEX1':
                readTexture((J3DTextureBlock*)block);
                break;
            default:
                OSReport("Unknown data block\n");
                break;
        }
        block = block->getNext();
    }
    const J3DModelHierarchy* hierarchy = mpModelData->getHierarchy();
    mpModelData->makeHierarchy(NULL, &hierarchy);
    mpModelData->sortVcdVatCmd();
    setupBBoardInfo();
    if (mpModelData->getFlag() & 0x100) {
        for (u16 shape_no = 0; shape_no < mpModelData->getShapeNum(); shape_no++) {
            mpModelData->getShapeNodePointer(shape_no)->onFlag(0x200);
        }
    }
    return mpModelData;
}

/* 802FBCC4-802FBE24       .text loadMaterialTable__14J3DModelLoaderFPCv */
J3DMaterialTable* J3DModelLoader::loadMaterialTable(const void* i_data) {
    mpMaterialTable = new J3DMaterialTable();
    mpMaterialTable->clear();
    const JUTDataFileHeader* data = (JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &data->mFirstBlock;
    for (u32 block_no = 0; block_no < data->mBlockNum; block_no++) {
        switch (block->mType) {
            case 'MAT3':
                readMaterialTable((J3DMaterialBlock*)block, 0x51100000);
                break;
            case 'MAT2':
                readMaterialTable_v21((J3DMaterialBlock_v21*)block, 0x51100000);
                break;
            case 'TEX1':
                readTextureTable((J3DTextureBlock*)block);
                break;
            default:
                OSReport("Unknown data block\n");
                break;
        }
        block = block->getNext();
    }
    if (mpMaterialTable->getTexture() == NULL) {
        mpMaterialTable->setTexture(new J3DTexture(0, NULL));
    }
    return mpMaterialTable;
}

/* 802FBE24-802FC0CC       .text loadBinaryDisplayList__14J3DModelLoaderFPCvUl */
J3DModelData* J3DModelLoader::loadBinaryDisplayList(const void* i_data, u32 i_flags) {
    mpModelData = new J3DModelData();
    mpModelData->clear();
    mpModelData->mpRawData = i_data;
    mpModelData->setModelDataType(1);
    mpMaterialTable = &mpModelData->mMaterialTable;
    const JUTDataFileHeader* data = (JUTDataFileHeader*)i_data;
    const JUTDataBlockHeader* block = &data->mFirstBlock;
    for (u32 block_no = 0; block_no < data->mBlockNum; block_no++) {
        switch (block->mType) {
            case 'INF1':
                readInformation((J3DModelInfoBlock*)block, (u32)i_flags); // cast fixes regalloc
                break;
            case 'VTX1':
                readVertex((J3DVertexBlock*)block);
                break;
            case 'EVP1':
                readEnvelop((J3DEnvelopBlock*)block);
                break;
            case 'DRW1':
                readDraw((J3DDrawBlock*)block);
                break;
            case 'JNT1':
                readJoint((J3DJointBlock*)block);
                break;
            case 'SHP1':
                readShape((J3DShapeBlock*)block, i_flags);
                break;
            case 'TEX1':
                readTexture((J3DTextureBlock*)block);
                break;
            case 'MDL3':
                readMaterialDL((J3DMaterialDLBlock*)block, i_flags);
                modifyMaterial(i_flags);
                break;
            case 'MAT3':
                u32 matFlags = 0x50100000;
                matFlags |= i_flags & 0x03000000;
                mpMaterialBlock = (J3DMaterialBlock*)block;
                u32 matType = getBdlFlag_MaterialType(i_flags);
                if (matType == 0) {
                    readMaterial((J3DMaterialBlock*)block, matFlags);
                } else if (matType == 0x2000) {
                    readPatchedMaterial((J3DMaterialBlock*)block, matFlags);
                }
                break;
            default:
                OSReport("Unknown data block\n");
                break;
        }
        block = block->getNext();
    }
    J3DModelHierarchy const* hierarchy = mpModelData->getHierarchy();
    mpModelData->makeHierarchy(NULL, &hierarchy);
    mpModelData->sortVcdVatCmd();
    setupBBoardInfo();
    mpModelData->indexToPtr();
    return mpModelData;
}

/* 802FC0CC-802FC234       .text setupBBoardInfo__14J3DModelLoaderFv */
void J3DModelLoader::setupBBoardInfo() {
    for (u16 i = 0; i < mpModelData->getJointNum(); i++) {
        J3DMaterial* mesh = mpModelData->getJointNodePointer(i)->getMesh();
        if (mesh != NULL) {
            u16 shape_index = mesh->getShape()->getIndex();
            u16* index_table = JSUConvertOffsetToPtr<u16>(mpShapeBlock, (u32)mpShapeBlock->mpIndexTable);
            J3DShapeInitData* shape_init_data =
                JSUConvertOffsetToPtr<J3DShapeInitData>(mpShapeBlock, (u32)mpShapeBlock->mpShapeInitData);
            J3DJoint* joint;
            switch (shape_init_data[index_table[shape_index]].mShapeMtxType) {
                case 0:
                    joint = mpModelData->getJointNodePointer(i);
                    joint->setMtxType(0);
                    break;
                case 1:
                    joint = mpModelData->getJointNodePointer(i);
                    joint->setMtxType(1);
                    mpModelData->mbHasBillboard = true;
                    break;
                case 2:
                    joint = mpModelData->getJointNodePointer(i);
                    joint->setMtxType(2);
                    mpModelData->mbHasBillboard = true;
                    break;
                case 3:
                    joint = mpModelData->getJointNodePointer(i);
                    joint->setMtxType(0);
                    break;
                default:
                    OSReport("WRONG SHAPE MATRIX TYPE (__FILE__)\n");
                    break;
            }
        }
    }
}

/* 802FC234-802FC3E4       .text readInformation__14J3DModelLoaderFPC17J3DModelInfoBlockUl */
void J3DModelLoader::readInformation(const J3DModelInfoBlock* i_block, u32 i_flags) {
    mpModelData->mFlags = i_flags | i_block->mFlags;
    mpModelData->getJointTree().setFlag(mpModelData->mFlags);
    J3DMtxCalc* mtx_calc = NULL;
    switch (mpModelData->mFlags & 0xF) {
        case 0: // TODO: enum for mtxcalc type (and other load flags)
            mtx_calc = new J3DMtxCalcBasic();
            break;
        case 1:
            mtx_calc = new J3DMtxCalcSoftimage();
            break;
        case 2:
            mtx_calc = new J3DMtxCalcMaya();
            break;
    }
    mpModelData->setBasicMtxCalc(mtx_calc);
    mpModelData->mVertexData.mPacketNum = i_block->mPacketNum;
    mpModelData->getVertexData().mVtxNum = i_block->mVtxNum;
    mpModelData->setHierarchy(JSUConvertOffsetToPtr<J3DModelHierarchy>(i_block, i_block->mpHierarchy));
}

/* 802FC3E4-802FC410       .text getFmtType__FP17_GXVtxAttrFmtList7_GXAttr */
static GXCompType getFmtType(GXVtxAttrFmtList* i_fmtList, GXAttr i_attr) {
    for (; i_fmtList->mAttrib != GX_VA_NULL; i_fmtList++) {
        if (i_fmtList->mAttrib == i_attr) {
            return i_fmtList->mCompType;
        }
    }
    return GX_F32;
}

/* 802FC410-802FC630       .text readVertex__14J3DModelLoaderFPC14J3DVertexBlock */
void J3DModelLoader::readVertex(const J3DVertexBlock* i_block) {
    J3DVertexData& vertex_data = mpModelData->getVertexData();
    vertex_data.mVtxAttrFmtList =
        JSUConvertOffsetToPtr<GXVtxAttrFmtList>(i_block, i_block->mpVtxAttrFmtList);
    vertex_data.mVtxPosArray = JSUConvertOffsetToPtr<void>(i_block, i_block->mpVtxPosArray);
    vertex_data.mVtxNrmArray = JSUConvertOffsetToPtr<void>(i_block, i_block->mpVtxNrmArray);
    vertex_data.mVtxNBTArray = JSUConvertOffsetToPtr<void>(i_block, i_block->mpVtxNBTArray);
    for (int i = 0; i < 2; i++) {
        vertex_data.mVtxColorArray[i] =
            (GXColor*)JSUConvertOffsetToPtr<void>(i_block, i_block->mpVtxColorArray[i]);
    }
    for (int i = 0; i < 8; i++) {
        vertex_data.mVtxTexCoordArray[i] =
            JSUConvertOffsetToPtr<void>(i_block, i_block->mpVtxTexCoordArray[i]);
    }

    _GXCompType nrm_type = getFmtType(vertex_data.mVtxAttrFmtList, GX_VA_NRM);
    u32 nrm_size = nrm_type == GX_F32 ? 12 : 6;

    void* nrm_end = NULL;
    if (vertex_data.mVtxNBTArray != NULL) {
        nrm_end = vertex_data.mVtxNBTArray;
    } else if (vertex_data.mVtxColorArray[0] != NULL) {
        nrm_end = vertex_data.mVtxColorArray[0];
    } else if (vertex_data.mVtxTexCoordArray[0] != NULL) {
        nrm_end = vertex_data.mVtxTexCoordArray[0];
    }

    if (vertex_data.mVtxNrmArray == NULL) {
        vertex_data.mNrmNum = 0;
    } else if (nrm_end != NULL) {
        vertex_data.mNrmNum = ((u32)nrm_end - (u32)vertex_data.mVtxNrmArray) / nrm_size + 1;
    } else {
        vertex_data.mNrmNum = (i_block->mSize - (u32)i_block->mpVtxNrmArray) / nrm_size + 1;
    }

    void* color0_end = NULL;
    if (vertex_data.mVtxColorArray[1] != NULL) {
        color0_end = vertex_data.mVtxColorArray[1];
    } else if (vertex_data.mVtxTexCoordArray[0] != NULL) {
        color0_end = vertex_data.mVtxTexCoordArray[0];
    }

    if (vertex_data.mVtxColorArray[0] == NULL) {
        vertex_data.mColNum = 0;
    } else if (color0_end != NULL) {
        vertex_data.mColNum = ((u32)color0_end - (u32)vertex_data.mVtxColorArray[0]) / 4 + 1;
    } else {
        vertex_data.mColNum = (i_block->mSize - (u32)i_block->mpVtxColorArray[0]) / 4 + 1;
    }

    if (vertex_data.mVtxTexCoordArray[0] == NULL) {
        vertex_data.mTexCoordNum = 0;
    } else {
        vertex_data.mTexCoordNum = (i_block->mSize - (u32)i_block->mpVtxTexCoordArray[0]) / 8 + 1;
    }
}

/* 802FC630-802FC6C0       .text readEnvelop__14J3DModelLoaderFPC15J3DEnvelopBlock */
void J3DModelLoader::readEnvelop(const J3DEnvelopBlock* i_block) {
    mpModelData->getJointTree().mWEvlpMtxNum = i_block->mWEvlpMtxNum;
    mpModelData->getJointTree().mWEvlpMixMtxNum =
        JSUConvertOffsetToPtr<u8>(i_block, i_block->mpWEvlpMixMtxNum);
    mpModelData->getJointTree().mWEvlpMixMtxIndex =
        JSUConvertOffsetToPtr<u16>(i_block, i_block->mpWEvlpMixMtxIndex);
    mpModelData->getJointTree().mWEvlpMixWeight =
        JSUConvertOffsetToPtr<f32>(i_block, i_block->mpWEvlpMixWeight);
    mpModelData->getJointTree().mInvJointMtx =
        JSUConvertOffsetToPtr<Mtx>(i_block, i_block->mpInvJointMtx);
}

/* 802FC6C0-802FC750       .text readDraw__14J3DModelLoaderFPC12J3DDrawBlock */
void J3DModelLoader::readDraw(const J3DDrawBlock* i_block) {
    J3DJointTree& joint_tree = mpModelData->getJointTree();
    joint_tree.mDrawMtxData.mEntryNum = i_block->mMtxNum;
    joint_tree.mDrawMtxData.mDrawMtxFlag = JSUConvertOffsetToPtr<u8>(i_block, i_block->mpDrawMtxFlag);
    joint_tree.mDrawMtxData.mDrawMtxIndex = JSUConvertOffsetToPtr<u16>(i_block, i_block->mpDrawMtxIndex);
    u16 i;
    for (i = 0; i < joint_tree.mDrawMtxData.mEntryNum; i++) {
        if (joint_tree.mDrawMtxData.mDrawMtxFlag[i] == 1) {
            break;
        }
    }
    joint_tree.mDrawMtxData.mDrawFullWgtMtxNum = i;
}

/* 802FC750-802FC834       .text readJoint__14J3DModelLoaderFPC13J3DJointBlock */
void J3DModelLoader::readJoint(const J3DJointBlock* i_block) {
    J3DJointFactory factory(*i_block);
    mpModelData->getJointTree().mJointNum = i_block->mJointNum;
    if (i_block->mpNameTable != NULL) {
        mpModelData->getJointTree().mJointName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpModelData->getJointTree().mJointName = NULL;
    }
    mpModelData->getJointTree().mJointNodePointer =
        new J3DJoint*[mpModelData->getJointTree().mJointNum];
    for (u16 i = 0; i < mpModelData->getJointTree().getJointNum(); i++) {
        mpModelData->getJointTree().mJointNodePointer[i] = factory.create(i);
    }
}

/* 802FC834-802FCAB0       .text readMaterial__18J3DModelLoader_v26FPC16J3DMaterialBlockUl */
void J3DModelLoader_v26::readMaterial(const J3DMaterialBlock* i_block, u32 i_flags) {
    J3DMaterialFactory factory(*i_block);
    mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
    mpMaterialTable->mUniqueMatNum = factory.countUniqueMaterials();
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mMaterialName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mMaterialName = NULL;
    }
    mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
    if (i_flags & 0x200000) {
        mpMaterialTable->mMaterialBase = new (0x20) J3DMaterial[mpMaterialTable->mUniqueMatNum];
    } else {
        mpMaterialTable->mMaterialBase = NULL;
    }
    if (i_flags & 0x200000) {
        for (u16 i = 0; i < mpMaterialTable->mUniqueMatNum; i++) {
            factory.create(&mpMaterialTable->mMaterialBase[i],
                           J3DMaterialFactory::MATERIAL_TYPE_NORMAL, i, i_flags);
            mpMaterialTable->mMaterialBase[i].mDiffFlag = (u32)&mpMaterialTable->mMaterialBase[i] >> 4;
        }
    }
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i] =
            factory.create(NULL, J3DMaterialFactory::MATERIAL_TYPE_NORMAL, i, i_flags);
    }
    if (i_flags & 0x200000) {
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
                (u32)&mpMaterialTable->mMaterialBase[factory.getMaterialID(i)] >> 4;
            mpMaterialTable->mMaterialNodePointer[i]->mpOrigMaterial =
                &mpMaterialTable->mMaterialBase[factory.getMaterialID(i)];
        }
    } else {
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
                ((u32)mpMaterialTable->mMaterialNodePointer >> 4) + factory.getMaterialID(i);
        }
    }
}

/* 802FCAB0-802FCD14       .text readMaterial_v21__18J3DModelLoader_v21FPC20J3DMaterialBlock_v21Ul */
void J3DModelLoader_v21::readMaterial_v21(const J3DMaterialBlock_v21* i_block, u32 i_flags) {
    J3DMaterialFactory_v21 factory(*i_block);
    mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
    mpMaterialTable->mUniqueMatNum = factory.countUniqueMaterials();
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mMaterialName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mMaterialName = NULL;
    }
    mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
    if (i_flags & 0x200000) {
        mpMaterialTable->mMaterialBase = new (0x20) J3DMaterial[mpMaterialTable->mUniqueMatNum];
    } else {
        mpMaterialTable->mMaterialBase = NULL;
    }
    if (i_flags & 0x200000) {
        for (u16 i = 0; i < mpMaterialTable->mUniqueMatNum; i++) {
            factory.create(&mpMaterialTable->mMaterialBase[i], i, i_flags);
            mpMaterialTable->mMaterialBase[i].mDiffFlag = (u32)&mpMaterialTable->mMaterialBase[i] >> 4;
        }
    }
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i] = factory.create(NULL, i, i_flags);
    }
    if (i_flags & 0x200000) {
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
                (u32)&mpMaterialTable->mMaterialBase[factory.getMaterialID(i)] >> 4;
            mpMaterialTable->mMaterialNodePointer[i]->mpOrigMaterial =
                &mpMaterialTable->mMaterialBase[factory.getMaterialID(i)];
        }
    } else {
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag = 0xC0000000;
        }
    }
}

/* 802FCD14-802FCE50       .text readShape__14J3DModelLoaderFPC13J3DShapeBlockUl */
void J3DModelLoader::readShape(const J3DShapeBlock* i_block, u32 i_flags) {
    mpShapeBlock = i_block;
    J3DShapeFactory factory(*i_block);
    mpModelData->mShapeTable.mShapeNum = i_block->mShapeNum;
    if (i_block->mpNameTable != NULL) {
        mpModelData->mName = new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpModelData->mName = NULL;
    }
    mpModelData->mShapeTable.mShapeNodePointer = new J3DShape*[mpModelData->mShapeTable.mShapeNum];
    factory.allocVcdVatCmdBuffer(mpModelData->mShapeTable.mShapeNum);
    J3DModelHierarchy const* hierarchy_entry = mpModelData->getHierarchy();
    GXVtxDescList* vtx_desc_list = NULL;
    for (; hierarchy_entry->mType != 0; hierarchy_entry++) {
        if (hierarchy_entry->mType == 0x12) {
            mpModelData->mShapeTable.mShapeNodePointer[hierarchy_entry->mValue] =
                factory.create(hierarchy_entry->mValue, i_flags, vtx_desc_list);
            vtx_desc_list = factory.getVtxDescList(hierarchy_entry->mValue);
        }
    }
}

/* 802FCE50-802FCF14       .text readTexture__14J3DModelLoaderFPC15J3DTextureBlock */
void J3DModelLoader::readTexture(const J3DTextureBlock* i_block) {
    u16 texture_num = i_block->mTextureNum;
    ResTIMG* texture_res = JSUConvertOffsetToPtr<ResTIMG>(i_block, i_block->mpTextureRes);
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mTextureName = new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mTextureName = NULL;
    }
    mpMaterialTable->mTexture = new J3DTexture(texture_num, texture_res);
}

/* 802FCF14-802FD050       .text readMaterialTable__18J3DModelLoader_v26FPC16J3DMaterialBlockUl */
void J3DModelLoader_v26::readMaterialTable(const J3DMaterialBlock* i_block, u32 i_flags) {
    J3DMaterialFactory factory(*i_block);
    mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mMaterialName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mMaterialName = NULL;
    }
    mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i] =
            factory.create(NULL, J3DMaterialFactory::MATERIAL_TYPE_NORMAL, i, i_flags);
    }
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
            (u32)mpMaterialTable->mMaterialNodePointer + factory.getMaterialID(i);
    }
}

/* 802FD050-802FD18C       .text readMaterialTable_v21__18J3DModelLoader_v21FPC20J3DMaterialBlock_v21Ul */
void J3DModelLoader_v21::readMaterialTable_v21(const J3DMaterialBlock_v21* i_block, u32 i_flags) {
    J3DMaterialFactory_v21 factory(*i_block);
    mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mMaterialName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mMaterialName = NULL;
    }
    mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i] =
            factory.create(NULL, i, i_flags);
    }
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
            ((u32)mpMaterialTable->mMaterialNodePointer >> 4) + factory.getMaterialID(i);
    }
}

/* 802FD18C-802FD250       .text readTextureTable__14J3DModelLoaderFPC15J3DTextureBlock */
void J3DModelLoader::readTextureTable(const J3DTextureBlock* i_block) {
    u16 texture_num = i_block->mTextureNum;
    ResTIMG* texture_res = JSUConvertOffsetToPtr<ResTIMG>(i_block, i_block->mpTextureRes);
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mTextureName = new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mTextureName = NULL;
    }
    mpMaterialTable->mTexture = new J3DTexture(texture_num, texture_res);
}

/* 802FD250-802FD390       .text readPatchedMaterial__14J3DModelLoaderFPC16J3DMaterialBlockUl */
void J3DModelLoader::readPatchedMaterial(const J3DMaterialBlock* i_block, u32 i_flags) {
    J3DMaterialFactory factory(*i_block);
    mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
    mpMaterialTable->mUniqueMatNum = factory.countUniqueMaterials();
    if (i_block->mpNameTable != NULL) {
        mpMaterialTable->mMaterialName =
            new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
    } else {
        mpMaterialTable->mMaterialName = NULL;
    }
    mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
    mpMaterialTable->mMaterialBase = NULL;
    for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
        mpMaterialTable->mMaterialNodePointer[i] =
            factory.create(NULL, J3DMaterialFactory::MATERIAL_TYPE_PATCHED, i, i_flags);
        mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag =
            ((u32)mpMaterialTable->mMaterialNodePointer >> 4) + factory.getMaterialID(i);
    }
}

/* 802FD390-802FD548       .text readMaterialDL__14J3DModelLoaderFPC18J3DMaterialDLBlockUl */
void J3DModelLoader::readMaterialDL(const J3DMaterialDLBlock* i_block, u32 i_flags) {
    J3DMaterialFactory factory(*i_block);
    if (mpMaterialTable->mMaterialNum == 0) {
        mpMaterialTable->mbIsLocked = 1;
        mpMaterialTable->mMaterialNum = i_block->mMaterialNum;
        mpMaterialTable->mUniqueMatNum = i_block->mMaterialNum;
        if (i_block->mpNameTable != NULL) {
            mpMaterialTable->mMaterialName =
                new JUTNameTab(JSUConvertOffsetToPtr<ResNTAB>(i_block, i_block->mpNameTable));
        } else {
            mpMaterialTable->mMaterialName = NULL;
        }
        mpMaterialTable->mMaterialNodePointer = new J3DMaterial*[mpMaterialTable->mMaterialNum];
        mpMaterialTable->mMaterialBase = NULL;
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i] = factory.create(
                NULL, J3DMaterialFactory::MATERIAL_TYPE_LOCKED, i, (u32)i_flags // cast fixes regalloc
            );
        }
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i]->mDiffFlag = 0xC0000000;
        }
    } else {
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            mpMaterialTable->mMaterialNodePointer[i] = factory.create(
                mpMaterialTable->mMaterialNodePointer[i],
                J3DMaterialFactory::MATERIAL_TYPE_LOCKED, i, (u32)i_flags // cast fixes regalloc
            );
        }
    }
}

/* 802FD548-802FD5C4       .text modifyMaterial__14J3DModelLoaderFUl */
void J3DModelLoader::modifyMaterial(u32 i_flags) {
    if (i_flags & 0x2000) {
        J3DMaterialFactory factory(*mpMaterialBlock);
        for (u16 i = 0; i < mpMaterialTable->mMaterialNum; i++) {
            factory.modifyPatchedCurrentMtx(mpMaterialTable->mMaterialNodePointer[i], i);
        }
    }
}
