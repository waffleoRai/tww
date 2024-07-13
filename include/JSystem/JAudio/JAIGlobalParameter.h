#ifndef JAIGLOBALPARAMETER_H
#define JAIGLOBALPARAMETER_H

#include "dolphin/types.h"

namespace JAIGlobalParameter {
    inline void getPointerDistanceMax() {}
    inline void getPointerMaxVolumeDistance() {}
    inline void getPointerMinDistanceVolume() {}
    inline void getPointerSeDolbyBehindDistanceMax() {}
    inline void getPointerSeDolbyCenterValue() {}
    inline void getPointerSeDolbyFrontDistanceMax() {}

    void setParamInitDataPointer(void*);
    void setParamInterfaceHeapSize(u32);
    void setParamSoundSceneMax(u32);
    void setParamSeRegistMax(u32);
    void setParamSeTrackMax(u32);
    void setParamSeqPlayTrackMax(u32);
    void setParamSeqControlBufferMax(u32);
    void setParamStreamControlBufferMax(u32);
    void setParamAutoHeapMax(u32);
    void setParamStayHeapMax(u32);
    void setParamInputGainDown(f32);
    void setParamOutputGainUp(f32);
    void setParamDistanceMax(f32);
    void setParamMaxVolumeDistance(f32);
    void setParamMinDistanceVolume(f32);
    void setParamSeDistanceFxParameter(u16);
    void setParamStreamDecodedBufferBlocks(u32);
    void setParamStreamInsideBufferCut(bool);
    void setParamAutoHeapRoomSize(u32);
    void setParamStayHeapSize(u32);
    void setParamSeDolbyCenterValue(u8);
    void setParamSeDolbyFrontDistanceMax(f32);
    void setParamSeDolbyBehindDistanceMax(f32);
    void setParamInitDataFileName(char*);
    void setParamWavePath(char*);
    void setParamSequenceArchivesPath(char*);
    void setParamStreamPath(char*);
    void setParamAudioResPath(char*);
    void setParamSequenceArchivesFileName(char*);
    void setParamDummyObjectLifeTime(u32);
    void setParamDummyObjectMax(u32);
    void setParamAudioCameraMax(u32);
    void setParamSystemTrackMax(s32);
    void setParamSoundOutputMode(u32);
    u32 getParamSeCategoryMax();
    u32 getParamSoundSceneMax();
    u32 getParamSeRegistMax();
    u32 getParamSeTrackMax();
    u32 getParamSeqTrackMax();
    u32 getParamSeqControlBufferMax();
    u32 getParamStreamControlBufferMax();
    u32 getParamStreamParameterBufferMax();
    u32 getParamAutoHeapMax();
    u32 getParamStayHeapMax();
    u32 getParamSeqPlayTrackMax();
    f32 getParamDistanceMax();
    f32 getParamMaxVolumeDistance();
    f32 getParamMinDistanceVolume();
    u32 getParamAutoHeapRoomSize();
    u32 getParamStayHeapSize();
    f32 getParamSeDolbyCenterValue();
    f32 getParamSeDolbyFrontDistanceMax();
    f32 getParamSeDolbyBehindDistanceMax();
    char* getParamInitDataFileName();
    char* getParamWavePath();
    char* getParamSequenceArchivesPath();
    char* getParamStreamPath();
    char* getParamAudioResPath();
    char* getParamSequenceArchivesFileName();
    u32 getParamDopplarMoveTime();
    u8 getParamDistanceParameterMoveTime();
    u32 getParamDummyObjectMax();
    u8 getParamSeqMuteVolumeSePlay();
    u32 getParamSeqMuteMoveSpeedSePlay();
    u32 getParamAudioCameraMax();
    u8 getParamSeqParameterLines();
    u8 getParamStreamParameterLines();
    u16 getParamSeDistanceWaitMax();

    extern u8 distanceParameterMoveTime;
    extern u8 audioSystemThreadPriority;
    extern u8 audioDvdThreadPriority;
    extern u8 seqMuteVolumeSePlay;
    extern u8 seqParameterLines;
    extern u8 streamParameterLines;
    extern u16 seDistanceFxParameter;
    extern u32 soundSceneMax;
    extern u32 seRegistMax;
    extern u32 seTrackMax;
    extern u32 seqTrackMax;
    extern u32 seqPlayTrackMax;
    extern u32 seqControlBufferMax;
    extern u32 streamControlBufferMax;
    extern u32 streamParameterBufferMax;
    extern u32 autoHeapMax;
    extern u32 stayHeapMax;
    extern u32 autoHeapRoomSize;
    extern u32 stayHeapSize;
    extern char* initDataFileName;
    extern char* wavePath;
    extern char* sequenceArchivesPath;
    extern char* streamPath;
    extern char* audioResPath;
    extern char* sequenceArchivesFileName;
    extern f32 inputGainDown;
    extern f32 outputGainUp;
    extern f32 distanceMax;
    extern f32 maxVolumeDistance;
    extern f32 seDolbyCenterValue;
    extern f32 seDolbyFrontDistanceMax;
    extern f32 seDolbyBehindDistanceMax;
    extern u32 dopplarMoveTime;
    extern u32 dummyObjectLifeTime;
    extern u32 dummyObjectMax;
    extern u32 seqMuteMoveSpeedSePlay;
    extern u32 audioCameraMax;
    extern s32 systemTrackMax;
    extern f32 panDistanceMax;
    extern f32 panDistance2Max;
    extern f32 panAngleParameter;
    extern f32 panAngleParameter2;
    extern f32 dopplarParameter;
    extern u16 seDistanceWaitMax;
    extern f32 seDistancepitchMax;
    extern u16 seDefaultFx;
    extern u32 interfaceHeapSize;
    extern f32 minDistanceVolume;
}

#endif /* JAIGLOBALPARAMETER_H */
