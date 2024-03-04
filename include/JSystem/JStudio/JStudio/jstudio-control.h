#ifndef JSTUDIO_CONTROL_H
#define JSTUDIO_CONTROL_H

#include "JSystem/JStudio/JStudio/fvb.h"
#include "JSystem/JStudio/JStudio/stb.h"
#include "dolphin/gx/GX.h"
#include "dolphin/mtx/vec.h"

namespace JStudio {
struct TObject;
struct TCreateObject {
    TCreateObject() {}
    virtual ~TCreateObject() = 0;
    virtual bool create(TObject**, JStudio::stb::data::TParse_TBlock_object const&) = 0;

    /* 0x4 */ JGadget::TLinkListNode mNode;
};  // Size: 0xC

struct TFactory : public stb::TFactory {
    TFactory() {}

    virtual ~TFactory();
    virtual TObject* create(JStudio::stb::data::TParse_TBlock_object const&);

    void appendCreateObject(JStudio::TCreateObject*);

    /* 0x04 */ JGadget::TLinkList<TCreateObject, -4> mList;
    /* 0x10 */ fvb::TFactory fvb_Factory;
};

class TControl : public stb::TControl {
public:
    struct TTransform_translation_rotation_scaling {};
    struct TTransform_position {};

    TControl();
    virtual ~TControl();
    void setFactory(JStudio::TFactory*);
    void transformOnSet_setOrigin(const Vec&, f32);
    void transformOnGet_setOrigin(const Vec&, f32);

    void stb_destroyObject_all() { stb::TControl::destroyObject_all(); }
    void fvb_destroyObject_all() { fvb_Control.destroyObject_all(); }

    void destroyObject_all() {
        stb_destroyObject_all();
        fvb_destroyObject_all();
    }

    void transformOnSet_enable(bool param_0) { mTransformOnSet = param_0; }
    void transformOnGet_enable(bool param_0) { mTransformOnGet = param_0; }

    void transform_enable(bool param_0) {
        transformOnSet_enable(param_0);
        transformOnGet_enable(param_0);
    }

    void transform_setOrigin(const Vec& xyz, f32 rotY) {
        transformOnSet_setOrigin(xyz, rotY);
        transformOnGet_setOrigin(xyz, rotY);
    }

    void setSecondPerFrame(f64 param_0) { mSecondPerFrame = param_0; }
    f64 getSecondPerFrame() const { return mSecondPerFrame; }


    fvb::TObject* fvb_getObject(const void* param_1, u32 param_2) {
        return fvb_Control.getObject(param_1, param_2);
    }

    fvb::TObject* fvb_getObject_index(u32 index) {
        return fvb_Control.getObject_index(index);
    }

    TFunctionValue* getFunctionValue(const void* param_1, u32 param_2) {
        fvb::TObject* obj = fvb_getObject(param_1, param_2);
        if (obj == NULL) {
            return NULL;
        } 
        return obj->referFunctionValue();
    }

    TFunctionValue* getFunctionValue_index(u32 index) {
        fvb::TObject* obj = fvb_getObject_index(index);
        if (obj == NULL) {
            return NULL;
        } 
        return obj->referFunctionValue();
    }

    /* 0x58 */ f64 mSecondPerFrame;
    /* 0x60 */ fvb::TControl fvb_Control;
    /* 0x74 */ bool mTransformOnSet;
    /* 0x75 */ bool mTransformOnGet;
    /* 0x78 */ Vec field_0x8c;
    /* 0x84 */ Vec field_0x98;
    /* 0x90 */ f32 mTransformOnSet_RotationY;
    /* 0x94 */ f32 field_0xa8;
    /* 0x98 */ Mtx mTransformOnSet_Matrix;
    /* 0xC8 */ Mtx mTransformOnGet_Matrix;
};

struct TParse : public stb::TParse {
    TParse(JStudio::TControl*);
    bool parseBlock_block_fvb_(JStudio::stb::data::TParse_TBlock const&, u32);

    virtual ~TParse();
    virtual bool parseHeader(JStudio::stb::data::TParse_THeader const&, u32);
    virtual bool parseBlock_block(JStudio::stb::data::TParse_TBlock const&, u32);

    TControl* getControl() { return (TControl*)stb::TParse::getControl(); }
};

};  // namespace JStudio

#endif /* JSTUDIO_CONTROL_H */
