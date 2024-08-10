//
// Generated by dtk
// Translation Unit: JASTrackPort.cpp
//

#include "JSystem/JAudio/JASTrackPort.h"
#include "JSystem/JUtility/JUTAssert.h"

const u32 MAX_PORTS = 16;

/* 802842A8-802842E8       .text init__Q28JASystem10TTrackPortFv */
void JASystem::TTrackPort::init() {
    /* Nonmatching */
    for (int i = 0; i < 16; i++) {
        mImportFlag[i] = 0;
        mExportFlag[i] = 0;
        mValue[i] = 0;
    }
}

/* 802842E8-8028437C       .text readImport__Q28JASystem10TTrackPortFi */
u16 JASystem::TTrackPort::readImport(int port_num) {
    JUT_ASSERT(31, port_num >= 0 && port_num < MAX_PORTS);
    mImportFlag[port_num] = 0;
    return mValue[port_num];
}

/* 8028437C-80284414       .text readExport__Q28JASystem10TTrackPortFi */
u16 JASystem::TTrackPort::readExport(int port_num) {
    JUT_ASSERT(38, port_num >= 0 && port_num < MAX_PORTS);
    mExportFlag[port_num] = 0;
    return mValue[port_num];
}

/* 80284414-802844AC       .text writeImport__Q28JASystem10TTrackPortFiUs */
void JASystem::TTrackPort::writeImport(int port_num, u16 value) {
    JUT_ASSERT(45, port_num >= 0 && port_num < MAX_PORTS);
    mImportFlag[port_num] = 1;
    mValue[port_num] = value;
}

/* 802844AC-80284548       .text writeExport__Q28JASystem10TTrackPortFiUs */
void JASystem::TTrackPort::writeExport(int port_num, u16 value) {
    JUT_ASSERT(51, port_num >= 0 && port_num < MAX_PORTS);
    mExportFlag[port_num] = 1;
    mValue[port_num] = value;
}
