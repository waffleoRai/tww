//
// Generated by dtk
// Translation Unit: stb.cpp
//

#include "JSystem/JStudio/JStudio/stb.h"
#include "JSystem/JStudio/JStudio/jstudio-object.h"
#include "dolphin/types.h"
#include "algorithm.h"
#include "string.h"

namespace JStudio {
namespace stb {

/* 80274BE8-80274C30       .text __ct__Q37JStudio3stb7TObjectFUlPCvUl */
TObject::TObject(u32 arg1, const void* id, u32 id_size)
    : TObject_ID(id, id_size), pControl(NULL), signature(arg1), mFlag(0), bSequence_(0), _20(0),
      pSequence(NULL), pSequence_next(NULL), u32Wait_(0), mStatus(STATUS_STILL) {}

/* 80274C30-80274CAC       .text __ct__Q37JStudio3stb7TObjectFRCQ47JStudio3stb4data20TParse_TBlock_object */
TObject::TObject(const data::TParse_TBlock_object& object)
    : TObject_ID(object.get_ID(), object.get_IDSize()), pControl(NULL),
      signature(object.get_type()), mFlag(object.get_flag()), bSequence_(0), _20(0), pSequence(0),
      pSequence_next(object.getContent()), u32Wait_(0), mStatus(STATUS_STILL) {}

/* 80274CAC-80274CF4       .text __dt__Q37JStudio3stb7TObjectFv */
TObject::~TObject() {}

/* 80274CF4-80274D4C       .text setFlag_operation__Q37JStudio3stb7TObjectFUci */
void TObject::setFlag_operation(u8 op, int val) {
    switch (op) {
    default:
        break;
    case 1:
        mFlag |= val;
        break;
    case 2:
        mFlag &= val;
        break;
    case 3:
        mFlag ^= val;
        break;
    }
}

/* 80274D4C-80274D64       .text reset__Q37JStudio3stb7TObjectFPCv */
void TObject::reset(const void* arg1) {
    bSequence_ = 0;
    mStatus = STATUS_STILL;
    pSequence_next = arg1;
    u32Wait_ = 0;
}

/* 80274D64-80274F74       .text forward__Q37JStudio3stb7TObjectFUl */
u8 TObject::forward(u32 arg1) {
    u8 temp = false;

    while (true) {
        if (mFlag & 0x8000) {
            switch (getStatus()) {
            default:
                setStatus_(STATUS_INACTIVE);
                if (bSequence_) {
                    on_end();
                }
                break;
            case STATUS_INACTIVE:
                break;
            }
            return 1;
        }

        if (getStatus() == STATUS_INACTIVE) {
            ASSERT(bSequence_);
            on_begin();
            setStatus_(STATUS_WAIT);
        }
        ASSERT(getStatus() != STATUS_INACTIVE);

        TControl* control = getControl();
        if ((control != NULL && control->isSuspended()) || isSuspended()) {
            if (bSequence_) {
                ASSERT((getStatus() == STATUS_WAIT) || (getStatus() == STATUS_SUSPEND));
                setStatus_(STATUS_SUSPEND);
                on_wait(arg1);
            }
            return 1;
        }

        while (true) {
            void* nextseq = (void*)getSequence_next();
            setSequence_(nextseq);

            if (nextseq == NULL) {
                if (bSequence_) {
                    ASSERT(getStatus() != STATUS_STILL);
                    if (!temp) {
                        on_wait(0);
                    }
                    bSequence_ = false;
                    setStatus_(STATUS_END);
                    on_end();
                }
                return 0;
            }

            if (!bSequence_) {
                ASSERT(getStatus() == STATUS_STILL);
                bSequence_ = true;
                on_begin();
            }
            setStatus_(STATUS_WAIT);
            if (u32Wait_ == 0) {
                process_sequence_();
                if (u32Wait_ == 0) {
                    break;
                }
            }
            ASSERT(u32Wait_ > 0);

            temp = true;
            if (arg1 >= u32Wait_) {
                u32 wait = u32Wait_;
                arg1 -= u32Wait_;
                u32Wait_ = 0;
                on_wait(wait);
            } else {
                u32Wait_ -= arg1;
                on_wait(arg1);
                return 1;
            }
        }
    }
}

/* 80274F74-80274F78       .text do_begin__Q37JStudio3stb7TObjectFv */
void TObject::do_begin() {}

/* 80274F78-80274F7C       .text do_end__Q37JStudio3stb7TObjectFv */
void TObject::do_end() {}

/* 80274F7C-80274F80       .text do_paragraph__Q37JStudio3stb7TObjectFUlPCvUl */
void TObject::do_paragraph(u32, const void*, u32) {}

/* 80274F80-80274F84       .text do_wait__Q37JStudio3stb7TObjectFUl */
void TObject::do_wait(u32) {}

/* 80274F84-80274F88       .text do_data__Q37JStudio3stb7TObjectFPCvUlPCvUl */
void TObject::do_data(const void*, u32, const void*, u32) {}

/* 80274F88-802750DC       .text process_sequence___Q37JStudio3stb7TObjectFv */
void TObject::process_sequence_() {
    data::TParse_TSequence seq(getSequence());

    data::TParse_TSequence::TData dat;

    seq.getData(&dat);
    u8 type = dat.type;
    u32 u32Value = dat.param;
    const void* pContent = dat.content;
    const void* pNext = dat.next;
    setSequence_next(dat.next);

    switch (type) {
    case 0:
        JUT_EXPECT(u32Value == 0);
        JUT_EXPECT(pContent == 0);
        break;
    case 1:
        JUT_EXPECT(pContent == 0);
        setFlag_operation_(u32Value);
        break;
    case 2:
        JUT_EXPECT(pContent == 0);
        setWait(u32Value);
        break;
    case 3:
        JUT_EXPECT(pContent == 0);
        s32 off = toInt32FromUInt24_(u32Value);
        void* nextseq = (void*)getSequence_offset(off);
        setSequence_next(nextseq);
        break;
    case 4:
        JUT_EXPECT(pContent == 0);
        u32 val = toInt32FromUInt24_(u32Value);
        suspend(val);
        break;
    case 0x80:
        ASSERT(pContent != 0);
        void* p = (void*)pContent;
        data::TParse_TParagraph para(NULL);
        while (p < pNext) {
            para.setRaw(p);

            data::TParse_TParagraph::TData para_dat;
            para.getData(&para_dat);
            if (para_dat.type <= 0xff) {
                process_paragraph_reserved_(para_dat.type, para_dat.content, para_dat.param);
            } else {
                on_paragraph(para_dat.type, para_dat.content, para_dat.param);
            }
            p = (void*)para_dat.next;
            ASSERT(p != 0);
        }
        JUT_EXPECT(p == pNext);
        break;
    default:
        break;
    }
}

/* 802750DC-802751C4       .text process_paragraph_reserved___Q37JStudio3stb7TObjectFUlPCvUl */
void TObject::process_paragraph_reserved_(u32 arg1, const void* pContent, u32 uSize) {
    switch (arg1) {
    case 0x1:
        setFlag_operation_(*(u32*)pContent);
        break;
    case 0x2:
        setWait(*(u32*)pContent);
        break;
    case 0x3:
        const void* seq = getSequence_offset(*(s32*)pContent);
        setSequence_next(seq);
        break;
    case 0x80:
        on_data(NULL, 0, pContent, uSize);
        break;
    case 0x81:
        data::TParse_TParagraph_dataID dataID(pContent);
        const void* temp = dataID.getContent();
        on_data(dataID.get_ID(), dataID.get_IDSize(), temp,
                uSize - ((u32)temp - (u32)dataID.getRaw()));
        break;
    case 0x82:
        break;
    }
}

/* 802751C4-80275210       .text __ct__Q37JStudio3stb15TObject_controlFPCvUl */
TObject_control::TObject_control(const void* arg1, u32 arg2) : TObject(-1, arg1, arg2) {}

/* 80275210-80275290       .text __ct__Q37JStudio3stb8TControlFv */
TControl::TControl() : _4(0), _8(0), pFactory(NULL), mObject_control(NULL, 0), _54(0) {
    resetStatus_();
    mObject_control.setControl_(this);
}

/* 802752F0-80275384       .text __dt__Q37JStudio3stb8TControlFv */
TControl::~TControl() {
    mObject_control.setControl_(NULL);
}

/* 80275384-802753D4       .text appendObject__Q37JStudio3stb8TControlFPQ37JStudio3stb7TObject */
void TControl::appendObject(TObject* p) {
    p->setControl_(this);
    mObjectContainer.Push_back(p);
}

/* 802753D4-8027540C       .text removeObject__Q37JStudio3stb8TControlFPQ37JStudio3stb7TObject */
void TControl::removeObject(TObject* p) {
    p->setControl_(NULL);
    mObjectContainer.Erase(p);
}

/* 8027540C-8027545C       .text destroyObject__Q37JStudio3stb8TControlFPQ37JStudio3stb7TObject */
void TControl::destroyObject(TObject* p) {
    removeObject(p);
    pFactory->destroy(p);
}

/* 8027545C-802754C0       .text destroyObject_all__Q37JStudio3stb8TControlFv */
void TControl::destroyObject_all() {
    while (!mObjectContainer.empty()) {
        destroyObject(&mObjectContainer.back());
    }
}

/* 802754C0-80275560       .text getObject__Q37JStudio3stb8TControlFPCvUl */
TObject* TControl::getObject(const void* param_0, u32 param_1) {
    /* Nonmatching - TPRObject_ID_equal copy issue */
    JGadget::TLinkList<TObject, -12>::iterator begin = mObjectContainer.begin();
    JGadget::TLinkList<TObject, -12>::iterator end = mObjectContainer.end();
    JGadget::TLinkList<TObject, -12>::iterator local_50 = std::find_if(begin, end, object::TPRObject_ID_equal(param_0, param_1));
    if ((local_50 != end) != false) {
        return &*local_50;
    }
    return NULL;
}

/* 80275560-8027565C       .text forward__Q37JStudio3stb8TControlFUl */
u8 TControl::forward(u32 param_0) {
    /* Nonmatching - regalloc */
    _54 = mObject_control.getSuspend();
    u8 rv = mObject_control.forward(param_0);
    int uVar7 = 0xf;
    int uVar6 = 0;
    JGadget::TContainerEnumerator<JStudio::stb::TObject, -12> aTStack_38(&mObjectContainer);
    while (aTStack_38) {
        JStudio::stb::TObject& this_00 = *aTStack_38;
        u8 iVar5 = 0;
        u8 iVar4 = this_00.forward(param_0);
        if (iVar4 != 0 || rv != 0) {
            iVar5 = 1;
        }
        rv = iVar5;
        int uVar3 = this_00.getStatus();
        uVar7 &= uVar3;
        uVar6 |= uVar3;
    }
    setStatus_(uVar7 | (uVar6 << 0x10));
    return rv;
}

/* 8027565C-802756A4       .text __dt__Q37JStudio3stb8TFactoryFv */
TFactory::~TFactory() {}

/* 802756A4-802756AC       .text create__Q37JStudio3stb8TFactoryFRCQ47JStudio3stb4data20TParse_TBlock_object */
JStudio::TObject* TFactory::create(const data::TParse_TBlock_object&) {
    return NULL;
}

/* 802756AC-802756E8       .text destroy__Q37JStudio3stb8TFactoryFPQ37JStudio3stb7TObject */
void TFactory::destroy(TObject* p) {
    delete p;
}

/* 802756E8-80275708       .text __ct__Q37JStudio3stb6TParseFPQ37JStudio3stb8TControl */
TParse::TParse(TControl* pControl) : pControl(pControl) {}

/* 80275708-80275768       .text __dt__Q37JStudio3stb6TParseFv */
TParse::~TParse() {}

/* 80275768-80275834       .text parseHeader_next__Q37JStudio3stb6TParseFPPCvPUlUl */
bool TParse::parseHeader_next(const void** ppData_inout, u32* puBlock_out, u32 flags) {
    ASSERT(ppData_inout != 0);
    ASSERT(puBlock_out != 0);

    const void* pData = *ppData_inout;
    ASSERT(pData != 0);

    const data::TParse_THeader header(pData);
    *ppData_inout = header.getContent();
    *puBlock_out = header.get_blockNumber();

    if (memcmp(header.get_signature(), &data::ga4cSignature, 4) != 0) {
        return false;
    }

    if (header.get_byteOrder() != 0xFEFF) {
        return false;
    }
    u16 version = header.get_version();
    if (version < 1) {
        return false;
    } else if (version > 3) {
        return false;
    }
    return parseHeader(header, flags);
}

/* 80275834-80275888       .text parseBlock_next__Q37JStudio3stb6TParseFPPCvPUlUl */
bool TParse::parseBlock_next(void const** ppData_inout, u32* puData_out, u32 flags) {
    const void* pData = *ppData_inout;

    data::TParse_TBlock blk(pData);
    *ppData_inout = blk.getNext();
    *puData_out = blk.get_size();
    return parseBlock_block(blk, flags);
}

/* 80275888-80275890       .text parseHeader__Q37JStudio3stb6TParseFRCQ47JStudio3stb4data14TParse_THeaderUl */
bool TParse::parseHeader(const data::TParse_THeader&, u32) {
    return true;
}

/* 80275890-802758C8       .text parseBlock_block__Q37JStudio3stb6TParseFRCQ47JStudio3stb4data13TParse_TBlockUl */
bool TParse::parseBlock_block(const data::TParse_TBlock& ppBlock, u32 flags) {
    return parseBlock_object(ppBlock.get(), flags);
}

/* 802758C8-802759D0       .text parseBlock_object__Q37JStudio3stb6TParseFRCQ47JStudio3stb4data20TParse_TBlock_objectUl */
bool TParse::parseBlock_object(const data::TParse_TBlock_object& ppObject, u32 flags) {
    TControl* pControl = getControl();
    ASSERT(pControl != 0);

    if (ppObject.get_type() == data::BLOCK_NONE) {
        TObject_control& ref = pControl->referObject_control();
        ref.reset(ppObject.getContent());
        return true;
    }

    if (flags & 0x10) {
        TObject* p = pControl->getObject(ppObject.get_ID(), ppObject.get_IDSize());
        if (p != NULL) {
            p->reset(ppObject.getContent());
            return true;
        }
    }

    if (flags & 0x20)
        return true;

    TFactory* pFactory = pControl->getFactory();
    if (pFactory == NULL) {
        return false;
    }

    JStudio::TObject* p = pFactory->create(ppObject);
    if (p == NULL) {
        if (flags & 0x40)
            return true;

        char a5c[8];
        char t[16];
        int type = ppObject.get_type();
        data::toString_block(a5c, type);

        return false;
    }
    pControl->appendObject(p);
    return true;
}

}  // namespace stb
}  // namespace JStudio
