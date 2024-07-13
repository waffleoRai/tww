//
// Generated by dtk
// Translation Unit: JKRExpHeap.cpp
//

#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JSupport/JSupport.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTException.h"
#include "dolphin/os/OS.h"
#include "dolphin/types.h"
#include "new.h"

/* 802B1558-802B15D0       .text createRoot__10JKRExpHeapFib */
JKRExpHeap* JKRExpHeap::createRoot(int maxHeaps, bool errorFlag) {
    JKRExpHeap* heap = NULL;
    if (!sRootHeap) {
        void* memory;
        u32 memorySize;
        initArena((char**)&memory, &memorySize, maxHeaps);
        u8* start = (u8*)memory + OSRoundUp(sizeof(JKRExpHeap), 0x10);
        u32 alignedSize = memorySize - OSRoundUp(sizeof(JKRExpHeap), 0x10);
        heap = new (memory) JKRExpHeap(start, alignedSize, NULL, errorFlag);
        sRootHeap = heap;
    }
    heap->field_0x6e = true;
    return heap;
}

/* 802B15D0-802B16A4       .text create__10JKRExpHeapFUlP7JKRHeapb */
JKRExpHeap* JKRExpHeap::create(u32 size, JKRHeap* parent, bool errorFlag) {
    if (!parent) {
        parent = sRootHeap;
    }

    if (size == 0xffffffff) {
        size = parent->getMaxAllocatableSize(0x10);
    }

    u32 alignedSize = OSRoundDown(size, 0x10);
    u32 expHeapSize = OSRoundUp(sizeof(JKRExpHeap), 0x10);
    if (alignedSize < 0xa0)
        return NULL;

    u8* memory = (u8*)JKRAllocFromHeap(parent, alignedSize, 0x10);
    u8* dataPtr = (memory + expHeapSize);
    if (!memory) {
        return NULL;
    }

    JKRExpHeap* newHeap =
        new (memory) JKRExpHeap(dataPtr, alignedSize - expHeapSize, parent, errorFlag);

    if (newHeap == NULL) {
        JKRFree(memory);
        return NULL;
    }

    newHeap->field_0x6e = false;
    return newHeap;
}

/* 802B16A4-802B1728       .text do_destroy__10JKRExpHeapFv */
void JKRExpHeap::do_destroy() {
    if (!field_0x6e) {
        JKRHeap* heap = mChildTree.getParent()->getObject();
        if (heap) {
            this->~JKRExpHeap();
            JKRHeap::free(this, heap);
        }
    } else {
        this->~JKRExpHeap();
    }
}

/* 802B1728-802B17B8       .text __ct__10JKRExpHeapFPvUlP7JKRHeapb */
JKRExpHeap::JKRExpHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag) : JKRHeap(data, size, parent, errorFlag) {
    mAllocMode = 0;
    mCurrentGroupId = 0xff;
    mHeadFreeList = (CMemBlock*)data;
    mTailFreeList = mHeadFreeList;
    mHeadFreeList->initiate(NULL, NULL, size - sizeof(CMemBlock), 0, 0);
    mHeadUsedList = NULL;
    mTailUsedList = NULL;
}

/* 802B17B8-802B1820       .text __dt__10JKRExpHeapFv */
JKRExpHeap::~JKRExpHeap() {
    dispose();
}

/* 802B1820-802B192C       .text do_alloc__10JKRExpHeapFUli */
void* JKRExpHeap::do_alloc(u32 size, int alignment) {
    void* ptr;

    lock();
    if (size < 4) {
        size = 4;
    }

    if (alignment >= 0) {
        if (alignment <= 4) {
            ptr = allocFromHead(size);
        } else {
            ptr = allocFromHead(size, alignment);
        }
    } else {
        if (-alignment <= 4) {
            ptr = allocFromTail(size);
        } else {
            ptr = allocFromTail(size, -alignment);
        }
    }

    if (ptr == NULL) {
        JUTWarningConsole_f(":::cannot alloc memory (0x%x byte).\n", size);
        if (mErrorFlag == true) {
            callErrorHandler(this, size, alignment);
        }
    }
    unlock();

    return ptr;
}

static u32 DBfoundSize;
static u32 DBfoundOffset;
static JKRExpHeap::CMemBlock* DBfoundBlock;
static JKRExpHeap::CMemBlock* DBnewFreeBlock;
static JKRExpHeap::CMemBlock* DBnewUsedBlock;

/* 802B192C-802B1B88       .text allocFromHead__10JKRExpHeapFUli */
// wrong register at end
void* JKRExpHeap::allocFromHead(u32 size, int align) {
    u32 foundOffset;
    int foundSize;
    CMemBlock* newFreeBlock;
    CMemBlock* newUsedBlock;
    CMemBlock* foundBlock;

    size = ALIGN_NEXT(size, 4);
    foundSize = -1;
    foundOffset = 0;
    foundBlock = NULL;

    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        u32 offset =
            ALIGN_PREV(align - 1 + (u32)block->getContent(), align) - (u32)block->getContent();
        if (block->size < size + offset) {
            continue;
        }

        if (foundSize <= (u32)block->size) {
            continue;
        }

        foundSize = block->size;
        foundBlock = block;
        foundOffset = offset;
        if (mAllocMode != 0) {
            break;
        }

        u32 blockSize = block->size;
        if (blockSize == size) {
            break;
        }
    }

    DBfoundSize = foundSize;
    DBfoundOffset = foundOffset;
    DBfoundBlock = foundBlock;

    if (foundBlock) {
        if (foundOffset >= sizeof(CMemBlock)) {
            CMemBlock* prev = foundBlock->mPrev;
            CMemBlock* next = foundBlock->mNext;
            newUsedBlock = foundBlock->allocFore(foundOffset - sizeof(CMemBlock), 0, 0, 0, 0);

            if (newUsedBlock) {
                newFreeBlock = newUsedBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
            } else {
                newFreeBlock = NULL;
            }

            if (newFreeBlock) {
                setFreeBlock(foundBlock, prev, newFreeBlock);
            } else {
                setFreeBlock(foundBlock, prev, next);
            }

            if (newFreeBlock) {
                setFreeBlock(newFreeBlock, foundBlock, next);
            }

            appendUsedList(newUsedBlock);
            DBnewFreeBlock = newFreeBlock;
            DBnewUsedBlock = newUsedBlock;
            return newUsedBlock->getContent();
        } else {
            if (foundOffset != 0) {
                CMemBlock* prev = foundBlock->mPrev;
                CMemBlock* next = foundBlock->mNext;
                removeFreeBlock(foundBlock);
                newUsedBlock = (CMemBlock*)((u32)foundBlock + foundOffset);
                newUsedBlock->size = foundBlock->size - foundOffset;
                newFreeBlock =
                    newUsedBlock->allocFore(size, mCurrentGroupId, (u8)foundOffset, 0, 0);
                if (newFreeBlock) {
                    setFreeBlock(newFreeBlock, prev, next);
                }
                appendUsedList(newUsedBlock);
                return newUsedBlock->getContent();
            } else {
                CMemBlock* prev = foundBlock->mPrev;
                CMemBlock* next = foundBlock->mNext;
                // Regalloc doesn't match
                /*
                newFreeBlock = foundBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
                removeFreeBlock(foundBlock);
                if (newFreeBlock) {
                    setFreeBlock(newFreeBlock, prev, next);
                }
                */
                // Works but very fake match
                // /*
                size = (u32)foundBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
                removeFreeBlock(foundBlock);
                if (size) {
                    setFreeBlock((CMemBlock*)size, prev, next);
                }
                // */
                appendUsedList(foundBlock);
                return foundBlock->getContent();
            }
        }
    }

    return NULL;
}

/* 802B1B88-802B1C6C       .text allocFromHead__10JKRExpHeapFUl */
void* JKRExpHeap::allocFromHead(u32 size) {
    size = ALIGN_NEXT(size, 4);
    s32 foundSize = -1;
    CMemBlock* foundBlock = NULL;
    for (CMemBlock* block = mHeadFreeList; block; block = block->getNextBlock()) {
        if (block->getSize() < size) {
            continue;
        }

        if (foundSize <= block->getSize()) {
            continue;
        }

        foundSize = block->getSize();
        foundBlock = block;
        if (mAllocMode != 0) {
            break;
        }

        if (foundSize == size) {
            break;
        }
    }

    if (foundBlock) {
        CMemBlock* newblock = foundBlock->allocFore(size, mCurrentGroupId, 0, 0, 0);
        if (newblock) {
            setFreeBlock(newblock, foundBlock->getPrevBlock(), foundBlock->getNextBlock());
        } else {
            removeFreeBlock(foundBlock);
        }
        appendUsedList(foundBlock);
        return foundBlock->getContent();
    }
    return NULL;
}

/* 802B1C6C-802B1DCC       .text allocFromTail__10JKRExpHeapFUli */
void* JKRExpHeap::allocFromTail(u32 size, int align) {
    u32 offset = 0;
    CMemBlock* foundBlock = NULL;
    CMemBlock* newBlock = NULL;
    u32 usedSize;
    u32 start;

    for (CMemBlock* block = mTailFreeList; block; block = block->mPrev) {
        start = ALIGN_PREV((u32)block->getContent() + block->size - size, align);
        usedSize = (u32)block->getContent() + block->size - start;
        if (block->size >= usedSize) {
            foundBlock = block;
            offset = block->size - usedSize;
            newBlock = (CMemBlock*)start - 1;
            break;
        }
    }

    if (foundBlock != NULL) {
        if (offset >= sizeof(CMemBlock)) {
            newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, -0x80);
            foundBlock->size = foundBlock->size - usedSize - sizeof(CMemBlock);
            appendUsedList(newBlock);
            return newBlock->getContent();
        } else {
            if (offset != 0) {
                removeFreeBlock(foundBlock);
                newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, offset | 0x80);
                appendUsedList(newBlock);
                return newBlock->getContent();
            } else {
                removeFreeBlock(foundBlock);
                newBlock->initiate(NULL, NULL, usedSize, mCurrentGroupId, -0x80);
                appendUsedList(newBlock);
                return newBlock->getContent();
            }
        }
    }

    return NULL;
}

/* 802B1DCC-802B1EA4       .text allocFromTail__10JKRExpHeapFUl */
void* JKRExpHeap::allocFromTail(u32 size) {
    u32 size2 = ALIGN_NEXT(size, 4);
    CMemBlock* foundBlock = NULL;
    for (CMemBlock* block = mTailFreeList; block; block = block->getPrevBlock()) {
        if (block->getSize() >= size2) {
            foundBlock = block;
            break;
        }
    }

    if (foundBlock != NULL) {
        CMemBlock* usedBlock = foundBlock->allocBack(size2, 0, 0, mCurrentGroupId, 0);
        CMemBlock* freeBlock;
        if (usedBlock) {
            freeBlock = foundBlock;
        } else {
            removeFreeBlock(foundBlock);
            usedBlock = foundBlock;
            freeBlock = NULL;
        }

        if (freeBlock) {
            setFreeBlock(freeBlock, foundBlock->getPrevBlock(), foundBlock->getNextBlock());
        }
        appendUsedList(usedBlock);
        return usedBlock->getContent();
    }
    return NULL;
}

/* 802B1EA4-802B1F44       .text do_free__10JKRExpHeapFPv */
void JKRExpHeap::do_free(void* ptr) {
    lock();
    if (getStartAddr() <= ptr && ptr <= getEndAddr()) {
        CMemBlock* block = CMemBlock::getHeapBlock(ptr);
        if (block) {
            block->free(this);
        }
    } else {
        JUT_WARN(888, "free: memblock %x not in heap %x", ptr, this);
    }
    unlock();
}

/* 802B1F44-802B1FC0       .text do_freeAll__10JKRExpHeapFv */
void JKRExpHeap::do_freeAll() {
    lock();
    JKRHeap::callAllDisposer();
    mHeadFreeList = (CMemBlock*)getStartAddr();
    mTailFreeList = mHeadFreeList;
    mHeadFreeList->initiate(NULL, NULL, getSize() - 0x10, 0, 0);
    mHeadUsedList = NULL;
    mTailUsedList = NULL;
    unlock();
}

/* 802B1FC0-802B2048       .text do_freeTail__10JKRExpHeapFv */
void JKRExpHeap::do_freeTail() {
    lock();
    for (CMemBlock* block = mHeadUsedList; block != NULL;) {
        if ((block->mFlags & 0x80) != 0) {
            dispose(block + 1, block->size);
            CMemBlock* temp = block->mNext;
            block->free(this);
            block = temp;
        } else {
            block = block->mNext;
        }
    }
    unlock();
}

/* 802B2048-802B2098       .text do_changeGroupID__10JKRExpHeapFUc */
s32 JKRExpHeap::do_changeGroupID(u8 groupId) {
    lock();
    u8 prev = mCurrentGroupId;
    mCurrentGroupId = groupId;
    unlock();
    return prev;
}

/* 802B2098-802B2244       .text do_resize__10JKRExpHeapFPvUl */
s32 JKRExpHeap::do_resize(void* ptr, u32 size) {
    lock();
    CMemBlock* block = CMemBlock::getHeapBlock(ptr);
    if (block == NULL || ptr < mStart || mEnd < ptr) {
        unlock();
        return -1;
    }

    size = ALIGN_NEXT(size, 4);
    if (size == block->size) {
        unlock();
        return size;
    }

    if (size > block->size) {
        CMemBlock* foundBlock = NULL;
        for (CMemBlock* freeBlock = mHeadFreeList; freeBlock; freeBlock = freeBlock->mNext) {
            if (freeBlock == (CMemBlock*)((u32)(block + 1) + block->size)) {
                foundBlock = freeBlock;
                break;
            }
        }

        if (foundBlock == NULL) {
            unlock();
            return -1;
        }

        if (size > block->size + sizeof(CMemBlock) + foundBlock->size) {
            unlock();
            return -1;
        }

        removeFreeBlock(foundBlock);
        block->size += foundBlock->size + sizeof(CMemBlock);
        if (block->size - size > sizeof(CMemBlock)) {
            CMemBlock* newBlock = block->allocFore(size, block->mGroupId, block->mFlags, 0, 0);
            if (newBlock) {
                recycleFreeBlock(newBlock);
            }
        }
    } else {
        if (block->size - size > sizeof(CMemBlock)) {
            CMemBlock* freeBlock = block->allocFore(size, block->mGroupId, block->mFlags, 0, 0);
            if (freeBlock) {
                recycleFreeBlock(freeBlock);
            }
        }
    }

    unlock();
    return block->size;
}

/* 802B2244-802B22C4       .text do_getSize__10JKRExpHeapFPv */
s32 JKRExpHeap::do_getSize(void* ptr) {
    lock();
    CMemBlock* block = CMemBlock::getHeapBlock(ptr);
    if (!block || ptr < getStartAddr() || getEndAddr() < ptr) {
        unlock();
        return -1;
    }
    unlock();
    return block->getSize();
}

/* 802B22C4-802B2330       .text do_getFreeSize__10JKRExpHeapFv */
s32 JKRExpHeap::do_getFreeSize() {
    lock();
    s32 size = 0;
    for (CMemBlock* block = mHeadFreeList; block; block = block->getNextBlock()) {
        if (size < (s32)block->getSize()) {
            size = block->getSize();
        }
    }
    unlock();
    return size;
}

/* 802B2330-802B23A4       .text do_getMaxFreeBlock__10JKRExpHeapFv */
void* JKRExpHeap::do_getMaxFreeBlock() {
    lock();
    s32 size = 0;
    CMemBlock* res = NULL;
    for (CMemBlock* block = mHeadFreeList; block; block = block->getNextBlock()) {
        if (size < (s32)block->getSize()) {
            size = block->getSize();
            res = block;
        }
    }
    unlock();
    return res;
}

/* 802B23A4-802B2408       .text do_getTotalFreeSize__10JKRExpHeapFv */
s32 JKRExpHeap::do_getTotalFreeSize() {
    u32 size = 0;
    lock();
    for (CMemBlock* block = mHeadFreeList; block; block = block->getNextBlock()) {
        size += block->getSize();
    }
    unlock();
    return size;
}

/* 802B2408-802B2484       .text getUsedSize__10JKRExpHeapCFUc */
s32 JKRExpHeap::getUsedSize(u8 groupId) const {
    JKRExpHeap* this2 = const_cast<JKRExpHeap*>(this);
    this2->lock();
    u32 size = 0;

    for (CMemBlock* block = mHeadUsedList; block; block = block->getNextBlock()) {
        u8 blockGroupId = block->getGroupId();
        if (blockGroupId == groupId) {
            size += block->getSize() + sizeof(CMemBlock);
        }
    }

    this2->unlock();
    return size;
}

/* 802B2484-802B24EC       .text getTotalUsedSize__10JKRExpHeapCFv */
s32 JKRExpHeap::getTotalUsedSize() const {
    JKRExpHeap* this2 = const_cast<JKRExpHeap*>(this);
    this2->lock();
    u32 size = 0;

    for (CMemBlock* block = mHeadUsedList; block; block = block->getNextBlock()) {
        size += block->getSize() + sizeof(CMemBlock);
    }

    this2->unlock();
    return size;
}

static void dummy1() {
    OSReport("newSize > 0");
    OSReport("Halt");
}

/* 802B24EC-802B2584       .text appendUsedList__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::appendUsedList(CMemBlock* newblock) {
    if (!newblock) {
        OSPanic(__FILE__, 1466, ":::ERROR! appendUsedList\n");
    }

    CMemBlock* block = mTailUsedList;
    newblock->mMagic = 'HM';

    if (block) {
        block->mNext = newblock;
        newblock->mPrev = block;
    } else {
        newblock->mPrev = NULL;
    }

    mTailUsedList = newblock;
    if (!mHeadUsedList) {
        mHeadUsedList = newblock;
    }
    newblock->mNext = NULL;
}

/* 802B2584-802B25D0       .text setFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::setFreeBlock(CMemBlock* block, CMemBlock* prev, CMemBlock* next) {
    if (prev == NULL) {
        mHeadFreeList = block;
        block->mPrev = NULL;
    } else {
        prev->mNext = block;
        block->mPrev = prev;
    }

    if (next == NULL) {
        mTailFreeList = block;
        block->mNext = NULL;
    } else {
        next->mPrev = block;
        block->mNext = next;
    }

    block->mMagic = 0;
}

/* 802B25D0-802B2604       .text removeFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::removeFreeBlock(CMemBlock* block) {
    CMemBlock* prev = block->mPrev;
    CMemBlock* next = block->mNext;

    if (prev == NULL) {
        mHeadFreeList = next;
    } else {
        prev->mNext = next;
    }

    if (next == NULL) {
        mTailFreeList = prev;
    } else {
        next->mPrev = prev;
    }
}

/* 802B2604-802B2638       .text removeUsedBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::removeUsedBlock(CMemBlock* block) {
    CMemBlock* prev = block->mPrev;
    CMemBlock* next = block->mNext;

    if (prev == NULL) {
        mHeadUsedList = next;
    } else {
        prev->mNext = next;
    }

    if (next == NULL) {
        mTailUsedList = prev;
    } else {
        next->mPrev = prev;
    }
}

/* 802B2638-802B27D0       .text recycleFreeBlock__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::recycleFreeBlock(CMemBlock* block) {
    JKRExpHeap::CMemBlock* newBlock = block;
    int size = block->size;
    void* blockEnd = (u8*)block + size;
    block->mMagic = 0;

    if ((block->mFlags & 0x7f) != 0) {
        newBlock = (CMemBlock*)((u8*)block - (block->mFlags & 0x7f));
        size += (block->mFlags & 0x7f);
        blockEnd = (u8*)newBlock + size;
        newBlock->mGroupId = 0;
        newBlock->mFlags = 0;
        newBlock->size = size;
    }

    if (!mHeadFreeList) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        mHeadFreeList = newBlock;
        mTailFreeList = newBlock;
        setFreeBlock(newBlock, NULL, NULL);
        return;
    }

    if (mHeadFreeList >= blockEnd) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        setFreeBlock(newBlock, NULL, mHeadFreeList);
        joinTwoBlocks(newBlock);
        return;
    }

    if (mTailFreeList <= newBlock) {
        newBlock->initiate(NULL, NULL, size, 0, 0);
        setFreeBlock(newBlock, mTailFreeList, NULL);
        joinTwoBlocks(newBlock->mPrev);
        return;
    }

    for (CMemBlock* freeBlock = mHeadFreeList; freeBlock; freeBlock = freeBlock->mNext) {
        if (freeBlock >= newBlock || newBlock >= freeBlock->mNext) {
            continue;
        }
        newBlock->mNext = freeBlock->mNext;
        newBlock->mPrev = freeBlock;
        freeBlock->mNext = newBlock;
        newBlock->mNext->mPrev = newBlock;
        newBlock->mGroupId = 0;
        joinTwoBlocks(newBlock);
        joinTwoBlocks(freeBlock);
        return;
    }
}

/* 802B27D0-802B291C       .text joinTwoBlocks__10JKRExpHeapFPQ210JKRExpHeap9CMemBlock */
void JKRExpHeap::joinTwoBlocks(CMemBlock* block) {
    u32 curBlock = (u32)block; // Fakematch?
    u32 endAddr = (u32)(block + 1) + block->size;
    CMemBlock* next = block->mNext;
    u32 nextAddr = (u32)next - (next->mFlags & 0x7f);
    if (endAddr > nextAddr) {
        JUTWarningConsole_f(":::Heap may be broken. (block = %x)", block);
        OSReport(":::block = %x\n", curBlock);
        OSReport(":::joinTwoBlocks [%x %x %x][%x %x %x]\n", block, block->mFlags, block->size, block->mNext, block->mNext->mFlags, block->mNext->size);
        OSReport(":::: endAddr = %x\n", endAddr);
        OSReport(":::: nextAddr = %x\n", nextAddr);
        JKRGetCurrentHeap()->dump();
        OSPanic(__FILE__, 1718, ":::: Bad Block\n");
    }

    if (endAddr == nextAddr) {
        block->size = next->size + sizeof(CMemBlock) + next->getAlignment() + block->size;
        setFreeBlock(block, block->mPrev, next->mNext);
    }
}

/* 802B291C-802B2B44       .text check__10JKRExpHeapFv */
bool JKRExpHeap::check() {
    lock();
    int totalBytes = 0;
    bool ok = true;
    for (CMemBlock* block = mHeadUsedList; block; block = block->mNext) {
        if (!block->isValid()) {
            ok = false;
            JUTWarningConsole_f(":::addr %08x: bad heap signature. (%c%c)\n", block,
                                JSUHiByte(block->mMagic), JSULoByte(block->mMagic));
        }

        if (block->mNext) {
            if (!block->mNext->isValid()) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad next pointer (%08x)\nabort\n", block,
                                    block->mNext);
                break;
            }
            if (block->mNext->mPrev != block) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad previous pointer (%08x)\n", block->mNext,
                                    block->mNext->mPrev);
            }
        } else {
            if (mTailUsedList != block) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad used list(REV) (%08x)\n", block,
                                    mTailUsedList);
            }
        }
        totalBytes += sizeof(CMemBlock) + block->size + block->getAlignment();
    }

    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        totalBytes += block->size + sizeof(CMemBlock);
        if (block->mNext) {
            if (block->mNext->mPrev != block) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad previous pointer (%08x)\n", block->mNext,
                                    block->mNext->mPrev);
            }

            if ((u32)block + block->size + sizeof(CMemBlock) > (u32)block->mNext) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad block size (%08x)\n", block, block->size);
            }
        } else {
            if (mTailFreeList != block) {
                ok = false;
                JUTWarningConsole_f(":::addr %08x: bad used list(REV) (%08x)\n", block,
                                    mTailFreeList);
            }
        }
    }

    if (totalBytes != mSize) {
        ok = false;
        JUTWarningConsole_f(":::bad total memory block size (%08X, %08X)\n", mSize, totalBytes);
    }

    if (!ok) {
        JUTWarningConsole(":::there is some error in this heap!\n");
    }

    unlock();
    return ok;
}

/* 802B2B44-802B2B48       .text do_freeFill__10JKRExpHeapFv */
void JKRExpHeap::do_freeFill() {}

/* 802B2B48-802B2D5C       .text dump__10JKRExpHeapFv */
bool JKRExpHeap::dump() {
    lock();
    bool result = check();
    u32 usedBytes = 0;
    u32 usedCount = 0;
    u32 freeCount = 0;

    JUTReportConsole(" attr  address:   size    gid aln   prev_ptr next_ptr\n");
    JUTReportConsole("(Used Blocks)\n");
    if (!mHeadUsedList) {
        JUTReportConsole(" NONE\n");
    }

    for (CMemBlock* block = mHeadUsedList; block; block = block->mNext) {
        if (!block->isValid()) {
            JUTReportConsole_f("xxxxx %08x: --------  --- ---  (-------- --------)\nabort\n",
                               block);
            break;
        }

        JUTReportConsole_f("%s %08x: %08x  %3d %3d  (%08x %08x)\n",
                           block->_isTempMemBlock() ? " temp" : "alloc", block->getContent(),
                           block->size, block->mGroupId, block->getAlignment(), block->mPrev,
                           block->mNext);
        usedBytes += sizeof(CMemBlock) + block->size + block->getAlignment();
        usedCount++;
    }

    JUTReportConsole("(Free Blocks)\n");
    if (!mHeadFreeList) {
        JUTReportConsole(" NONE\n");
    }

    for (CMemBlock* block = mHeadFreeList; block; block = block->mNext) {
        JUTReportConsole_f("%s %08x: %08x  %3d %3d  (%08x %08x)\n", " free", block->getContent(),
                           block->size, block->mGroupId, block->getAlignment(), block->mPrev,
                           block->mNext);
        freeCount++;
    }

    float percent = ((float)usedBytes / (float)mSize) * 100.0f;
    JUTReportConsole_f("%d / %d bytes (%6.2f%%) used (U:%d F:%d)\n", usedBytes, mSize, percent,
                       usedCount, freeCount);
    unlock();
    return result;
}

/* 802B2D5C-802B2F5C       .text dump_sort_by_address__10JKRExpHeapFv */
bool JKRExpHeap::dump_sort_by_address() {
    lock();
    bool result = check();
    u32 usedBytes = 0;
    u32 usedCount = 0;
    u32 freeCount = 0;
    JUTReportConsole(" attr  address:   size    gid aln   prev_ptr next_ptr\n");

    CMemBlock* block;
    for (CMemBlock* nextBlock = NULL; ; nextBlock = block) {
        block = (CMemBlock*)0xffffffff;

        for (CMemBlock* iterBlock = mHeadFreeList; iterBlock; iterBlock = iterBlock->getNextBlock()) {
            if (nextBlock < iterBlock && iterBlock < block) {
                block = iterBlock;
            }
        }

        for (CMemBlock* iterBlock = mHeadUsedList; iterBlock; iterBlock = iterBlock->getNextBlock()) {
            if (nextBlock < iterBlock && iterBlock < block) {
                block = iterBlock;
            }
        }

        if (block == (CMemBlock*)0xffffffff) {
            break;
        }

        if (block->mMagic == 0) {
            JUTReportConsole_f("%s %08x: %08x  %3d %3d  (%08x %08x)\n", " free", block->getContent(), block->getSize(), block->getGroupId(), block->getAlignment(), block->getPrevBlock(), block->getNextBlock());
            freeCount += 1;
            continue;
        }

        if (!block->isValid()) {
            JUTReportConsole_f("xxxxx %08x: --------  --- ---  (-------- --------)\nabort\n", nextBlock);
            break;
        }

        int offset = block->getAlignment();
        void* content = block->getContent();
        const char* type = block->_isTempMemBlock() ? " temp" : "alloc";
        JUTReportConsole_f("%s %08x: %08x  %3d %3d  (%08x %08x)\n", type, content, block->getSize(), block->getGroupId(), offset, block->getPrevBlock(), block->getNextBlock());
        usedBytes += sizeof(CMemBlock) + block->size + block->getAlignment();
        usedCount++;
    }

    float percent = ((float)usedBytes / (float)mSize) * 100.0f;
    JUTReportConsole_f("%d / %d bytes (%6.2f%%) used (U:%d F:%d)\n", usedBytes, mSize, percent, usedCount, freeCount);
    unlock();
    return result;
}

/* 802B2F5C-802B2F7C       .text dump_sort__10JKRExpHeapFv */
bool JKRExpHeap::dump_sort() {
    return dump_sort_by_address();
}

/* 802B2F7C-802B2F9C       .text initiate__Q210JKRExpHeap9CMemBlockFPQ210JKRExpHeap9CMemBlockPQ210JKRExpHeap9CMemBlockUlUcUc */
void JKRExpHeap::CMemBlock::initiate(CMemBlock* prev, CMemBlock* next, u32 size, u8 groupId, u8 alignment) {
    mMagic = 'HM';
    mFlags = alignment;
    mGroupId = groupId;
    this->size = size;
    mPrev = prev;
    mNext = next;
}

/* 802B2F9C-802B2FE0       .text allocFore__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc */
JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::allocFore(u32 size, u8 groupId1, u8 alignment1, u8 groupId2, u8 alignment2) {
    CMemBlock* block = NULL;
    mGroupId = groupId1;
    mFlags = alignment1;
    if (getSize() >= size + sizeof(CMemBlock)) {
        block = (CMemBlock*)(size + (u32)this);
        block[1].mGroupId = groupId2;
        block[1].mFlags = alignment2;
        block[1].size = this->size - (size + sizeof(CMemBlock));
        this->size = size;
        block = block + 1;
    }
    return block;
}

/* 802B2FE0-802B3038       .text allocBack__Q210JKRExpHeap9CMemBlockFUlUcUcUcUc */
JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::allocBack(u32 size, u8 groupId1, u8 alignment1, u8 groupId2, u8 alignment2) {
    CMemBlock* newblock = NULL;
    if (getSize() >= size + sizeof(CMemBlock)) {
        newblock = (CMemBlock*)((u32)this + getSize() - size);
        newblock->mGroupId = groupId2;
        newblock->mFlags = alignment2 | 0x80;
        newblock->size = size;
        mGroupId = groupId1;
        mFlags = alignment1;
        this->size -= size + sizeof(CMemBlock);
    } else {
        mGroupId = groupId2;
        mFlags = 0x80;
    }
    return newblock;
}

/* 802B3038-802B3088       .text free__Q210JKRExpHeap9CMemBlockFP10JKRExpHeap */
int JKRExpHeap::CMemBlock::free(JKRExpHeap* heap) {
    heap->removeUsedBlock(this);
    heap->recycleFreeBlock(this);
    return 0;
}

/* 802B3088-802B30A4       .text getHeapBlock__Q210JKRExpHeap9CMemBlockFPv */
JKRExpHeap::CMemBlock* JKRExpHeap::CMemBlock::getHeapBlock(void* ptr) {
    if (ptr) {
        CMemBlock* block = (CMemBlock*)ptr - 1;
        if (block->isValid()) {
            return block;
        }
    }
    return NULL;
}

static void dummy2() {
    OSReport("+---------------JKRExpHeap\n");
    OSReport("|         Align Group  size    ( prev , next )\n");
    OSReport("| ---- FreeFirst\n");
    OSReport("| %08x  ");
    OSReport("%2x  %3d  %6x  (%08x %08x)\n");
    OSReport("| ---- FreeLast\n");
    OSReport("| ---- UsedFirst\n");
    OSReport("| ---- UsedLast\n");
    OSReport("+---------------End\n");
}

/* 802B30A4-802B31D4       .text state_register__10JKRExpHeapCFPQ27JKRHeap6TStateUl */
void JKRExpHeap::state_register(TState* p, u32 param_1) const {
    JUT_ASSERT(VERSION_SELECT(2420, 2423, 2423), p != NULL);
    JUT_ASSERT(VERSION_SELECT(2421, 2424, 2424), p->getHeap() == this);
    p->mId = param_1;
    if (param_1 <= 0xff) {
        p->mUsedSize = getUsedSize(param_1);
    } else {
        s32 freeSize = const_cast<JKRExpHeap*>(this)->getTotalFreeSize();
        p->mUsedSize = getSize() - freeSize;
    }

    u32 checkCode = 0;
    for (CMemBlock* block = mHeadUsedList; block; block = block->getNextBlock()) {
        if (param_1 <= 0xff) {
            u8 groupId = block->getGroupId();
            if (groupId == param_1) {
                checkCode += (u32)block * 3;
            }
        } else {
            checkCode += (u32)block * 3;
        }
    }
    p->mCheckCode = checkCode;
}

/* 802B31D4-802B327C       .text state_compare__10JKRExpHeapCFRCQ27JKRHeap6TStateRCQ27JKRHeap6TState */
bool JKRExpHeap::state_compare(const JKRHeap::TState& r1, const JKRHeap::TState& r2) const {
    JUT_ASSERT(VERSION_SELECT(2468, 2471, 2471), r1.getHeap() == r2.getHeap());
    bool result = true;
    if (r1.mCheckCode != r2.mCheckCode) {
        result = false;
    }

    if (r1.mUsedSize != r2.mUsedSize) {
        result = false;
    }

    return result;
}

/* 802B327C-802B3288       .text getHeapType__10JKRExpHeapFv */
u32 JKRExpHeap::getHeapType() {
    return 'EXPH';
}

/* 802B3288-802B3290       .text do_getCurrentGroupId__10JKRExpHeapFv */
u8 JKRExpHeap::do_getCurrentGroupId() {
    return mCurrentGroupId;
}
